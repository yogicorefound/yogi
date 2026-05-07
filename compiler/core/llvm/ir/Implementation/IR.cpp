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
#include "utils/utils.h"

namespace yogi::core::ir {
    using namespace yogi::visitor::nodes;

    void IR::declareRuntimeFunctions() const {
        // struct String* create_string(const char* data, int64_t len)
        //
        // In LLVM's type system, since String* is an opaque pointer in modern LLVM,
        // we represent it as ptr (i8* in older LLVM)

        llvm::Type *ptrTy = llvm::PointerType::get(builder->getContext(), 0);
        llvm::Type *int64Ty = builder->getInt64Ty();

        llvm::FunctionType *createStringTy = llvm::FunctionType::get(
            ptrTy, // return type: String*
            {ptrTy, int64Ty}, // args: const char*, int64_t
            false // not variadic
        );

        module->getOrInsertFunction("create_string", createStringTy);
    }

    IR::IR(const std::string &moduleName) {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>(moduleName, *context);
        builder = std::make_unique<llvm::IRBuilder<> >(*context);

        declareRuntimeFunctions();
    }

    llvm::Value *IR::convertType(llvm::Value *val, llvm::Type *targetType, const std::string &name, const std::string &phase) const {
        if (val->getType() == targetType)
            return val;

        if (val->getType()->isIntegerTy() && targetType->isFloatingPointTy()) {
            return val->getType()->getIntegerBitWidth() == 1 ? builder->CreateUIToFP(val, targetType, name + "_" + phase + "_bool_to_fp") : builder->CreateSIToFP(val, targetType, name + "_" + phase + "_int_to_fp");
        }
        if (val->getType()->isFloatingPointTy() && targetType->isIntegerTy()) {
            return builder->CreateFPToSI(val, targetType, name + "_" + phase + "_fp_to_int");
        }
        if (val->getType()->isIntegerTy() && targetType->isIntegerTy()) {
            const auto *src = llvm::cast<llvm::IntegerType>(val->getType());
            auto *tgt = llvm::cast<llvm::IntegerType>(targetType);

            if (src->getBitWidth() < tgt->getBitWidth())
                return src->getBitWidth() == 1 ? builder->CreateZExt(val, tgt, name + "_" + phase + "_zext") : builder->CreateSExt(val, tgt, name + "_" + phase + "_sext");

            return builder->CreateTrunc(val, tgt, name + "_" + phase + "_trunc");
        }
        if (val->getType()->isPointerTy() && targetType->isPointerTy()) {
            return builder->CreateBitCast(val, targetType, name + "_" + phase + "_bitcast");
        }

        throw std::runtime_error("Cannot convert value to target type for: " + name);
    }

    bool IR::linkModule(std::unique_ptr<llvm::Module> other) const {
        llvm::Linker linker(*module);
        if (constexpr llvm::Linker::Flags flags = llvm::Linker::Flags::None; linker.linkInModule(std::move(other), flags))
            return false;
        return true;
    }

    llvm::Type *IR::mapDataType(const utils::Types &typeName) const {

        // =====================
        // INTEGER TYPES
        // =====================
        if (typeName == utils::Types::Integer8)
            return builder->getInt8Ty();

        if (typeName == utils::Types::Integer16)
            return builder->getInt16Ty();

        if (typeName == utils::Types::Integer32)
            return builder->getInt32Ty(); // default int

        if (typeName == utils::Types::Integer64)
            return builder->getInt64Ty();

        // =====================
        // FLOATING TYPES
        // =====================
        if (typeName == utils::Types::Float32)
            return builder->getFloatTy();

        if (typeName == utils::Types::Float64 ||
            typeName == utils::Types::Float)
            return builder->getDoubleTy(); // default float = double

        // =====================
        // BOOLEAN
        // =====================
        if (typeName == utils::Types::Boolean)
            return builder->getInt1Ty();

        // =====================
        // VOID / NONE
        // =====================
        if (typeName == utils::Types::Void ||
            typeName == utils::Types::None)
            return builder->getVoidTy();

        // =====================
        // STRING
        // =====================
        if (typeName == utils::Types::String)
            return llvm::PointerType::get(*context, 0); // opaque pointer

        // =====================
        // FALLBACK (SHOULD NEVER HAPPEN)
        // =====================
        throw std::runtime_error("Unknown type in mapDataType");
    }

