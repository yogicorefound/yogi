//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"
#include "StatementNode.h"

namespace cromio::visitor::nodes {
    // Array Element (for array initialization)
    struct ArrayElementNode : BaseNode {
        std::any value;  // Can be any literal, expression, or nested array

        explicit ArrayElementNode(
            std::any val,
            const Position start,
            const Position end
        ) : BaseNode(Kind::ARRAY_ELEMENT, start, end),
            value(std::move(val)) {}
    };

    // Array Declaration Statement
    struct ArrayDeclarationNode : BaseNode {
        std::string identifier;           // Array name
        std::string elementType;          // Type of elements: "int", "float", "str", etc.
        std::vector<ArrayElementNode> elements;  // Array elements
        size_t size;                      // Number of elements

        explicit ArrayDeclarationNode(
            const std::string& id,
            const std::string& elemType,
            const Position start,
            const Position end
        ) : BaseNode(Kind::ARRAY_DECLARATION, start, end),
            identifier(id),
            elementType(elemType),
            size(0) {}
    };


} // namespace cromio::visitor::nodes
