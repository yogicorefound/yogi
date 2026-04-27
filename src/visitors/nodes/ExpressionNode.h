//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <utility>

#include "BaseNode.h"
#include "LiteralNode.h"
#include <any>


namespace yogi::visitor::nodes {
    struct BinaryExpressionNode : BaseNode {
        std::any left; // Can be any literal or expression node
        std::any right; // Can be any literal or expression node
        std::string op; // Operator: +, -, *, /, %
        std::string value; // Computed result as string
        std::string resultType; // Result type: "int", "float", "error"

        explicit BinaryExpressionNode(std::any l, std::any r, std::string  operation, std::string  v, std::string  resType, const Position start, const Position end) : BaseNode(Kind::BINARY_EXPRESSION, start, end), left(std::move(l)), right(std::move(r)), op(std::move(operation)), value(std::move(v)), resultType(std::move(resType)) {}
    };

    struct BinaryExpressionLiteralNode : BaseNode {
        std::string value;

        explicit BinaryExpressionLiteralNode(std::string  value, const Position start, const Position end) : BaseNode(Kind::BINARY_EXPRESSION, start, end), value(std::move(value)) {}
    };

    struct ConcatenationExpressionNode : BaseNode {
        StringLiteralNode value;
        std::vector<StringLiteralNode> literals; // Computed result as string
        std::string resultType = "str";

        explicit ConcatenationExpressionNode(StringLiteralNode value, std::vector<StringLiteralNode> literals, const Position start, const Position end) : BaseNode(Kind::CONCATENATION_EXPRESSION, start, end), value(std::move(value)), literals(std::move(literals)) {}
    };

    struct UnaryExpressionNode {
        std::string op;
        std::any value;

        Position start{};
        Position end{};

        UnaryExpressionNode() = default;
        UnaryExpressionNode(std::string op, std::any value, const Position start, const Position end): op(std::move(op)),value(std::move(value)),start(start),end(end) {}
    };

    struct TernaryExpressionNode {
        std::any condition;
        std::any trueExpr;
        std::any falseExpr;

        std::string value;      // optional (kept for consistency with your current design)
        std::string resultType; // optional placeholder

        Position start{};
        Position end{};

        TernaryExpressionNode() = default;
        TernaryExpressionNode(std::any condition,std::any trueExpr,std::any falseExpr,std::string value,std::string resultType,Position start,Position end): condition(std::move(condition)), trueExpr(std::move(trueExpr)), falseExpr(std::move(falseExpr)), value(std::move(value)), resultType(std::move(resultType)), start(start), end(end) {}
    };



} // namespace yogi::visitor::nodes
