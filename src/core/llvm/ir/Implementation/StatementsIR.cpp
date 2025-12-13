//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace cromio::core::ir {

    llvm::Value* IR::statement(const visitor::nodes::StatementNode& node) {
        llvm::Value* lastVal = nullptr;

        for (const auto& child : node.children) {
            if (!child.has_value())
                continue;

            try {
                if (child.type() == typeid(visitor::nodes::VariableDeclarationNode)) {
                    auto n = std::any_cast<visitor::nodes::VariableDeclarationNode>(child);
                    lastVal = variableDeclaration(n);
                } else if (child.type() == typeid(visitor::nodes::ArrayDeclarationNode)) {
                    auto n = std::any_cast<visitor::nodes::ArrayDeclarationNode>(child);
                    lastVal = arrayDeclaration(n);
                } else {
                    // Default: treat as expression
                    lastVal = expression(child);
                }
            } catch (const std::exception& e) {
                throw std::runtime_error("Statement generation failed: " + std::string(e.what()));
            }
        }

        return lastVal;
    }

} // namespace cromio::core::ir