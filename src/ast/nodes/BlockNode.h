//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"
#include "StatementNode.h"

namespace cromio::visitor::nodes {
    // Block Node (holds multiple statements)
    struct BlockNode : BaseNode {
        std::vector<StatementNode> statements;  // List of statements

        explicit BlockNode(
            const Position start,
            const Position end
        ) : BaseNode(Kind::BLOCK, start, end) {}

        void addStatement(StatementNode stmt) {
            statements.push_back(std::move(stmt));
        }
    };

} // namespace cromio::visitor::nodes

