// Created by Brayhan De Aza on 11/25/25.
//

#include "../IR.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include "llvm/IR/Verifier.h"
#include "llvm/Linker/Linker.h"

namespace cromio::core::ir {
    using namespace cromio::visitor::nodes;

    IR::IR(const std::string& moduleName) {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>(moduleName, *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
    }

    bool IR::linkModule(std::unique_ptr<llvm::Module> other) const {
        llvm::Linker linker(*module);
        if (constexpr llvm::Linker::Flags flags = llvm::Linker::Flags::None;
            linker.linkInModule(std::move(other), flags))
            return false;
        return true;
    }

    llvm::Type* IR::mapDataType(const std::string& typeName) const {
        if (typeName == "int") return builder->getInt32Ty();
        if (typeName == "int8") return builder->getInt8Ty();
        if (typeName == "int16") return builder->getInt16Ty();
        if (typeName == "int32") return builder->getInt32Ty();
        if (typeName == "int64") return builder->getInt64Ty();
        if (typeName == "float") return builder->getDoubleTy();
        if (typeName == "float32") return builder->getFloatTy();
        if (typeName == "float64") return builder->getDoubleTy();
        if (typeName == "bool") return builder->getInt1Ty();
        if (typeName == "none") return builder->getInt8Ty();
        if (typeName == "str") return llvm::PointerType::get(*context, 0);
        return builder->getInt64Ty();
    }

    llvm::Value* IR::promoteToDouble(llvm::Value* v) const {
        if (v->getType()->isDoubleTy())
            return v;
        if (v->getType()->isIntegerTy())
            return builder->CreateSIToFP(v, builder->getDoubleTy(), "int_to_double");
        throw std::runtime_error("Cannot promote value to double");
    }

    llvm::Type* IR::inferType(const std::any& node) const {
        if (!node.has_value())
            throw std::runtime_error("Cannot infer type from empty node");

        try {
            if (node.type() == typeid(FloatLiteralNode)) {
                return builder->getDoubleTy();
            }
            if (node.type() == typeid(IntegerLiteralNode)) {
                return builder->getInt32Ty();
            }
            if (node.type() == typeid(BooleanLiteralNode)) {
                return builder->getInt1Ty();
            }
            if (node.type() == typeid(NoneLiteralNode)) {
                return builder->getInt8Ty();
            }
            if (node.type() == typeid(StringLiteralNode)) {
                return llvm::PointerType::get(*context, 0);
            }
            if (node.type() == typeid(VariableDeclarationNode)) {
                auto n = std::any_cast<VariableDeclarationNode>(node);
                return mapDataType(n.varType);
            }
            if (node.type() == typeid(BinaryExpressionNode)) {
                auto n = std::any_cast<BinaryExpressionNode>(node);
                llvm::Type* LT = inferType(n.left);
                llvm::Type* RT = inferType(n.right);

                if (LT->isDoubleTy() || RT->isDoubleTy())
                    return builder->getDoubleTy();
                if (LT->isFloatTy() || RT->isFloatTy())
                    return builder->getFloatTy();

                if (LT->isIntegerTy() && RT->isIntegerTy()) {
                    auto* LIT = llvm::cast<llvm::IntegerType>(LT);
                    auto* RIT = llvm::cast<llvm::IntegerType>(RT);
                    unsigned maxBits = std::max(LIT->getBitWidth(), RIT->getBitWidth());
                    return builder->getIntNTy(maxBits);
                }
            }
            if (node.type() == typeid(IdentifierLiteral)) {
                auto n = std::any_cast<IdentifierLiteral>(node);
                auto it = symbols.find(n.value);
                if (it == symbols.end())
                    throw std::runtime_error("Undefined identifier in inferType: " + n.value);
                return it->second->getAllocatedType();
            }
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Type inference failed: " + std::string(e.what()));
        }

        throw std::runtime_error("Unknown node type in inferType");
    }

    llvm::AllocaInst* IR::createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name) {
        llvm::IRBuilder tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
        return tmpBuilder.CreateAlloca(type, nullptr, name);
    }

    std::unique_ptr<llvm::Module> IR::loadBitcode(const std::string& path, llvm::LLVMContext& context) {
        llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> mb = llvm::MemoryBuffer::getFile(path);
        if (!mb)
            return nullptr;

        llvm::Expected<std::unique_ptr<llvm::Module>> modOrErr =
            llvm::parseBitcodeFile(mb.get()->getMemBufferRef(), context);

        if (!modOrErr)
            return nullptr;

        return std::move(*modOrErr);
    }

    void IR::loadAndLinkModulesFromFolder() const {
        const std::string folderPath = "../modules";

        if (!std::filesystem::exists(folderPath))
            return;

        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".bc")
                continue;

            try {
                if (auto extMod = loadBitcode(entry.path().string(), *context);
                    extMod && !linkModule(std::move(extMod))) {
                    llvm::errs() << "Warning: Failed to link module: " << entry.path() << "\n";
                }
            } catch (...) {
                llvm::errs() << "Warning: Skipping module: " << entry.path() << "\n";
            }
        }
    }

    llvm::Module* IR::generate(const ProgramNode& node) {
        loadAndLinkModulesFromFolder();
        program(node);
        return module.get();
    }

    llvm::Value* IR::program(const ProgramNode& node) {
        // Create main function
        llvm::Type* retType = builder->getInt32Ty();
        auto* fnType = llvm::FunctionType::get(retType, false);
        auto* fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, "main", module.get());

        auto* entry = llvm::BasicBlock::Create(*context, "entry", fn);
        builder->SetInsertPoint(entry);

        // Process all statements in the program
        for (const auto& stmt : node.body) {
            try {
                statement(stmt);
            } catch (const std::exception& e) {
                throw std::runtime_error("Program generation failed: " + std::string(e.what()));
            }
        }

        // Return 0
        builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

        if (llvm::verifyFunction(*fn, &llvm::errs()))
            throw std::runtime_error("IR verification failed");

        return fn;
    }
} // namespace cromio::lowering