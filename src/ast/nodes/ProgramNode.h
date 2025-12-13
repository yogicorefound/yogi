//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"
#include "StatementNode.h"

namespace cromio::visitor::nodes {
    // Program Node (root of AST - holds all top-level statements)
    struct ProgramNode : BaseNode {
        std::vector<StatementNode> body;  // All top-level statements

        explicit ProgramNode(
            const Position start,
            const Position end
        ) : BaseNode(Kind::PROGRAM, start, end) {}

        void addStatement(StatementNode stmt) {
            body.push_back(std::move(stmt));
        }
    };

} // namespace cromio::visitor::nodes
