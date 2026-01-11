// Created by Brayhan De Aza on 12/4/25.

#include <boost/multiprecision/cpp_int.hpp>
#ifdef EOF
#undef EOF
#endif
#include <visitors/nodes/nodes.h>
#include "ExpressionVisitor.h"

namespace yogi::visitor {

    using namespace nodes;
    using BigInt = boost::multiprecision::int128_t; // or cpp_int for arbitrary size

    // --------------------------------------------------------
    // Extract helper
    // --------------------------------------------------------
    struct ExtractResult {
        std::string value;
        std::string type; // "int", "float", "str", "bool"
    };

    std::function<ExtractResult(const std::any&, const semantic::Scope*, const std::string&)> extract = [](const std::any& value, const semantic::Scope* scope, const std::string& source) -> ExtractResult {
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
        if (value.type() == typeid(RegexLiteralNode)) {
            auto n = std::any_cast<RegexLiteralNode>(value);
            return {n.value, "regex"};
        }
        if (value.type() == typeid(BooleanLiteralNode)) {
            auto n = std::any_cast<BooleanLiteralNode>(value);
            return {n.value, "bool"};
        }
        if (value.type() == typeid(IdentifierLiteral)) {
            auto id = std::any_cast<IdentifierLiteral>(value);
            if (!scope)
                utils::Errors::throwError("Error", "No scope for identifier", value, source);

            if (const auto varOpt = scope->lookupVariable(id.value); varOpt.has_value())
                return extract(varOpt.value()->value, scope, source);

            utils::Errors::throwError("Error", "Variable '" + id.value + "' not declared", value, source);
        }

        utils::Errors::throwError("Error", "Unsupported operand type in extract", value, source);
        return {};
    };

    bool isTruthy(const std::any& value, const semantic::Scope* scope, const std::string& source) {
        const auto [v, t] = extract(value, scope, source);

        if (t == "bool")
            return v == "1";
        if (t == "int")
            return BigInt(v) != 0;
        if (t == "float")
            return std::stod(v) != 0.0;
        if (t == "str")
            return !v.empty();

        return false;
    }