    llvm::Value *IR::promoteToDouble(llvm::Value *v) const {
        if (v->getType()->isDoubleTy())
            return v;
        if (v->getType()->isIntegerTy())
            return builder->CreateSIToFP(v, builder->getDoubleTy(), "int_to_double");
        throw std::runtime_error("Cannot promote value to double");
    }

    llvm::Type *IR::inferType(const std::any &node) const {
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
                llvm::Type *LT = inferType(n.left);
                llvm::Type *RT = inferType(n.right);

                if (LT->isDoubleTy() || RT->isDoubleTy())
                    return builder->getDoubleTy();
                if (LT->isFloatTy() || RT->isFloatTy())
                    return builder->getFloatTy();

                if (LT->isIntegerTy() && RT->isIntegerTy()) {
                    auto *LIT = llvm::cast<llvm::IntegerType>(LT);
                    auto *RIT = llvm::cast<llvm::IntegerType>(RT);
                    unsigned maxBits = std::max(LIT->getBitWidth(), RIT->getBitWidth());
                    return builder->getIntNTy(maxBits);
                }
            }
            if (node.type() == typeid(IdentifierLiteral)) {
                auto n = std::any_cast<IdentifierLiteral>(node);
                auto it = symbols.find(n.value);
                if (it == symbols.end())
                    throw std::runtime_error("Undefined identifier in inferType: " + n.value);
                return it->second->getType();
            }
        } catch (const std::bad_any_cast &e) {
            throw std::runtime_error("Type inference failed: " + std::string(e.what()));
        }

        throw std::runtime_error("Unknown node type in inferType");
    }

    llvm::AllocaInst *IR::createEntryBlockAlloca(llvm::Function *function, llvm::Type *type, const std::string &name) {
        llvm::IRBuilder tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
        return tmpBuilder.CreateAlloca(type, nullptr, name);
    }

    std::unique_ptr<llvm::Module> IR::loadBitcode(const std::string &path, llvm::LLVMContext &context) {
        llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer> > mb = llvm::MemoryBuffer::getFile(path);
        if (!mb)
            return nullptr;

        llvm::Expected<std::unique_ptr<llvm::Module> > modOrErr = llvm::parseBitcodeFile(mb.get()->getMemBufferRef(), context);

        if (!modOrErr)
            return nullptr;

        return std::move(*modOrErr);
    }

    void IR::loadAndLinkModulesFromFolder() const {
        constexpr std::string folderPath = "../modules";

        if (!std::filesystem::exists(folderPath))
            return;

        for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".bc")
                continue;

            try {
                if (auto extMod = loadBitcode(entry.path().string(), *context); extMod && !linkModule(std::move(extMod))) {
                    llvm::errs() << "Warning: Failed to link module: " << entry.path() << "\n";
                }
            } catch (...) {
                llvm::errs() << "Warning: Skipping module: " << entry.path() << "\n";
            }
        }
    }

    llvm::Module *IR::generate(const ProgramNode &node) {
        loadAndLinkModulesFromFolder();
        program(node);
        return module.get();
    }

    llvm::Value *IR::program(const ProgramNode &node) {
        // Create main function
        llvm::Type *retType = builder->getInt32Ty();
        auto *fnType = llvm::FunctionType::get(retType, false);
        auto *fn = llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, "main", module.get());

        auto *entry = llvm::BasicBlock::Create(*context, "entry", fn);
        builder->SetInsertPoint(entry);

        // Process all statements in the program
        for (const auto &stmt: node.body) {
            try {
                statement(stmt);
            } catch (const std::exception &e) {
                throw std::runtime_error("Program generation failed: " + std::string(e.what()));
            }
        }

        // Return 0
        builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 0));

        if (llvm::verifyFunction(*fn, &llvm::errs()))
            throw std::runtime_error("IR verification failed");

        return fn;
    }
} // namespace yogi::core::ir