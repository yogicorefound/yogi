//
// Created by Brayhan De Aza on 11/27/25.
//

#include "CodeEmitter.h"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>
#include <fstream>
#include <optional>

namespace cromio::lowering {
    std::vector<uint8_t> CodeEmitter::toMemory(const llvm::Module& module) {
        llvm::SmallVector<char, 0> buffer;
        llvm::raw_svector_ostream stream(buffer);
        llvm::WriteBitcodeToFile(module, stream);

        return {buffer.begin(), buffer.end()};
    }

    void CodeEmitter::toFile(const llvm::Module& module, const std::string& filename) {
        llvm::SmallVector<char, 0> buffer;
        llvm::raw_svector_ostream stream(buffer);

        llvm::WriteBitcodeToFile(module, stream);

        std::ofstream out(filename, std::ios::binary);
        if (!out)
            throw std::runtime_error("Failed to open output file: " + filename);

        out.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        out.close();
    }

    std::vector<uint8_t> CodeEmitter::toObjectInMemory(llvm::Module* module) {
        // Initialize native target for code generation
        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        std::string err;
        const auto targetTripleStr = llvm::sys::getDefaultTargetTriple();

        // Create Triple object (LLVM 21 requires explicit Triple type)
        const llvm::Triple targetTriple(targetTripleStr);
        module->setTargetTriple(targetTriple);

        const llvm::Target* target = llvm::TargetRegistry::lookupTarget(targetTripleStr, err);
        if (!target)
            throw std::runtime_error("Failed to lookup target: " + err);

        const llvm::TargetOptions opt;
        constexpr std::optional<llvm::Reloc::Model> RM = std::nullopt;

        llvm::TargetMachine* targetMachine = target->createTargetMachine(targetTriple, "generic", "", opt, RM);

        module->setDataLayout(targetMachine->createDataLayout());

        // Use SmallVector to capture object file in memory
        llvm::SmallVector<char, 0> buffer;
        {
            llvm::raw_svector_ostream dest(buffer);

            llvm::legacy::PassManager pass;

            // LLVM 21 uses CodeGenFileType enum class
            if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) {
                throw std::runtime_error("TargetMachine can't emit object file");
            }

            pass.run(*module);
            // dest automatically flushes when it goes out of scope
        }

        return {buffer.begin(), buffer.end()};
    }

    void CodeEmitter::toObjectFile(llvm::Module* module, const std::string& outputPath) {
        // Get object code in memory
        const auto objectCode = toObjectInMemory(module);

        // Write to file
        std::ofstream out(outputPath, std::ios::binary);
        if (!out)
            throw std::runtime_error("Failed to open output file: " + outputPath);

        out.write(reinterpret_cast<const char*>(objectCode.data()), static_cast<std::streamsize>(objectCode.size()));
        out.close();
    }

    void CodeEmitter::toExecutable(llvm::Module* module, const std::string& outputPath) {
        // Get object code in memory
        const auto objectCode = toObjectInMemory(module);

        // Create temporary object file
        const std::string tempObjPath = outputPath + "_temp.o";
        std::ofstream tempOut(tempObjPath, std::ios::binary);
        if (!tempOut)
            throw std::runtime_error("Failed to create temporary object file");

        tempOut.write(reinterpret_cast<const char*>(objectCode.data()), static_cast<std::streamsize>(objectCode.size()));
        tempOut.close();

        // Link object file into executable using system linker
        const std::string linkCommand = "clang++ \"" + tempObjPath + "\" -o \"" + outputPath + "\"";

        if (const int result = std::system(linkCommand.c_str()); result != 0) {
            std::remove(tempObjPath.c_str());
            throw std::runtime_error("Failed to link executable");
        }

        // Clean up temporary object file
        std::remove(tempObjPath.c_str());
    }
} // namespace cromio::lowering