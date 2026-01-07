//
// Created by Brayhan De Aza on 12/4/25.
//

#include "ExpressionVisitor.h"
#include <visitors/nodes/nodes.h>

#include <cmath>
#include <stdexcept>

namespace yogi::visitor {

    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        if (const auto expression = visitChildren(ctx); expression.type() == typeid(nodes::BinaryExpressionNode)) {
            const auto node = std::any_cast<nodes::BinaryExpressionNode>(expression);

            if (node.resultType == "str") {
                return nodes::StringLiteralNode(node.value, node.start, node.end);
            }

            if (node.resultType == "int") {
                return nodes::IntegerLiteralNode(formatFloatNumberDecimal(node.value, -1), node.start, node.end);
            }

            if (node.resultType == "float") {
                return nodes::FloatLiteralNode(node.value, node.start, node.end);
            }
        }

        return visitChildren(ctx);
    }

    std::any ExpressionVisitor::visitBinaryExpression(Grammar::BinaryExpressionContext* ctx) {
        // -------------------------------------------------------
        // (1) literals
        // -------------------------------------------------------
        if (ctx->literals())
            return visit(ctx->literals());

        // -------------------------------------------------------
        // (2) Parenthesized expression
        // -------------------------------------------------------
        if (ctx->LPAREN() && ctx->binaryExpression().size() == 1)
            return visit(ctx->binaryExpression(0));

        // -------------------------------------------------------
        // (3) binaryExpression op binaryExpression
        // -------------------------------------------------------
        if (ctx->binaryExpression().size() == 2) {
            std::string op;
            if (ctx->MUL()) {
                op = "*";
            } else if (ctx->DIV()) {
                op = "/";
            } else if (ctx->MOD()) {
                op = "%";
            } else if (ctx->PLUS()) {
                op = "+";
            } else if (ctx->MINUS()) {
                op = "-";
            }

            std::any leftAny = visit(ctx->binaryExpression(0));
            std::any rightAny = visit(ctx->binaryExpression(1));

            const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
            const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

            // ---------------------------------------------------
            // Recursive extractor (RESOLVES IDENTIFIERS)
            // ---------------------------------------------------
            std::function<std::pair<std::string, std::string>(const std::any&)> extract;

            extract = [&](const std::any& value) -> std::pair<std::string, std::string> {
                if (value.type() == typeid(nodes::IntegerLiteralNode)) {
                    auto n = std::any_cast<nodes::IntegerLiteralNode>(value);
                    return {n.value, "int"};
                }

                if (value.type() == typeid(nodes::FloatLiteralNode)) {
                    auto n = std::any_cast<nodes::FloatLiteralNode>(value);
                    return {n.value, "float"};
                }

                if (value.type() == typeid(nodes::StringLiteralNode)) {
                    auto s = std::any_cast<nodes::StringLiteralNode>(value);
                    return {s.value, "str"};
                }

                if (value.type() == typeid(nodes::BooleanLiteralNode)) {
                    auto b = std::any_cast<nodes::BooleanLiteralNode>(value);
                    return {b.value, "bool"};
                }

                if (value.type() == typeid(nodes::IdentifierLiteral)) {
                    auto id = std::any_cast<nodes::IdentifierLiteral>(value);

                    if (!scope)
                        throw std::runtime_error("No scope for identifier");

                    auto var = scope->lookupVariable(id.value);
                    if (!var.has_value())
                        throw std::runtime_error("Variable '" + id.value + "' not declared");

                    return extract(var.value()->value);
                }

                if (value.type() == typeid(nodes::BinaryExpressionNode)) {
                    auto n = std::any_cast<nodes::BinaryExpressionNode>(value);
                    return {n.value, n.resultType};
                }

                throw std::runtime_error("Unsupported operand");
            };

            std::string lv, lt, rv, rt;
            std::tie(lv, lt) = extract(leftAny);
            std::tie(rv, rt) = extract(rightAny);

            // ---------------------------------------------------
            // STRING CONCATENATION
            // ---------------------------------------------------
            if (op == "+" && lt == "str" && rt == "str") {
                return nodes::BinaryExpressionNode(leftAny, rightAny, op, lv + rv, "str", start, end);
            }

            // ---------------------------------------------------
            // NUMERIC OPERATIONS ONLY
            // ---------------------------------------------------
            const bool leftNumeric = (lt == "int" || lt == "float");
            if (const bool rightNumeric = (rt == "int" || rt == "float"); !leftNumeric || !rightNumeric) {
                if (lt == "str") {
                    throwError("TypeError", "cannot concatenate '" + lt + "' " + op + " '" + rt + "'", ctx, source);
                }

                throwError("TypeError", "Invalid operands for operator '" + op + "'", ctx, source);
            }

            // Safe numeric validation
            auto isNumeric = [](const std::string& s) {
                if (s.empty())
                    return false;
                char* end = nullptr;
                std::strtod(s.c_str(), &end);
                return end != s.c_str() && *end == '\0';
            };

            if (!isNumeric(lv) || !isNumeric(rv)) {
                throwError("TypeError", "Non-numeric value used with operator '" + op + "'", ctx, source);
            }

            double lhs = std::stod(lv);
            double rhs = std::stod(rv);
            double result = 0.0;

            if (op == "+")
                result = lhs + rhs;
            else if (op == "-")
                result = lhs - rhs;
            else if (op == "*")
                result = lhs * rhs;
            else if (op == "/") {
                if (rhs == 0.0)
                    throwError("MathError", "Division by zero", ctx, source);
                result = lhs / rhs;
            } else if (op == "%") {
                if (rhs == 0.0)
                    throwError("MathError", "Modulo by zero", ctx, source);
                result = std::fmod(lhs, rhs);
            }

            std::string finalType = (lt == "float" || rt == "float" || op == "/") ? "float" : "int";

            return nodes::BinaryExpressionNode(leftAny, rightAny, op, std::to_string(result), finalType, start, end);
        }

        // -------------------------------------------------------
        // Fallback
        // -------------------------------------------------------
        return visit(ctx->binaryExpression(0));
    }

    std::any ExpressionVisitor::visitConcatenationExpression(Grammar::ConcatenationExpressionContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        std::string value;
        std::string type = "str";
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

            } else {
                if (auto literal = visit(expression); literal.type() == typeid(nodes::RegexLiteralNode)) {
                    auto literalNode = std::any_cast<nodes::RegexLiteralNode>(literal);
                    auto stringNode = nodes::StringLiteralNode(literalNode.value, literalNode.start, literalNode.end);

                    type = "regex";
                    value += literalNode.value;
                    literals.push_back(stringNode);
                } else {
                    auto literalNode = std::any_cast<nodes::StringLiteralNode>(literal);

                    value += literalNode.value;
                    literals.push_back(literalNode);
                }
            }
        }

        if (type == "regex") {
            const nodes::RegexLiteralNode node(value, start, end);
            return node;
        }

        const nodes::StringLiteralNode node(value, start, end);
        return node;
    }

} // namespace yogi::visitor
