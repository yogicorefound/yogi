//
// Created by Brayhan De Aza on 12/4/25.
//

#include "ExpressionVisitor.h"
#include <ast/nodes/nodes.h>

#include <cmath>
#include <stdexcept>

namespace cromio::visitor {

    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        if (ctx->binaryExpression()) {
            return visit(ctx->binaryExpression());
        }

        if (ctx->concatenationExpression()) {
            return visit(ctx->concatenationExpression());
        }

        // Return None literal as fallback
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("None", start, end);
    }

    std::any ExpressionVisitor::visitBinaryExpression(Grammar::BinaryExpressionContext* ctx) {
        // -------------------------------------------------------
        // (1) Literal → return literal node
        // -------------------------------------------------------
        if (ctx->numberLiterals()) {
            return visit(ctx->numberLiterals());
        }

        // -------------------------------------------------------
        // (2) Detect operator
        // -------------------------------------------------------
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

        // -------------------------------------------------------
        // (3) Parenthesized expression
        // -------------------------------------------------------
        if (ctx->binaryExpression().size() == 1 && op.empty()) {
            return visit(ctx->binaryExpression(0));
        }

        // -------------------------------------------------------
        // (4) Binary expression
        // -------------------------------------------------------
        if (!op.empty() && ctx->binaryExpression().size() >= 2) {
            std::any leftResult = visit(ctx->binaryExpression(0));
            std::any rightResult = visit(ctx->binaryExpression(1));

            const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
            const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

            std::function<std::pair<double, std::string>(const std::any&)> extractedValue;
            extractedValue = [this, &extractedValue](const std::any& result) -> std::pair<double, std::string> {
                try {
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

                        // Look up identifier value from symbol table
                        if (!scope) {
                            throw std::runtime_error("No scope available for identifier lookup: " + node.value);
                        }

                        const std::string identifier = node.value;
                        if (const auto variable = scope->lookup(identifier); variable.has_value()) {
                            const auto varNode = variable.value();
                            return extractedValue(varNode->value);
                        }

                        // Variable not found in scope
                        throw std::runtime_error("Variable '" + identifier + "' is not declared");
                    }
                } catch (const std::exception& _) {
                    throw std::runtime_error("Cannot extract numeric value");
                }
                throw std::runtime_error("Unsupported node type in expression");
            };

            double leftValue, rightValue;
            std::string leftType, rightType;

            try {
                auto [lv, lt] = extractedValue(leftResult);
                auto [rv, rt] = extractedValue(rightResult);
                leftValue = lv;
                rightValue = rv;
                leftType = lt;
                rightType = rt;
            } catch (const std::exception& _) {
                // Return error node
                auto errorNode = nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
                return errorNode;
            }

            // -------------------------------------------------------
            // (5) Perform arithmetic
            // -------------------------------------------------------
            double result = 0.0;

            if (op == "+")
                result = leftValue + rightValue;
            else if (op == "-")
                result = leftValue - rightValue;
            else if (op == "*")
                result = leftValue * rightValue;
            else if (op == "/") {
                if (rightValue == 0.0) {
                    auto errorNode = nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
                    return errorNode;
                }
                result = leftValue / rightValue;
            } else if (op == "%") {
                if (rightValue == 0.0) {
                    auto errorNode = nodes::BinaryExpressionNode(leftResult, rightResult, op, "0.0", "error", start, end);
                    return errorNode;
                }
                if (leftValue == static_cast<int>(leftValue) && rightValue == static_cast<int>(rightValue))
                    result = static_cast<int>(leftValue) % static_cast<int>(rightValue);
                else
                    result = std::fmod(leftValue, rightValue);
            }

            // -------------------------------------------------------
            // (6) Determine final data type
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

            // -------------------------------------------------------
            // (7) Create and return BinaryExpressionNode
            // -------------------------------------------------------
            auto node = nodes::BinaryExpressionNode(leftResult, rightResult, op, std::to_string(result), finalType, start, end);
            // auto literalExpressionNode = nodes::BinaryExpressionLiteralNode(std::to_string(node.value), start, end);
            //
            // std::cout << "node.value " << std::to_string(result)<< std::endl;

            return node;
        }

        // -------------------------------------------------------
        // (8) Fallback
        // -------------------------------------------------------
        if (!ctx->binaryExpression().empty())
            return visit(ctx->binaryExpression(0));

        // Return None literal as fallback
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

                auto variable = scope->lookup(literalNode.value);
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
                std::cout << "literalNode.value " << literalNode.value << std::endl;

            } else {
                auto literal = visit(expression);
                auto literalNode = std::any_cast<nodes::StringLiteralNode>(literal);
                value += literalNode.value;
                literals.push_back(literalNode);
            }
        }

        const nodes::StringLiteralNode node(value, start, end);
        return node;
    }

} // namespace cromio::visitor
