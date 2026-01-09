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
    // Additive: +, -
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitAdditiveExpression(Grammar::AdditiveExpressionContext* ctx) {
        std::any result = visit(ctx->multiplicativeExpression(0));

        for (size_t i = 1; i < ctx->multiplicativeExpression().size(); ++i) {
            std::any rhs = visit(ctx->multiplicativeExpression(i));
            std::string op = ctx->children[2 * i - 1]->getText();

            const auto [lValue, lType] = extract(result, scope);
            const auto [rValue, rType] = extract(rhs, scope);

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

            const auto [lValue, lType] = extract(result, scope);

            if (const auto [rValue, rType] = extract(rhs, scope); lType == "int" && rType == "int" && op != "/") {
                BigInt l(lValue);
                BigInt r(rValue);
                BigInt out;

                if (op == "*")
                    out = l * r;

                else if (op == "%") {
                    if (r == 0)
                        throw std::runtime_error("Modulo by zero");
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
                        throw std::runtime_error("Division by zero");

                    out = l / r;

                } else if (op == "%") {
                    if (r == 0) {
                        throw std::runtime_error("Modulo by zero");
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
        const auto [lValue, lType] = extract(left, scope);
        const auto [rValue, rType] = extract(right, scope);

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
    // Unary: +, -
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitUnaryExpression(Grammar::UnaryExpressionContext* ctx) {
        // Primero obtenemos el valor de la expresión interna (primary o recursiva)
        std::any value = visit(ctx->primaryExpression());

        // Resolver identificadores si es necesario
        if (value.type() == typeid(IdentifierLiteral)) {
            const auto identifierLiteral = std::any_cast<IdentifierLiteral>(value);
            const auto variable = scope->lookupVariable(identifierLiteral.value);
            if (!variable.has_value()) {
                throwScopeError("variable '" + identifierLiteral.value + "' not declared", identifierLiteral.value, value, source);
            }
            value = variable.value()->value;
        }

        // -------------------------------------------------
        // Operador NOT '!'
        // -------------------------------------------------
        if (ctx->NOT()) {
            const auto [vValue, vType] = extract(value, scope);
            bool b;

            if (vType == "bool") {
                b = (vValue == "true");
            } else if (vType == "int") {
                BigInt num(vValue);
                b = (num != 0);
            } else if (vType == "float") {
                double num = std::stod(vValue);
                b = (num != 0.0);
            } else if (vType == "str") {
                b = !vValue.empty(); // empty string → false, non-empty → true
            } else {
                throw std::runtime_error("Operator '!' requires a boolean, numeric, or string literal");
            }

            return BooleanLiteralNode(b ? "0" : "1", {}, {});
        }

        // -------------------------------------------------
        // Operadores + y - unarios
        // -------------------------------------------------
        if (ctx->PLUS() || ctx->MINUS()) {
            const auto [eValue, eType] = extract(value, scope);
            if (eType != "int" && eType != "float")
                throw std::runtime_error("Unary operator requires numeric operand");

            if (eType == "int") {
                BigInt num(eValue);
                if (ctx->MINUS())
                    num = -num;
                return IntegerLiteralNode(num.str(), {}, {});
            }

            double num = std::stod(eValue);
            if (ctx->MINUS())
                num = -num;
            return FloatLiteralNode(std::to_string(num), {}, {});
        }

        // Si no hay operador, retornamos el valor tal cual
        return value;
    }

    // --------------------------------------------------------
    // Primary: literals, identifiers, member, parentheses
    // --------------------------------------------------------
    std::any ExpressionVisitor::visitPrimaryExpression(Grammar::PrimaryExpressionContext* ctx) {
        if (ctx->literals()) {
            return visit(ctx->literals());
        }
        if (ctx->memberExpression())
            return visit(ctx->memberExpression());
        if (ctx->LPAREN())
            return visit(ctx->expression());

        throw std::runtime_error("Unknown primary expression");
    }

} // namespace yogi::visitor