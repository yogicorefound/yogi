//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace cromio::core::ir {

    llvm::Value* IR::literal(const std::any& node) {
        if (!node.has_value())
            throw std::runtime_error("Cannot generate code for empty literal");

        try {
            if (node.type() == typeid(visitor::nodes::FloatLiteralNode)) {
                auto n = std::any_cast<visitor::nodes::FloatLiteralNode>(node);
                double val = std::stod(n.value);
                return llvm::ConstantFP::get(builder->getDoubleTy(), val);
            }
            if (node.type() == typeid(visitor::nodes::IntegerLiteralNode)) {
                auto n = std::any_cast<visitor::nodes::IntegerLiteralNode>(node);
                long long val = std::stoll(n.value);
                return llvm::ConstantInt::get(builder->getInt32Ty(), val, true);
            }
            if (node.type() == typeid(visitor::nodes::BooleanLiteralNode)) {
                auto n = std::any_cast<visitor::nodes::BooleanLiteralNode>(node);
                int val = n.value == "1" ? 1 : 0;
                return llvm::ConstantInt::get(builder->getInt1Ty(), val);
            }
            if (node.type() == typeid(visitor::nodes::NoneLiteralNode)) {
                return llvm::ConstantInt::get(builder->getInt8Ty(), 0);
            }
            if (node.type() == typeid(visitor::nodes::StringLiteralNode)) {
                auto n = std::any_cast<visitor::nodes::StringLiteralNode>(node);
                return builder->CreateGlobalString(n.value, "str");
            }
            if (node.type() == typeid(visitor::nodes::IdentifierLiteral)) {
                auto n = std::any_cast<visitor::nodes::IdentifierLiteral>(node);
                auto it = symbols.find(n.value);
                if (it == symbols.end())
                    throw std::runtime_error("Undefined identifier: " + n.value);
                llvm::Value* alloc = it->second;
                return builder->CreateLoad(alloc->getType(), alloc, n.value + ".load");
            }
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Literal generation failed: " + std::string(e.what()));
        }

        throw std::runtime_error("Unknown literal type");
    }

} // namespace cromio::core::ir