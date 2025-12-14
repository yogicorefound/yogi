//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace cromio::core::ir {

    llvm::Value* IR::variableDeclaration(const visitor::nodes::VariableDeclarationNode& node) {
        llvm::Type* varType = mapDataType(node.varType);


        if (const llvm::Function* currentFn = builder->GetInsertBlock()->getParent(); !currentFn)
            throw std::runtime_error("Must be inside a function to declare variable");

        // Evaluate initializer if present
        llvm::Value* initVal = nullptr;
        if (node.value.has_value()) {
            initVal = expression(node.value);
            if (!initVal)
                throw std::runtime_error("Variable initializer produced null");

            // Type conversion if necessary
            if (initVal->getType() != varType) {
                if (initVal->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                    initVal = initVal->getType()->getIntegerBitWidth() == 1 ? builder->CreateUIToFP(initVal, varType, "init_bool_to_fp") : builder->CreateSIToFP(initVal, varType, "init_int_to_fp");
                } else if (initVal->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                    initVal = builder->CreateFPToSI(initVal, varType, "init_fp_to_int");
                } else if (initVal->getType()->isIntegerTy() && varType->isIntegerTy()) {
                    const auto* initType = llvm::cast<llvm::IntegerType>(initVal->getType());
                    const auto* targetType = llvm::cast<llvm::IntegerType>(varType);

                    if (initType->getBitWidth() < targetType->getBitWidth()) {
                        initVal = initType->getBitWidth() == 1 ? builder->CreateZExt(initVal, varType, "init_zext") : builder->CreateSExt(initVal, varType, "init_sext");
                    } else if (initType->getBitWidth() > targetType->getBitWidth()) {
                        initVal = builder->CreateTrunc(initVal, varType, "init_trunc");
                    }
                } else if (initVal->getType()->isPointerTy() && varType->isPointerTy()) {
                    initVal = builder->CreateBitCast(initVal, varType, "init_bitcast");
                } else {
                    throw std::runtime_error("Cannot convert initializer to variable type for: " + node.identifier);
                }
            }
        } else {
            // No initializer - create a default value (0 for numbers, nullptr for pointers)
            if (varType->isIntegerTy()) {
                initVal = llvm::ConstantInt::get(varType, 0);
            } else if (varType->isFloatingPointTy()) {
                initVal = llvm::ConstantFP::get(varType, 0.0);
            } else if (varType->isPointerTy()) {
                initVal = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(varType));
            } else {
                throw std::runtime_error("Unsupported type for uninitialized variable: " + node.identifier);
            }
        }

        // Store the SSA value directly - no alloca needed
        symbols[node.identifier] = initVal;
        return initVal;
    }

    llvm::Value* IR::variableAssignment(const visitor::nodes::VariableDeclarationNode& node) {
        const auto it = symbols.find(node.identifier);
        if (it == symbols.end())
            throw std::runtime_error("Assign to undefined variable: " + node.identifier);

        llvm::Value* currentVal = it->second;
        llvm::Type* varType = currentVal->getType();

        llvm::Value* rhs = expression(node.value);
        if (!rhs)
            throw std::runtime_error("Variable assignment RHS produced null");

        // Type conversion (same logic as declaration)
        if (rhs->getType() != varType) {
            if (rhs->getType()->isIntegerTy() && varType->isFloatingPointTy()) {
                rhs = rhs->getType()->getIntegerBitWidth() == 1 ? builder->CreateUIToFP(rhs, varType, "assign_bool_to_fp") : builder->CreateSIToFP(rhs, varType, "assign_int_to_fp");
            } else if (rhs->getType()->isFloatingPointTy() && varType->isIntegerTy()) {
                rhs = builder->CreateFPToSI(rhs, varType, "assign_fp_to_int");
            } else if (rhs->getType()->isIntegerTy() && varType->isIntegerTy()) {
                const auto* Rit = llvm::cast<llvm::IntegerType>(rhs->getType());
                auto* Vt = llvm::cast<llvm::IntegerType>(varType);

                if (Rit->getBitWidth() < Vt->getBitWidth()) {
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

} // namespace cromio::core::ir