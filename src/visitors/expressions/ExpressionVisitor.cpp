//
// Created by Brayhan De Aza on 12/4/25.
//

#include "ExpressionVisitor.h"
#include <visitors/nodes/nodes.h>

#include <cmath>
#include <functional>
#include <stdexcept>

namespace yogi::visitor {

    using namespace nodes;

    // --------------------------------------------------------
    // Extract helper
    // --------------------------------------------------------
    struct ExtractResult {
        std::string value;
        std::string type;
    };

    std::function<ExtractResult(const std::any&, semantic::Scope*)> extract = [](const std::any& value, semantic::Scope* scope) -> ExtractResult {
        if (value.type() == typeid(IntegerLiteralNode)) {
            auto n = std::any_cast<IntegerLiteralNode>(value);
            return {n.value, "int"};
        }
        if (value.type() == typeid(FloatLiteralNode)) {
            auto n = std::any_cast<FloatLiteralNode>(value);
            return {n.value, "float"};
        }
        if (value.type() == typeid(StringLiteralNode)) {
            auto n = std::any_cast<StringLiteralNode>(value);
            return {n.value, "str"};
        }
        if (value.type() == typeid(BooleanLiteralNode)) {
            auto n = std::any_cast<BooleanLiteralNode>(value);
            return {n.value, "bool"};
        }
        if (value.type() == typeid(IdentifierLiteral)) {
            auto id = std::any_cast<IdentifierLiteral>(value);
            if (!scope)
                throw std::runtime_error("No scope for identifier");
            auto varOpt = scope->lookupVariable(id.value);
            if (!varOpt.has_value())
                throw std::runtime_error("Variable '" + id.value + "' not declared");
            return extract(varOpt.value()->value, scope);
        }
        throw std::runtime_error("Unsupported operand type in extract");
    };

    // --------------------------------------------------------
    // Expression
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        return visit(ctx->additiveExpression());
    }

    // --------------------------------------------------------
    // Additive: +, - (numeric or string concatenation)
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitAdditiveExpression(Grammar::AdditiveExpressionContext* ctx) {
        std::any result = visit(ctx->multiplicativeExpression(0));

        for (size_t i = 1; i < ctx->multiplicativeExpression().size(); ++i) {
            std::any rhs = visit(ctx->multiplicativeExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            auto lhsVal = extract(result, scope);
            auto rhsVal = extract(rhs, scope);

            // STRING CONCATENATION
            if (op == "+" && lhsVal.type == "str" && rhsVal.type == "str") {
                result = StringLiteralNode(lhsVal.value + rhsVal.value, {}, {});
                continue;
            }

            // NUMERIC OPERATIONS
            if ((lhsVal.type == "int" || lhsVal.type == "float") && (rhsVal.type == "int" || rhsVal.type == "float")) {
                double l = std::stod(lhsVal.value);
                double r = std::stod(rhsVal.value);
                double out = (op == "+") ? l + r : l - r;

                std::string finalType = (lhsVal.type == "float" || rhsVal.type == "float") ? "float" : "int";
                if (finalType == "int")
                    result = IntegerLiteralNode(std::to_string(static_cast<int>(out)), {}, {});
                else
                    result = FloatLiteralNode(std::to_string(out), {}, {});
                continue;
            }

            throw std::runtime_error("Invalid operands for operator '" + op + "'");
        }

        return result;
    }

    // --------------------------------------------------------
    // Multiplicative: *, /, %
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext* ctx) {
        std::any result = visit(ctx->powerExpression(0));

        for (size_t i = 1; i < ctx->powerExpression().size(); ++i) {
            std::any rhs = visit(ctx->powerExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            auto lhsVal = extract(result, scope);
            auto rhsVal = extract(rhs, scope);

            double l = std::stod(lhsVal.value);
            double r = std::stod(rhsVal.value);
            double out = 0.0;

            if (op == "*")
                out = l * r;
            else if (op == "/") {
                if (r == 0)
                    throw std::runtime_error("Division by zero");
                out = l / r;
            } else if (op == "%") {
                if (r == 0)
                    throw std::runtime_error("Modulo by zero");
                out = std::fmod(l, r);
            }

            std::string finalType = (lhsVal.type == "float" || rhsVal.type == "float" || op == "/") ? "float" : "int";

            if (finalType == "int")
                result = IntegerLiteralNode(std::to_string(static_cast<int>(out)), {}, {});
            else
                result = FloatLiteralNode(std::to_string(out), {}, {});
        }

        return result;
    }

    // --------------------------------------------------------
    // Power: **
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitPowerExpression(Grammar::PowerExpressionContext* ctx) {
        std::any left = visit(ctx->unaryExpression());
        if (!ctx->powerExpression())
            return left;

        std::any right = visit(ctx->powerExpression());
        auto lhsVal = extract(left, scope);
        auto rhsVal = extract(right, scope);

        double base = std::stod(lhsVal.value);
        double exp = std::stod(rhsVal.value);
        double out = std::pow(base, exp);

        std::string finalType = (lhsVal.type == "float" || rhsVal.type == "float" || exp < 0 || std::floor(exp) != exp) ? "float" : "int";

        if (finalType == "int")
            return IntegerLiteralNode(std::to_string(static_cast<int>(out)), {}, {});
        else
            return FloatLiteralNode(std::to_string(out), {}, {});
    }

    // --------------------------------------------------------
    // Unary: +, -
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitUnaryExpression(Grammar::UnaryExpressionContext* ctx) {
        std::any value = visit(ctx->primaryExpression());
        if (!ctx->PLUS() && !ctx->MINUS())
            return value;

        auto val = extract(value, scope);
        if (val.type != "int" && val.type != "float")
            throw std::runtime_error("Unary operator requires numeric operand");

        double num = std::stod(val.value);
        if (ctx->MINUS())
            num = -num;

        if (val.type == "int")
            return IntegerLiteralNode(std::to_string(static_cast<int>(num)), {}, {});
        else
            return FloatLiteralNode(std::to_string(num), {}, {});
    }

    // --------------------------------------------------------
    // Primary: literals, identifiers, member, parentheses
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitPrimaryExpression(Grammar::PrimaryExpressionContext* ctx) {
        if (ctx->literals())
            return visit(ctx->literals());
        if (ctx->memberExpression())
            return visit(ctx->memberExpression());
        if (ctx->LPAREN())
            return visit(ctx->expression());

        throw std::runtime_error("Unknown primary expression");
    }

} // namespace yogi::visitor
