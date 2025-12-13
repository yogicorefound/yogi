// Created by Brayhan De Aza on 11/25/25.
//

#include "IR.h"
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <filesystem>
#include <stdexcept>
#include <string>
#include "llvm/IR/Verifier.h"
#include "llvm/Linker/Linker.h"

namespace cromio::lowering {
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

    llvm::Value* IR::literal(const std::any& node) {
        if (!node.has_value())
            throw std::runtime_error("Cannot generate code for empty literal");

        try {
            if (node.type() == typeid(FloatLiteralNode)) {
                auto n = std::any_cast<FloatLiteralNode>(node);
                double val = std::stod(n.value);
                return llvm::ConstantFP::get(builder->getDoubleTy(), val);
            }
            if (node.type() == typeid(IntegerLiteralNode)) {
                auto n = std::any_cast<IntegerLiteralNode>(node);
                long long val = std::stoll(n.value);
                return llvm::ConstantInt::get(builder->getInt32Ty(), val, true);
            }
            if (node.type() == typeid(BooleanLiteralNode)) {
                auto n = std::any_cast<BooleanLiteralNode>(node);
                int val = (n.value == "1") ? 1 : 0;
                return llvm::ConstantInt::get(builder->getInt1Ty(), val);
            }
            if (node.type() == typeid(NoneLiteralNode)) {
                return llvm::ConstantInt::get(builder->getInt8Ty(), 0);
            }
            if (node.type() == typeid(StringLiteralNode)) {
                auto n = std::any_cast<StringLiteralNode>(node);
                return builder->CreateGlobalString(n.value, "str");
            }
            if (node.type() == typeid(IdentifierLiteral)) {
                auto n = std::any_cast<IdentifierLiteral>(node);
                auto it = symbols.find(n.value);
                if (it == symbols.end())
                    throw std::runtime_error("Undefined identifier: " + n.value);
                llvm::AllocaInst* alloc = it->second;
                return builder->CreateLoad(alloc->getAllocatedType(), alloc, n.value + ".load");
            }
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Literal generation failed: " + std::string(e.what()));
        }

        throw std::runtime_error("Unknown literal type");
    }

    llvm::Value* IR::expression(const std::any& node) {
        if (!node.has_value())
            throw std::runtime_error("Cannot generate code for empty expression");

        // Try literals first
        if (node.type() == typeid(IntegerLiteralNode) ||
            node.type() == typeid(FloatLiteralNode) ||
            node.type() == typeid(BooleanLiteralNode) ||
            node.type() == typeid(NoneLiteralNode) ||
            node.type() == typeid(StringLiteralNode) ||
            node.type() == typeid(IdentifierLiteral)) {
            return literal(node);
        }

        // Binary Expression
        if (node.type() == typeid(BinaryExpressionNode)) {
            auto n = std::any_cast<BinaryExpressionNode>(node);

            llvm::Value* L = expression(n.left);
            llvm::Value* R = expression(n.right);

            if (!L || !R)
                throw std::runtime_error("Subexpression produced null");

            const std::string& op = n.op;

            // FLOATING POINT OPERATIONS
            if (L->getType()->isDoubleTy() || R->getType()->isDoubleTy()) {
                L = promoteToDouble(L);
                R = promoteToDouble(R);

                if (op == "+") return builder->CreateFAdd(L, R, "fadd");
                if (op == "-") return builder->CreateFSub(L, R, "fsub");
                if (op == "*") return builder->CreateFMul(L, R, "fmul");
                if (op == "/") return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%") return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for double: " + op);
            }

            // FLOAT (32-bit) OPERATIONS
            if (L->getType()->isFloatTy() || R->getType()->isFloatTy()) {
                if (!L->getType()->isFloatingPointTy())
                    L = builder->CreateSIToFP(L, builder->getFloatTy(), "int_to_float");
                if (!R->getType()->isFloatingPointTy())
                    R = builder->CreateSIToFP(R, builder->getFloatTy(), "int_to_float");

                if (op == "+") return builder->CreateFAdd(L, R, "fadd");
                if (op == "-") return builder->CreateFSub(L, R, "fsub");
                if (op == "*") return builder->CreateFMul(L, R, "fmul");
                if (op == "/") return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%") return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for float: " + op);
            }

