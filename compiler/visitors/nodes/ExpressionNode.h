//
// Created by Brayhan De Aza on 12/10/25.
// CLEAN AST VERSION (NO EVALUATION)
//

#pragma once

#include <utility>
#include <any>
#include <vector>

#include "BaseNode.h"
#include "LiteralNode.h"

namespace yogi::visitor::nodes {

    // --------------------------------------------------------
    // Binary Expression (PURE AST)
    // --------------------------------------------------------
    struct BinaryExpressionNode : BaseNode {
        std::any left;     // expression or literal
        std::any right;    // expression or literal
        std::string op;    // + - * / % etc.

        explicit BinaryExpressionNode(
            std::any l,
            std::any r,
            std::string operation,
            const Position start,
            const Position end
        )
        : BaseNode(Kind::BINARY_EXPRESSION, start, end),
          left(std::move(l)),
          right(std::move(r)),
          op(std::move(operation)) {}
    };

    // --------------------------------------------------------
    // Concatenation Expression (PURE AST)
    // --------------------------------------------------------
    struct ConcatenationExpressionNode : BaseNode {
        StringLiteralNode value;
        std::vector<StringLiteralNode> literals;

        explicit ConcatenationExpressionNode(
            StringLiteralNode value,
            std::vector<StringLiteralNode> literals,
            const Position start,
            const Position end
        )
        : BaseNode(Kind::CONCATENATION_EXPRESSION, start, end),
          value(std::move(value)),
          literals(std::move(literals)) {}
    };

    // --------------------------------------------------------
    // Unary Expression (PURE AST)
    // --------------------------------------------------------
    struct UnaryExpressionNode : BaseNode {
        std::string op;
        std::any value;

        UnaryExpressionNode(
            std::string op,
            std::any value,
            const Position start,
            const Position end
        )
        : BaseNode(Kind::UNARY_EXPRESSION, start, end),
          op(std::move(op)),
          value(std::move(value)) {}
    };

    // --------------------------------------------------------
    // Ternary Expression (PURE AST)
    // --------------------------------------------------------
    struct TernaryExpressionNode : BaseNode {
        std::any condition;
        std::any trueExpr;
        std::any falseExpr;

        TernaryExpressionNode(
            std::any condition,
            std::any trueExpr,
            std::any falseExpr,
            const Position start,
            const Position end
        )
        : BaseNode(Kind::TERNARY_EXPRESSION, start, end),
          condition(std::move(condition)),
          trueExpr(std::move(trueExpr)),
          falseExpr(std::move(falseExpr)) {}
    };

} // namespace yogi::visitor::nodes