//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"
#include "StatementNode.h"

namespace cromio::visitor::nodes {
    // Array Element (for array initialization)
    struct ArrayElementNode : BaseNode {
        std::string type;
        std::any value; // Can be any literal, expression, or nested array

        explicit ArrayElementNode(std::any value, std::string type, const Position start, const Position end) : BaseNode(Kind::ARRAY_ELEMENT, start, end), type(std::move(type)), value(std::move(value)) {}
    };

    // Array Declaration Statement
    struct ArrayDeclarationNode : BaseNode {
        std::string identifier; // Array name
        std::string type; // Type of elements: "int", "float", "str", etc.
        std::string size; // Number of elements
        bool isConstant;
        std::vector<ArrayElementNode> elements; // Array elements

        explicit ArrayDeclarationNode(const std::string& identifier, const std::string& type, bool isConstant, std::string size, std::vector<ArrayElementNode> elements, const Position start, const Position end) : BaseNode(Kind::ARRAY_DECLARATION, start, end), identifier(identifier), type(type), isConstant(isConstant), size(size), elements(std::move(elements)) {}
    };

} // namespace cromio::visitor::nodes