            // INTEGER OPERATIONS
            if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy()) {
                auto* Lit = llvm::cast<llvm::IntegerType>(L->getType());
                auto* Rit = llvm::cast<llvm::IntegerType>(R->getType());

                unsigned maxBits = std::max(Lit->getBitWidth(), Rit->getBitWidth());
                llvm::IntegerType* opType = builder->getIntNTy(maxBits);

                if (Lit->getBitWidth() < maxBits) {
                    L = (Lit->getBitWidth() == 1) ?
                        builder->CreateZExt(L, opType, "zext_l") :
                        builder->CreateSExt(L, opType, "sext_l");
                }
                if (Rit->getBitWidth() < maxBits) {
                    R = (Rit->getBitWidth() == 1) ?
                        builder->CreateZExt(R, opType, "zext_r") :
                        builder->CreateSExt(R, opType, "sext_r");
                }

                if (op == "+") return builder->CreateAdd(L, R, "addtmp");
                if (op == "-") return builder->CreateSub(L, R, "subtmp");
                if (op == "*") return builder->CreateMul(L, R, "multmp");
                if (op == "/") return builder->CreateSDiv(L, R, "divtmp");
                if (op == "%") return builder->CreateSRem(L, R, "modtmp");

                throw std::runtime_error("Unsupported integer operator: " + op);
            }

            throw std::runtime_error("Unsupported operand types in Expression");
        }

        throw std::runtime_error("Invalid expression node");
    }

    llvm::AllocaInst* IR::createEntryBlockAlloca(llvm::Function* function, llvm::Type* type, const std::string& name) {
        llvm::IRBuilder tmpBuilder(&function->getEntryBlock(), function->getEntryBlock().begin());
        return tmpBuilder.CreateAlloca(type, nullptr, name);
    }

    llvm::Value* IR::variableDeclaration(const VariableDeclarationNode& node) {
        llvm::Type* varType = mapDataType(node.varType);

        llvm::Function* currentFn = builder->GetInsertBlock()->getParent();
        if (!currentFn)
            throw std::runtime_error("Must be inside a function to declare variable");

        llvm::AllocaInst* allocaInst = createEntryBlockAlloca(currentFn, varType, node.identifier);
        symbols[node.identifier] = allocaInst;

        // Evaluate initializer if present
        if (node.value.has_value()) {
            llvm::Value* initVal = expression(node.value);
            if (!initVal)
                throw std::runtime_error("Variable initializer produced null");

            // Type conversion if necessary
            if (initVal->getType() != varType) {
                if (initVal->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                    initVal = (initVal->getType()->getIntegerBitWidth() == 1) ?
                        builder->CreateUIToFP(initVal, varType, "init_bool_to_fp") :
                        builder->CreateSIToFP(initVal, varType, "init_int_to_fp");
                }
                else if (initVal->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                    initVal = builder->CreateFPToSI(initVal, varType, "init_fp_to_int");
                }
                else if (initVal->getType()->isIntegerTy() && varType->isIntegerTy()) {
                    auto* initType = llvm::cast<llvm::IntegerType>(initVal->getType());
                    auto* targetType = llvm::cast<llvm::IntegerType>(varType);

                    if (initType->getBitWidth() < targetType->getBitWidth()) {
                        initVal = (initType->getBitWidth() == 1) ?
                            builder->CreateZExt(initVal, varType, "init_zext") :
                            builder->CreateSExt(initVal, varType, "init_sext");
                    }
                    else if (initType->getBitWidth() > targetType->getBitWidth()) {
                        initVal = builder->CreateTrunc(initVal, varType, "init_trunc");
                    }
                }
                else if (initVal->getType()->isPointerTy() && varType->isPointerTy()) {
                    initVal = builder->CreateBitCast(initVal, varType, "init_bitcast");
                }
                else {
                    throw std::runtime_error("Cannot convert initializer to variable type for: " + node.identifier);
                }
            }

            builder->CreateStore(initVal, allocaInst);
        }

        return allocaInst;
    }

    llvm::Value* IR::variableAssignment(const VariableDeclarationNode& node) {
        auto it = symbols.find(node.identifier);
        if (it == symbols.end())
            throw std::runtime_error("Assign to undefined variable: " + node.identifier);

        llvm::AllocaInst* slot = it->second;
        llvm::Type* varType = slot->getAllocatedType();

        llvm::Value* rhs = expression(node.value);
        if (!rhs)
            throw std::runtime_error("Variable assignment RHS produced null");

        // Type conversion (same logic as declaration)
        if (rhs->getType() != varType) {
            if (rhs->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                rhs = (rhs->getType()->getIntegerBitWidth() == 1) ?
                    builder->CreateUIToFP(rhs, varType, "assign_bool_to_fp") :
                    builder->CreateSIToFP(rhs, varType, "assign_int_to_fp");
            }
            else if (rhs->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                rhs = builder->CreateFPToSI(rhs, varType, "assign_fp_to_int");
            }
            else if (rhs->getType()->isIntegerTy() && varType->isIntegerTy()) {
                auto* Rit = llvm::cast<llvm::IntegerType>(rhs->getType());
                auto* Vt = llvm::cast<llvm::IntegerType>(varType);

                if (Rit->getBitWidth() < Vt->getBitWidth()) {
                    rhs = (Rit->getBitWidth() == 1) ?
                        builder->CreateZExt(rhs, Vt, "assign_zext") :
                        builder->CreateSExt(rhs, Vt, "assign_sext");
                }
                else if (Rit->getBitWidth() > Vt->getBitWidth()) {
                    rhs = builder->CreateTrunc(rhs, Vt, "assign_trunc");
                }
            }
            else if (rhs->getType()->isPointerTy() && varType->isPointerTy()) {
                rhs = builder->CreateBitCast(rhs, varType, "assign_bitcast");
            }
            else {
                throw std::runtime_error("Cannot convert assignment RHS to variable type for: " + node.identifier);
            }
        }

        builder->CreateStore(rhs, slot);
        return rhs;
    }

    llvm::Value* IR::arrayDeclaration(const ArrayDeclarationNode& node) {
        llvm::Type* elementType = mapDataType(node.elementType);
        size_t arraySize = node.size;

        llvm::ArrayType* arrType = llvm::ArrayType::get(elementType, arraySize);
        llvm::Function* currentFn = builder->GetInsertBlock()->getParent();
        if (!currentFn)
            throw std::runtime_error("Must be inside a function to declare array");

        llvm::AllocaInst* allocaInst = createEntryBlockAlloca(currentFn, arrType, node.identifier);
        symbols[node.identifier] = allocaInst;

        // Initialize array elements
        for (size_t idx = 0; idx < node.elements.size(); idx++) {
            llvm::Value* val = expression(node.elements[idx].value);

            // Get element pointer
            llvm::Value* gep = builder->CreateGEP(
                arrType,
                allocaInst,
                {builder->getInt32(0), builder->getInt32(idx)},
                node.identifier + "_idx" + std::to_string(idx)
            );

            // Type conversion if necessary
            if (val->getType() != elementType) {
                if (val->getType()->isIntegerTy(1) && elementType->isIntegerTy() &&
                    elementType->getIntegerBitWidth() > 1) {
                    val = builder->CreateZExt(val, elementType, "bool_to_int");
                }
                else if (val->getType()->isIntegerTy() && val->getType()->getIntegerBitWidth() > 1 &&
                         elementType->isIntegerTy(1)) {
                    val = builder->CreateICmpNE(val, llvm::ConstantInt::get(val->getType(), 0), "int_to_bool");
                }
                else if (val->getType()->isIntegerTy() && elementType->isIntegerTy()) {
                    auto* vIt = llvm::cast<llvm::IntegerType>(val->getType());
                    auto* tIt = llvm::cast<llvm::IntegerType>(elementType);

                    if (vIt->getBitWidth() < tIt->getBitWidth())
                        val = builder->CreateSExt(val, elementType, "elem_sext");
                    else if (vIt->getBitWidth() > tIt->getBitWidth())
                        val = builder->CreateTrunc(val, elementType, "elem_trunc");
                }
                else if (val->getType()->isIntegerTy() && elementType->isFloatingPointTy())
                    val = builder->CreateSIToFP(val, elementType, "elem_int_to_fp");
                else if (val->getType()->isFloatingPointTy() && elementType->isIntegerTy())
                    val = builder->CreateFPToSI(val, elementType, "elem_fp_to_int");
                else
                    throw std::runtime_error("Cannot convert array element type");
            }

            builder->CreateStore(val, gep);
        }

        return allocaInst;
    }

    llvm::Value* IR::statement(const StatementNode& node) {
        llvm::Value* lastVal = nullptr;

        for (const auto& child : node.children) {
            if (!child.has_value())
                continue;

            try {
                if (child.type() == typeid(VariableDeclarationNode)) {
                    auto n = std::any_cast<VariableDeclarationNode>(child);
                    lastVal = variableDeclaration(n);
                }
                else if (child.type() == typeid(ArrayDeclarationNode)) {
                    auto n = std::any_cast<ArrayDeclarationNode>(child);
                    lastVal = arrayDeclaration(n);
                }
                else {
                    // Default: treat as expression
                    lastVal = expression(child);
                }
            } catch (const std::exception& e) {
                throw std::runtime_error("Statement generation failed: " + std::string(e.what()));
            }
        }

        return lastVal;
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