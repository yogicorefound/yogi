//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace cromio::visitor::nodes {
    struct BinaryExpressionNode : BaseNode {
        std::any left; // Can be any literal or expression node
        std::any right; // Can be any literal or expression node
        std::string op; // Operator: +, -, *, /, %
        std::string value; // Computed result as string
        std::string resultType; // Result type: "int", "float", "error"

        explicit BinaryExpressionNode(std::any l, std::any r, const std::string& operation, const std::string& v, const std::string& resType, const Position start, const Position end) : BaseNode(Kind::BINARY_EXPRESSION, start, end), left(std::move(l)), right(std::move(r)), op(operation), value(v), resultType(resType) {}
    };

} // namespace cromio::visitor::nodes
