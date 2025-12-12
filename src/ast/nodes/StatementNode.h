//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <vector>
#include <any>
#include "BaseNode.h"

namespace cromio::visitor::nodes {
    // Statement Node (holds mixed types: expressions, literals, declarations, etc.)
    struct StatementNode : BaseNode {
        std::vector<std::any> children; // Can hold any mix of node types

        explicit StatementNode(const Position start, const Position end)
            : BaseNode(Kind::STATEMENT, start, end) {}

        // Add a single child node
        void addChild(std::any child) {
            children.push_back(std::move(child));
        }

        // Add multiple child nodes
        void addChildren(const std::vector<std::any>& nodes) {
            for (const auto& node : nodes) {
                children.push_back(node);
            }
        }

        // Get number of children
        size_t size() const {
            return children.size();
        }

        // Check if empty
        bool empty() const {
            return children.empty();
        }
    };

} // namespace cromio::visitor::nodes