//
// Created by Brayhan De Aza on 12/4/25.
//

#include "ExpressionVisitor.h"
#include <ast/nodes/nodes.h>

#include <cmath>
#include <stdexcept>

namespace yogi::visitor {

    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        const auto expression = visitChildren(ctx);
        return visitChildren(ctx);
    }

    std::any ExpressionVisitor::visitBinaryExpression(Grammar::BinaryExpressionContext* ctx) {
        // -------------------------------------------------------
        // (1) Literal → return literal node
        // -------------------------------------------------------
        if (ctx->numberLiterals()) {
            return visit(ctx->numberLiterals());
        }

        if (ctx->identifierLiteral()) {
            return visit(ctx->identifierLiteral());
        }

        // -------------------------------------------------------
        // (2) Parenthesized expression: LPAREN binaryExpression RPAREN
        // -------------------------------------------------------
        if (ctx->LPAREN() && ctx->RPAREN() && ctx->binaryExpression().size() == 1) {
            return visit(ctx->binaryExpression(0));
        }

        // -------------------------------------------------------
        // (3) Binary expression with operator
        // -------------------------------------------------------
        if (ctx->binaryExpression().size() == 2) {
            std::string op;
            if (ctx->PLUS())
                op = "+";
            else if (ctx->MINUS())
                op = "-";
            else if (ctx->MUL())
                op = "*";
            else if (ctx->DIV())
                op = "/";
            else if (ctx->MOD())
                op = "%";

            if (op.empty())
                throw std::runtime_error("Binary expression with 2 operands but no operator found");

            std::any leftResult = visit(ctx->binaryExpression(0));
            std::any rightResult = visit(ctx->binaryExpression(1));

            const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
            const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

            // -------------------------------------------------------
            // Recursive value extraction
            // -------------------------------------------------------
            std::function<std::pair<double, std::string>(const std::any&)> extractedValue;
            extractedValue = [this, &extractedValue](const std::any& result) -> std::pair<double, std::string> {
                if (result.type() == typeid(nodes::IntegerLiteralNode)) {
                    auto node = std::any_cast<nodes::IntegerLiteralNode>(result);
                    return {std::stod(node.value), "int"};
                }
                if (result.type() == typeid(nodes::FloatLiteralNode)) {
                    auto node = std::any_cast<nodes::FloatLiteralNode>(result);
                    return {std::stod(node.value), "float"};
                }
                if (result.type() == typeid(nodes::BooleanLiteralNode)) {
                    auto node = std::any_cast<nodes::BooleanLiteralNode>(result);
                    return {std::stod(node.value), "bool"};
                }
                if (result.type() == typeid(nodes::NoneLiteralNode)) {
                    return {0.0, "none"};
                }
                if (result.type() == typeid(nodes::BinaryExpressionNode)) {
                    auto node = std::any_cast<nodes::BinaryExpressionNode>(result);
                    return {std::stod(node.value), node.resultType};
                }
                if (result.type() == typeid(nodes::IdentifierLiteral)) {
                    auto node = std::any_cast<nodes::IdentifierLiteral>(result);
                    if (!scope)
                        throw std::runtime_error("No scope available for identifier lookup: " + node.value);

                    auto variable = scope->lookupVariable(node.value);
                    if (!variable.has_value())
                        throw std::runtime_error("Variable '" + node.value + "' is not declared");

                    const auto& varNode = variable.value();
                    if (varNode->varType.starts_with("int") || varNode->varType.starts_with("uint")) {
                        if (varNode->kind != nodes::Kind::VARIABLE_DECLARATION)
                            throw std::runtime_error("Identifier '" + node.value + "' must be a variable");

                        return extractedValue(varNode->value);
                    }

                    throwError("Error", "identifier '" + varNode->identifier + "' must be an number", result, source);
                }

                throw std::runtime_error("Unsupported node type in expression");
            };

            double leftValue, rightValue;
            std::string leftType, rightType;
            try {
                auto [lv, lt] = extractedValue(leftResult);
                auto [rv, rt] = extractedValue(rightResult);
                leftValue = lv;
                leftType = lt;
                rightValue = rv;
                rightType = rt;
            } catch (...) {
                return nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
            }

            // -------------------------------------------------------
            // Perform arithmetic
            // -------------------------------------------------------
            double result = 0.0;
            if (op == "+")
                result = leftValue + rightValue;
            else if (op == "-")
                result = leftValue - rightValue;
            else if (op == "*")
                result = leftValue * rightValue;
            else if (op == "/") {
                if (rightValue == 0.0)
                    return nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
                result = leftValue / rightValue;
            } else if (op == "%") {
                if (rightValue == 0.0)
                    return nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
                if (leftValue == static_cast<int>(leftValue) && rightValue == static_cast<int>(rightValue))
                    result = static_cast<int>(leftValue) % static_cast<int>(rightValue);
                else
                    result = std::fmod(leftValue, rightValue);
            }

            // -------------------------------------------------------
            // Determine final data type
            // -------------------------------------------------------
            auto determineType = [](const std::string& mOp, const std::string& mLeftType, const std::string& mRightType) -> std::string {
                if (mLeftType == "float" || mRightType == "float")
                    return "float";
                if (mLeftType == "bool" || mRightType == "bool")
                    return "int";
                if (mLeftType == "none" || mRightType == "none")
                    return "int";
                if (mOp == "%")
                    return "int";
                if (mOp == "/")
                    return "float";
                return "int";
            };
            std::string finalType = determineType(op, leftType, rightType);

            return nodes::BinaryExpressionNode(leftResult, rightResult, op, std::to_string(result), finalType, start, end);
        }

        // -------------------------------------------------------
        // Fallbacks
        // -------------------------------------------------------
        if (!ctx->binaryExpression().empty())
            return visit(ctx->binaryExpression(0));

        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("None", start, end);
    }

    std::any ExpressionVisitor::visitConcatenationExpression(Grammar::ConcatenationExpressionContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        std::string value;
        std::vector<nodes::StringLiteralNode> literals;
        for (const auto expression : ctx->stringLiterals()) {
            if (expression->identifierLiteral()) {
                auto literal = visit(expression->identifierLiteral());
                auto literalNode = std::any_cast<nodes::IdentifierLiteral>(literal);

                auto variable = scope->lookupVariable(literalNode.value);
                if (!variable.has_value()) {
                    throwScopeError("Variable '" + literalNode.value + "' is not declared", literalNode.value, literalNode, source);
                }

                auto varNode = variable.value();
                if (varNode->varType != "str") {
                    throwTypeError(literalNode.value, varNode->varType, literalNode, source);
                }

                auto stringLiteralNode = std::any_cast<nodes::StringLiteralNode>(varNode->value);
                value += stringLiteralNode.value;
                literals.push_back(stringLiteralNode);

            }
            else {
                auto literal = visit(expression);
                auto literalNode = std::any_cast<nodes::StringLiteralNode>(literal);
                value += literalNode.value;
                literals.push_back(literalNode);
            }
        }

        const nodes::StringLiteralNode node(value, start, end);
        return node;
    }

} // namespace yogi::visitor
