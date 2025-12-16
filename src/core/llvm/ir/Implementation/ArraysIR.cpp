//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace cromio::core::ir {

    llvm::Value* IR::arrayDeclaration(const visitor::nodes::ArrayDeclarationNode& node) {
        llvm::Type* elementType = mapDataType(node.type);
        const size_t arraySize = std::stoull(node.size);

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
            llvm::Value* gep = builder->CreateGEP(arrType, allocaInst, {builder->getInt32(0), builder->getInt32(idx)}, node.identifier + "_idx" + std::to_string(idx));

            // Type conversion if necessary
            if (val->getType() != elementType) {
                if (val->getType()->isIntegerTy(1) && elementType->isIntegerTy() && elementType->getIntegerBitWidth() > 1) {
                    val = builder->CreateZExt(val, elementType, "bool_to_int");
                } else if (val->getType()->isIntegerTy() && val->getType()->getIntegerBitWidth() > 1 && elementType->isIntegerTy(1)) {
                    val = builder->CreateICmpNE(val, llvm::ConstantInt::get(val->getType(), 0), "int_to_bool");
                } else if (val->getType()->isIntegerTy() && elementType->isIntegerTy()) {
                    const auto* vIt = llvm::cast<llvm::IntegerType>(val->getType());

                    if (const auto* tIt = llvm::cast<llvm::IntegerType>(elementType); vIt->getBitWidth() < tIt->getBitWidth())
                        val = builder->CreateSExt(val, elementType, "elem_sext");
                    else if (vIt->getBitWidth() > tIt->getBitWidth())
                        val = builder->CreateTrunc(val, elementType, "elem_trunc");
                } else if (val->getType()->isIntegerTy() && elementType->isFloatingPointTy())
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

} // namespace cromio::core::ir