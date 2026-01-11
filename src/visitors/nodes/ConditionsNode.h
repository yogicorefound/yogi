//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace yogi::visitor::nodes {
    struct IfStatementNode : BaseNode {
        // Each branch: condition + body
        struct Branch {
            std::any condition; // nullptr for "else"
            std::vector<std::any> body;
        };

        std::vector<Branch> branches; // if + else if + else

        explicit IfStatementNode(const Position start, const Position end) : BaseNode(Kind::IF_STATEMENT, start, end) {}

        // Add a branch (if or else if)
        void addBranch(std::any conditionValue, std::vector<std::any> bodyValue) {
            branches.push_back(Branch{std::move(conditionValue), std::move(bodyValue)});
        }

        // Add the "else" branch (condition is null)
        void addElse(std::vector<std::any> bodyValue) {
            branches.push_back(Branch{std::any(), std::move(bodyValue)});
        }
    };

} // namespace yogi::visitor::nodes