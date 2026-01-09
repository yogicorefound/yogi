//
// Created by Brayhan De Aza on 12/4/25.
//

#include "ExpressionVisitor.h"
#include <visitors/nodes/nodes.h>

#include <cmath>
#include <stdexcept>

namespace yogi::visitor {
    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        const auto expression = std::any_cast<nodes::BinaryExpressionNode>(visit(ctx->additiveExpression()));

        if (expression.resultType == "float") {
            return nodes::FloatLiteralNode(expression.value, expression.start, expression.end);
        }

        if (expression.resultType == "int") {
            return nodes::IntegerLiteralNode(expression.value, expression.start, expression.end);
        }

        if (expression.resultType == "str") {
            return nodes::StringLiteralNode(expression.value, expression.start, expression.end);
        }

        return expression;
    }

    std::any ExpressionVisitor::visitAdditiveExpression(Grammar::AdditiveExpressionContext* ctx) {
        std::any result = visit(ctx->multiplicativeExpression(0));

        for (size_t i = 1; i < ctx->multiplicativeExpression().size(); ++i) {
            std::any rhsAny = visit(ctx->multiplicativeExpression(i));
            const auto [lValue, lType] = extract(result);
            const auto [rValue, rType] = extract(rhsAny);

            std::string op = ctx->children[2 * i - 1]->getText();

            // STRING CONCATENATION
            if (op == "+" && lType == "str" && rType == "str") {
                result = nodes::BinaryExpressionNode(result, rhsAny, "+", lValue + rValue, "str", {}, {});
                continue;
            }

            // NUMERIC
            if ((lType == "int" || lType == "float") && (rType == "int" || rType == "float")) {
                double l = std::stod(lValue);
                double r = std::stod(rValue);
                double out = op == "+" ? l + r : l - r;

                std::string finalType = lType == "float" || rType == "float" ? "float" : "int";

                result = nodes::BinaryExpressionNode(result, rhsAny, op, std::to_string(out), finalType, {}, {});
                continue;
            }

            throw std::runtime_error("Invalid operands for operator '" + op + "'");
        }

        return result;
    }

    std::any ExpressionVisitor::visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext* ctx) {
        std::any result = visit(ctx->powerExpression(0));

        for (size_t i = 1; i < ctx->powerExpression().size(); ++i) {
            std::any rhsAny = visit(ctx->powerExpression(i));
            const auto [lValue, lType] = extract(result);
            const auto [rValue, rType] = extract(rhsAny);

            std::string op = ctx->children[2 * i - 1]->getText();

            double l = std::stod(lValue);
            double r = std::stod(rValue);

            double out;
            if (op == "*")
                out = l * r;
            else if (op == "/") {
                if (r == 0)
                    throw std::runtime_error("Division by zero");
                out = l / r;
            } else {
                if (r == 0)
                    throw std::runtime_error("Modulo by zero");
                out = std::fmod(l, r);
            }

            std::string finalType = op == "/" || lType == "float" || rType == "float" ? "float" : "int";

            result = nodes::BinaryExpressionNode(result, rhsAny, op, std::to_string(out), finalType, {}, {});
        }

        return result;
    }

    std::any ExpressionVisitor::visitPowerExpression(Grammar::PowerExpressionContext* ctx) {
        std::any left = visit(ctx->unaryExpression());

        if (!ctx->powerExpression())
            return left;

        const std::any right = visit(ctx->powerExpression());
        const auto [lValue, lType] = extract(left);
        const auto [rValue, rType] = extract(right);

        const double base = std::stod(lValue);
        const double exp = std::stod(rValue);
        const double out = std::pow(base, exp);

        const std::string finalType = lType == "float" || rType == "float" || exp < 0 || std::floor(exp) != exp ? "float" : "int";

        return nodes::BinaryExpressionNode(left, right, "**", std::to_string(out), finalType, {}, {});
    }

    std::any ExpressionVisitor::visitUnaryExpression(Grammar::UnaryExpressionContext* ctx) {
        std::any valueAny = visit(ctx->primaryExpression());
        if (!ctx->PLUS() && !ctx->MINUS())
            return valueAny;

        auto [value, type] = extract(valueAny);
        if (type != "int" && type != "float")
            throw std::runtime_error("Unary operator requires numeric operand");

        double num = std::stod(value);
        if (ctx->MINUS())
            num = -num;

        return nodes::BinaryExpressionNode({}, valueAny, ctx->MINUS() ? "unary-" : "unary+", std::to_string(num), type, {}, {});
    }

    std::any ExpressionVisitor::visitPrimaryExpression(Grammar::PrimaryExpressionContext* ctx) {
        if (ctx->literals())
            return visit(ctx->literals());

        if (ctx->memberExpression())
            return visit(ctx->memberExpression());

        return visit(ctx->expression());
    }

} // namespace yogi::visitor
