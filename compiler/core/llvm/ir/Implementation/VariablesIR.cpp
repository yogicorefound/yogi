//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

#include "semantic/semantic.h"
#include "utils/utils.h"

namespace yogi::core::ir {
    inline uint64_t IR::getStringLength(const std::any &node) {
        if (const auto str = std::any_cast<visitor::nodes::StringLiteralNode>(&node)) {
            return str->value.size();
        }

        throw std::runtime_error("Expected string literal for length extraction");
    }

    llvm::Value *IR::variableDeclaration(const visitor::nodes::VariableDeclarationNode &node) {
        llvm::Function *currentFn = builder->GetInsertBlock()->getParent();

        if (!currentFn)
            throw std::runtime_error("Must be inside a function");

        llvm::Type *varType = mapDataType(node.varType);

        // =========================
        // 1. ALLOCATE VARIABLE
        // =========================
        llvm::AllocaInst *alloca = builder->CreateAlloca(varType, nullptr, node.identifier);

        llvm::Value *initVal = nullptr;

        // =========================
        // 2. INITIAL VALUE
        // =========================
        if (node.value.has_value()) {
            initVal = expression(node.value);

            if (!initVal)
                throw std::runtime_error("Initializer is null");

            llvm::Type *initType = initVal->getType();

            // =========================
            // STRING HANDLING (IMPORTANT)
            // =========================
            if (varType->isPointerTy() && node.varType == utils::Types::String) {

                // assume expression returns i8* for string literal
                llvm::Value *strPtr = initVal;

                llvm::Value *len =
                        llvm::ConstantInt::get(
                            builder->getInt64Ty(),
                            getStringLength(node.value) // your semantic helper
                        );

                // call runtime:
                llvm::Function *createStringFn = module->getFunction("create_string");

                if (!createStringFn)
                    throw std::runtime_error("");

                initVal = builder->CreateCall(
                    createStringFn,
                    {strPtr, len}
                );
            }

            // =========================
            // NUMERIC CASTING
            // =========================
            else if (initType != varType) {
                if (initType->isIntegerTy() &&
                    varType->isFloatingPointTy()) {

                    initVal = builder->CreateSIToFP(initVal, varType);
                } else if (initType->isFloatingPointTy() &&
                           varType->isIntegerTy()) {

                    initVal = builder->CreateFPToSI(initVal, varType);
                } else if (initType->isIntegerTy() &&
                           varType->isIntegerTy()) {

                    auto *src = llvm::cast<llvm::IntegerType>(initType);
                    auto *dst = llvm::cast<llvm::IntegerType>(varType);

                    if (src->getBitWidth() < dst->getBitWidth())
                        initVal = builder->CreateSExt(initVal, varType);
                    else if (src->getBitWidth() > dst->getBitWidth())
                        initVal = builder->CreateTrunc(initVal, varType);
                } else {
                    throw std::runtime_error(
                        "Type mismatch (should be caught in semantic phase): "
                        + node.identifier
                    );
                }

            }

        } else {
            initVal = llvm::Constant::getNullValue(varType);
        }

        // =========================
        // 3. STORE VALUE
        // =========================
        builder->CreateStore(initVal, alloca);

        // =========================
        // 4. SYMBOL TABLE
        // =========================
        symbols[node.identifier] = alloca;

        return alloca;
    }


    llvm::Value *IR::variableAssignment(const visitor::nodes::VariableDeclarationNode &node) {
        const auto it = symbols.find(node.identifier);
        if (it == symbols.end())
            throw std::runtime_error("Assign to undefined variable: " + node.identifier);

        const llvm::Value *currentVal = it->second;
        llvm::Type *varType = currentVal->getType();

        llvm::Value *rhs = expression(node.value);
        if (!rhs)
            throw std::runtime_error("Variable assignment RHS produced null");

        // Type conversion (same logic as declaration)
        if (rhs->getType() != varType) {
            if (rhs->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                rhs = rhs->getType()->getIntegerBitWidth() == 1 ? builder->CreateUIToFP(rhs, varType, "assign_bool_to_fp") : builder->CreateSIToFP(rhs, varType, "assign_int_to_fp");
            } else if (rhs->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                rhs = builder->CreateFPToSI(rhs, varType, "assign_fp_to_int");
            } else if (rhs->getType()->isIntegerTy() && varType->isIntegerTy()) {
                const auto *Rit = llvm::cast<llvm::IntegerType>(rhs->getType());

                if (auto *Vt = llvm::cast<llvm::IntegerType>(varType); Rit->getBitWidth() < Vt->getBitWidth()) {
                    rhs = Rit->getBitWidth() == 1 ? builder->CreateZExt(rhs, Vt, "assign_zext") : builder->CreateSExt(rhs, Vt, "assign_sext");
                } else if (Rit->getBitWidth() > Vt->getBitWidth()) {
                    rhs = builder->CreateTrunc(rhs, Vt, "assign_trunc");
                }
            } else if (rhs->getType()->isPointerTy() && varType->isPointerTy()) {
                rhs = builder->CreateBitCast(rhs, varType, "assign_bitcast");
            } else {
                throw std::runtime_error("Cannot convert assignment RHS to variable type for: " + node.identifier);
            }
        }

        // Update the symbol table with the new SSA value
        symbols[node.identifier] = rhs;
        return rhs;
    }

} // namespace yogi::core::ir