    // --------------------------------------------------------
    // Expression
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext* ctx) {
        return visit(ctx->conditionalExpression());
    }

    // --------------------------------------------------------
    // Conditional ternary: condition ? expr1 : expr2
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitConditionalExpression(Grammar::ConditionalExpressionContext* ctx) {
        std::any condition = visit(ctx->logicalOrExpression());

        const bool cond = isTruthy(condition, scope, source);

        if (ctx->expression().size() != 2) {
            return condition;
        }

        if (cond) {
            return visit(ctx->expression(0));
        }

        return visit(ctx->expression(1));
    }

    std::any ExpressionVisitor::visitLogicalOrExpression(Grammar::LogicalOrExpressionContext* ctx) {
        std::any left = visit(ctx->logicalAndExpression(0));

        for (size_t i = 1; i < ctx->logicalAndExpression().size(); ++i) {
            if (isTruthy(left, scope, source)) {
                // short-circuit → devuelve el valor real, no solo true
                return left;
            }

            const std::any right = visit(ctx->logicalAndExpression(i));
            left = right;
        }

        return left;
    }

    std::any ExpressionVisitor::visitLogicalAndExpression(Grammar::LogicalAndExpressionContext* ctx) {
        std::any left = visit(ctx->bitwiseOrExpression(0));

        for (size_t i = 1; i < ctx->bitwiseOrExpression().size(); ++i) {
            if (!isTruthy(left, scope, source)) {
                // short-circuit → devuelve el valor real
                return left;
            }

            const std::any right = visit(ctx->bitwiseOrExpression(i));
            left = right;
        }

        return left;
    }

    // --------------------------------------------------------
    // Relational: >, <, >=, <=, ==, !=
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitRelationalExpression(Grammar::RelationalExpressionContext* ctx) {
        std::any left = visit(ctx->shiftExpression(0));

        for (size_t i = 1; i < ctx->shiftExpression().size(); ++i) {
            std::any right = visit(ctx->shiftExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            const auto [lValue, lType] = extract(left, scope, source);
            const auto [rValue, rType] = extract(right, scope, source);

            // Allow string comparison if both operands are strings
            if (lType != rType && !(lType == "int" && rType == "float") && !(lType == "float" && rType == "int")) {
                throwError("Cannot compare different types: " + lType + " " + op + " " + rType, left, source);
            }

            bool result = false;

            if (lType == "int" || lType == "float") {
                const double l = lType == "int" ? std::stoll(lValue) : std::stod(lValue);
                const double r = rType == "int" ? std::stoll(rValue) : std::stod(rValue);

                if (op == ">")
                    result = l > r;
                else if (op == "<")
                    result = l < r;
                else if (op == ">=")
                    result = l >= r;
                else if (op == "<=")
                    result = l <= r;
                else if (op == "==")
                    result = l == r;
                else if (op == "!=")
                    result = l != r;

            } else if (lType == "str") { // Strings
                if (op == "==")
                    result = lValue == rValue;
                else if (op == "!=")
                    result = lValue != rValue;
                else if (op == ">")
                    result = lValue > rValue; // lexicographical
                else if (op == "<")
                    result = lValue < rValue;
                else if (op == ">=")
                    result = lValue >= rValue;
                else if (op == "<=")
                    result = lValue <= rValue;
                else
                    throwError("Invalid string comparison operator: " + op, left, source);

            } else {
                throwError("Unsupported operand type for relational operator: " + lType, left, source);
            }

            left = BooleanLiteralNode(result ? "1" : "0", {}, {});
        }

        return left;
    }

    std::any ExpressionVisitor::visitEqualityExpression(Grammar::EqualityExpressionContext* ctx) {
        std::any left = visit(ctx->relationalExpression(0));

        for (size_t i = 1; i < ctx->relationalExpression().size(); ++i) {
            std::any right = visit(ctx->relationalExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            const auto [lValue, lType] = extract(left, scope, source);
            const auto [rValue, rType] = extract(right, scope, source);

            bool result = false;

            if (lType == "int" && rType == "int") {
                BigInt l(lValue), r(rValue);
                result = op == "==" ? l == r : l != r;
            } else if (lType == "float" || rType == "float") {
                double l = std::stod(lValue);
                double r = std::stod(rValue);
                result = op == "==" ? l == r : l != r;
            } else if (lType == "str" && rType == "str") {
                result = op == "==" ? lValue == rValue : lValue != rValue;
            } else {
                throwError("Invalid operands for equality operator", left, source);
            }

            left = BooleanLiteralNode(result ? "1" : "0", {}, {});
        }

        return left;
    }

    std::any ExpressionVisitor::visitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext* ctx) {
        std::any result = visit(ctx->equalityExpression(0));

        for (size_t i = 1; i < ctx->equalityExpression().size(); ++i) {
            std::any rhs = visit(ctx->equalityExpression(i));

            const auto [lValue, lType] = extract(result, scope, source);
            const auto [rValue, rType] = extract(rhs, scope, source);

            if (lType != "int" || rType != "int")
                throwError("Bitwise '&' requires integer operands", result, source);

            BigInt l(lValue);
            BigInt r(rValue);

            result = IntegerLiteralNode((l & r).str(), {}, {});
        }

        return result;
    }

    std::any ExpressionVisitor::visitShiftExpression(Grammar::ShiftExpressionContext* ctx) {
        std::any result = visit(ctx->additiveExpression(0));

        for (size_t i = 1; i < ctx->additiveExpression().size(); ++i) {
            std::any rhs = visit(ctx->additiveExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            const auto [lValue, lType] = extract(result, scope, source);
            const auto [rValue, rType] = extract(rhs, scope, source);

            if (lType != "int" || rType != "int")
                throwError("Shift operators require integer operands", result, source);

            BigInt l(lValue);
            BigInt r(rValue);

            if (r < 0)
                throwError("Negative shift count", result, source);

            if (op == "<<")
                result = IntegerLiteralNode((l << r.convert_to<unsigned>()).str(), {}, {});
            else
                result = IntegerLiteralNode((l >> r.convert_to<unsigned>()).str(), {}, {});
        }

        return result;
    }

    // --------------------------------------------------------
    // Bitwise: XOR
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext* ctx) {
        std::any result = visit(ctx->bitwiseAndExpression(0));

        for (size_t i = 1; i < ctx->bitwiseAndExpression().size(); ++i) {
            std::any rhs = visit(ctx->bitwiseAndExpression(i));

            const auto [lValue, lType] = extract(result, scope, source);
            const auto [rValue, rType] = extract(rhs, scope, source);

            if (lType != "int" || rType != "int")
                throwError("Bitwise '^' requires integer operands", result, source);

            BigInt l(lValue);
            BigInt r(rValue);

            result = IntegerLiteralNode((l ^ r).str(), {}, {});
        }

        return result;
    }

    // --------------------------------------------------------
    // Bitwise OR: |
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext* ctx) {
        std::any result = visit(ctx->bitwiseXorExpression(0));

        for (size_t i = 1; i < ctx->bitwiseXorExpression().size(); ++i) {
            std::any rhs = visit(ctx->bitwiseXorExpression(i));

            const auto [lValue, lType] = extract(result, scope, source);
            const auto [rValue, rType] = extract(rhs, scope, source);

            if (lType != "int" || rType != "int")
                throwError("Bitwise '|' requires integer operands", result, source);

            BigInt l(lValue);
            BigInt r(rValue);
            result = IntegerLiteralNode((l | r).str(), {}, {});
        }

        return result;
    }

    // --------------------------------------------------------
    // Additive: +, -
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitAdditiveExpression(Grammar::AdditiveExpressionContext* ctx) {
        std::any result = visit(ctx->multiplicativeExpression(0));

        for (size_t i = 1; i < ctx->multiplicativeExpression().size(); ++i) {
            std::any rhs = visit(ctx->multiplicativeExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            const auto [lValue, lType] = extract(result, scope, source);
            const auto [rValue, rType] = extract(rhs, scope, source);

            // STRING CONCAT
            if (op == "+" && lType == "str" && rType == "str") {
                result = StringLiteralNode(lValue + rValue, {}, {});
                continue;
            }

            // INTEGER or FLOAT
            if ((lType == "int" || lType == "float") && (rType == "int" || rType == "float")) {
                // Integer operation → BigInt
                if (lType == "int" && rType == "int") {
                    BigInt l(lValue);
                    BigInt r(rValue);
                    BigInt out = op == "+" ? l + r : l - r;
                    result = IntegerLiteralNode(out.str(), {}, {});

                } else {
                    double l = lType == "int" ? std::stoll(lValue) : std::stod(lValue);
                    double r = rType == "int" ? std::stoll(rValue) : std::stod(rValue);
                    double out = op == "+" ? l + r : l - r;
                    result = FloatLiteralNode(std::to_string(out), {}, {});
                }
                continue;
            }

            throwError("Invalid operands for operator '" + op + "'", result, source);
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

            const auto [lValue, lType] = extract(result, scope, source);

            if (const auto [rValue, rType] = extract(rhs, scope, source); lType == "int" && rType == "int" && op != "/") {
                BigInt l(lValue);
                BigInt r(rValue);
                BigInt out;

                if (op == "*")
                    out = l * r;

                else if (op == "%") {
                    if (r == 0)
                        throwError("Modulo by zero", result, source);
                    out = l % r;
                }
                result = IntegerLiteralNode(out.str(), {}, {});

            } else { // float computation
                double l = lType == "int" ? std::stoll(lValue) : std::stod(lValue);
                double r = rType == "int" ? std::stoll(rValue) : std::stod(rValue);
                double out = 0;

                if (op == "*")
                    out = l * r;

                else if (op == "/") {
                    if (r == 0)
                        throwError("Division by zero", result, source);

                    out = l / r;

                } else if (op == "%") {
                    if (r == 0) {
                        throwError("Modulo by zero", result, source);
                    }

                    out = std::fmod(l, r);
                }

                result = FloatLiteralNode(std::to_string(out), {}, {});
            }
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

        const std::any right = visit(ctx->powerExpression());
        const auto [lValue, lType] = extract(left, scope, source);
        const auto [rValue, rType] = extract(right, scope, source);

        // INTEGER ** INTEGER using BigInt
        if (lType == "int" && rType == "int") {
            const BigInt base(lValue);
            const BigInt exp(rValue);
            if (exp < 0) { // negative → float
                const double out = std::pow(base.convert_to<double>(), exp.convert_to<double>());
                return FloatLiteralNode(std::to_string(out), {}, {});
            }

            BigInt out = 1;
            for (BigInt i = 0; i < exp; ++i)
                out *= base;
            return IntegerLiteralNode(out.str(), {}, {});
        }

        const double base = lType == "int" ? std::stoll(lValue) : std::stod(lValue);
        const double exp = rType == "int" ? std::stoll(rValue) : std::stod(rValue);
        const double out = std::pow(base, exp);

        return FloatLiteralNode(std::to_string(out), {}, {});
    }

    // --------------------------------------------------------
    // Unary: +, -, !, ~
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitUnaryExpression(Grammar::UnaryExpressionContext* ctx) {
        std::any value = visit(ctx->primaryExpression());

        // Resolve identifier
        if (value.type() == typeid(IdentifierLiteral)) {
            const auto id = std::any_cast<IdentifierLiteral>(value);
            const auto var = scope->lookupVariable(id.value);
            if (!var.has_value())
                throwScopeError("variable '" + id.value + "' not declared", id.value, value, source);
            value = var.value()->value;
        }

        // ---------- Logical NOT (!) ----------
        if (ctx->NOT().size() > 0) {
            const auto [vValue, vType] = extract(value, scope, source);
            bool b;

            if (vType == "int") {
                b = BigInt(vValue) != 0;
            } else if (vType == "float") {
                b = std::stod(vValue) != 0.0;
            } else if (vType == "str") {
                b = !vValue.empty();
            } else if (vType == "bool") {
                b = vValue == "1";
            } else {
                throwError("Invalid operand for '!'", value, source);
            }

            if (ctx->NOT().size() % 2 == 0)
                return BooleanLiteralNode(b ? "1" : "0", {}, {});

            return BooleanLiteralNode(b ? "0" : "1", {}, {});
        }

        // ---------- Bitwise NOT (~) ----------
        if (ctx->BIT_NOT()) {
            const auto [vValue, vType] = extract(value, scope, source);

            if (vType != "int")
                throwError("Operator '~' requires integer operand", value, source);

            BigInt num(vValue);
            return IntegerLiteralNode((~num).str(), {}, {});
        }

        // ---------- Unary + / - ----------
        if (ctx->PLUS() || ctx->MINUS()) {
            const auto [vValue, vType] = extract(value, scope, source);

            if (vType != "int" && vType != "float")
                throwError("Unary +/- requires numeric operand", value, source);

            if (vType == "int") {
                BigInt num(vValue);
                if (ctx->MINUS())
                    num = -num;
                return IntegerLiteralNode(num.str(), {}, {});
            }

            double num = std::stod(vValue);
            if (ctx->MINUS())
                num = -num;
            return FloatLiteralNode(std::to_string(num), {}, {});
        }

        return value;
    }

    // --------------------------------------------------------
    // Primary: literals, identifiers, member, parentheses
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitPrimaryExpression(Grammar::PrimaryExpressionContext* ctx) {
        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        if (ctx->literals()) {
            return visit(ctx->literals());
        }
        if (ctx->memberExpression())
            return visit(ctx->memberExpression());
        if (ctx->LPAREN())
            return visit(ctx->expression());

        throwError("Unknown primary expression", NoneLiteralNode("", start, end), source);
        return {};
    }

} // namespace yogi::visitor