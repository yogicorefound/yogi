//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace cromio::core::ir {
    using namespace cromio::visitor::nodes;

    llvm::Value* IR::expression(const std::any& node) {
        if (!node.has_value())
            throw std::runtime_error("Cannot generate code for empty expression");

        // Try literals first
        if (node.type() == typeid(IntegerLiteralNode) || node.type() == typeid(FloatLiteralNode) || node.type() == typeid(BooleanLiteralNode) || node.type() == typeid(NoneLiteralNode) || node.type() == typeid(StringLiteralNode) || node.type() == typeid(IdentifierLiteral)) {
            return literal(node);
        }

        // Binary Expression
        if (node.type() == typeid(BinaryExpressionNode)) {
            const auto n = std::any_cast<BinaryExpressionNode>(node);

            llvm::Value* L = expression(n.left);
            llvm::Value* R = expression(n.right);

            if (!L || !R)
                throw std::runtime_error("Subexpression produced null");

            const std::string& op = n.op;

            // FLOATING POINT OPERATIONS
            if (L->getType()->isDoubleTy() || R->getType()->isDoubleTy()) {
                L = promoteToDouble(L);
                R = promoteToDouble(R);

                if (op == "+")
                    return builder->CreateFAdd(L, R, "fadd");
                if (op == "-")
                    return builder->CreateFSub(L, R, "fsub");
                if (op == "*")
                    return builder->CreateFMul(L, R, "fmul");
                if (op == "/")
                    return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%")
                    return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for double: " + op);
            }

            // FLOAT (32-bit) OPERATIONS
            if (L->getType()->isFloatTy() || R->getType()->isFloatTy()) {
                if (!L->getType()->isFloatingPointTy())
                    L = builder->CreateSIToFP(L, builder->getFloatTy(), "int_to_float");
                if (!R->getType()->isFloatingPointTy())
                    R = builder->CreateSIToFP(R, builder->getFloatTy(), "int_to_float");

                if (op == "+")
                    return builder->CreateFAdd(L, R, "fadd");
                if (op == "-")
                    return builder->CreateFSub(L, R, "fsub");
                if (op == "*")
                    return builder->CreateFMul(L, R, "fmul");
                if (op == "/")
                    return builder->CreateFDiv(L, R, "fdiv");
                if (op == "%")
                    return builder->CreateFRem(L, R, "frem");

                throw std::runtime_error("Unsupported operator for float: " + op);
            }

            // INTEGER OPERATIONS
            if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy()) {
                const auto* Lit = llvm::cast<llvm::IntegerType>(L->getType());
                const auto* Rit = llvm::cast<llvm::IntegerType>(R->getType());
                const unsigned maxBits = std::max(Lit->getBitWidth(), Rit->getBitWidth());

                llvm::IntegerType* opType = builder->getIntNTy(maxBits);

                if (Lit->getBitWidth() < maxBits) {
                    L = Lit->getBitWidth() == 1 ? builder->CreateZExt(L, opType, "zext_l") : builder->CreateSExt(L, opType, "sext_l");
                }
                if (Rit->getBitWidth() < maxBits) {
                    R = Rit->getBitWidth() == 1 ? builder->CreateZExt(R, opType, "zext_r") : builder->CreateSExt(R, opType, "sext_r");
                }

                if (op == "+")
                    return builder->CreateAdd(L, R, "addtmp");
                if (op == "-")
                    return builder->CreateSub(L, R, "subtmp");
                if (op == "*")
                    return builder->CreateMul(L, R, "multmp");
                if (op == "/")
                    return builder->CreateSDiv(L, R, "divtmp");
                if (op == "%")
                    return builder->CreateSRem(L, R, "modtmp");

                throw std::runtime_error("Unsupported integer operator: " + op);
            }

            throw std::runtime_error("Unsupported operand types in Expression");
        }

        throw std::runtime_error("Invalid expression node");
    }

} // namespace cromio::core::ir