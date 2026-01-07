//
// Created by Brayhan De Aza on 12/13/25.
//

#include <core/llvm/ir/IR.h>

namespace yogi::core::ir {

    llvm::Value* IR::statement(const std::any& node) {
        llvm::Value* lastVal = nullptr;
            try {
                if (node.type() == typeid(visitor::nodes::VariableDeclarationNode)) {
                    const auto n = std::any_cast<visitor::nodes::VariableDeclarationNode>(node);
                    lastVal = variableDeclaration(n);

                } else if (node.type() == typeid(visitor::nodes::ArrayDeclarationNode)) {
                    auto n = std::any_cast<visitor::nodes::ArrayDeclarationNode>(node);
                    lastVal = arrayDeclaration(n);

                } else {
                    // Default: treat as expression
                    lastVal = expression(node);
                }
            } catch (const std::exception& e) {
                throw std::runtime_error("Statement generation failed: " + std::string(e.what()));
            }


        return lastVal;
    }

} // namespace yogi::core::ir