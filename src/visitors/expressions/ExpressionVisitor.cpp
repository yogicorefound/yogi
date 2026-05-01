#include <boost/multiprecision/cpp_int.hpp>
#ifdef EOF
#undef EOF
#endif

#include <visitors/nodes/nodes.h>
#include "ExpressionVisitor.h"

namespace yogi::visitor {

using namespace nodes;

// --------------------------------------------------------
// Expression
// --------------------------------------------------------
std::any ExpressionVisitor::visitExpression(Grammar::ExpressionContext *ctx) {
    return visit(ctx->conditionalExpression());
}

// --------------------------------------------------------
// Conditional (ternary)
// --------------------------------------------------------
std::any ExpressionVisitor::visitConditionalExpression(Grammar::ConditionalExpressionContext *ctx) {
    std::any condition = visit(ctx->logicalOrExpression());

    if (ctx->expression().size() != 2)
        return condition;

    const std::any left = visit(ctx->expression(0));
    const std::any right = visit(ctx->expression(1));

    return TernaryExpressionNode(condition, left, right, "", "", {}, {});
}

// --------------------------------------------------------
// Logical OR
// --------------------------------------------------------
std::any ExpressionVisitor::visitLogicalOrExpression(Grammar::LogicalOrExpressionContext *ctx) {
    std::any result = visit(ctx->logicalAndExpression(0));

    for (size_t i = 1; i < ctx->logicalAndExpression().size(); ++i) {
        std::any rhs = visit(ctx->logicalAndExpression(i));

        result = BinaryExpressionNode(result, rhs, "||", "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Logical AND
// --------------------------------------------------------
std::any ExpressionVisitor::visitLogicalAndExpression(Grammar::LogicalAndExpressionContext *ctx) {
    std::any result = visit(ctx->bitwiseOrExpression(0));

    for (size_t i = 1; i < ctx->bitwiseOrExpression().size(); ++i) {
        std::any rhs = visit(ctx->bitwiseOrExpression(i));

        result = BinaryExpressionNode(result, rhs, "&&", "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Relational
// --------------------------------------------------------
std::any ExpressionVisitor::visitRelationalExpression(Grammar::RelationalExpressionContext *ctx) {
    std::any left = visit(ctx->shiftExpression(0));

    for (size_t i = 1; i < ctx->shiftExpression().size(); ++i) {
        std::any right = visit(ctx->shiftExpression(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        left = BinaryExpressionNode(left, right, op, "", "", {}, {});
    }

    return left;
}

// --------------------------------------------------------
// Equality
// --------------------------------------------------------
std::any ExpressionVisitor::visitEqualityExpression(Grammar::EqualityExpressionContext *ctx) {
    std::any left = visit(ctx->relationalExpression(0));

    for (size_t i = 1; i < ctx->relationalExpression().size(); ++i) {
        std::any right = visit(ctx->relationalExpression(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        left = BinaryExpressionNode(left, right, op, "", "", {}, {});
    }

    return left;
}

// --------------------------------------------------------
// Bitwise AND
// --------------------------------------------------------
std::any ExpressionVisitor::visitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext *ctx) {
    std::any result = visit(ctx->equalityExpression(0));

    for (size_t i = 1; i < ctx->equalityExpression().size(); ++i) {
        std::any rhs = visit(ctx->equalityExpression(i));

        result = BinaryExpressionNode(result, rhs, "&", "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Bitwise XOR
// --------------------------------------------------------
std::any ExpressionVisitor::visitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext *ctx) {
    std::any result = visit(ctx->bitwiseAndExpression(0));

    for (size_t i = 1; i < ctx->bitwiseAndExpression().size(); ++i) {
        std::any rhs = visit(ctx->bitwiseAndExpression(i));

        result = BinaryExpressionNode(result, rhs, "^", "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Bitwise OR
// --------------------------------------------------------
std::any ExpressionVisitor::visitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext *ctx) {
    std::any result = visit(ctx->bitwiseXorExpression(0));

    for (size_t i = 1; i < ctx->bitwiseXorExpression().size(); ++i) {
        std::any rhs = visit(ctx->bitwiseXorExpression(i));

        result = BinaryExpressionNode(result, rhs, "|", "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Shift
// --------------------------------------------------------
std::any ExpressionVisitor::visitShiftExpression(Grammar::ShiftExpressionContext *ctx) {
    std::any result = visit(ctx->additiveExpression(0));

    for (size_t i = 1; i < ctx->additiveExpression().size(); ++i) {
        std::any rhs = visit(ctx->additiveExpression(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        result = BinaryExpressionNode(result, rhs, op, "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Additive
// --------------------------------------------------------
std::any ExpressionVisitor::visitAdditiveExpression(Grammar::AdditiveExpressionContext *ctx) {
    std::any result = visit(ctx->multiplicativeExpression(0));

    for (size_t i = 1; i < ctx->multiplicativeExpression().size(); ++i) {
        std::any rhs = visit(ctx->multiplicativeExpression(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        result = BinaryExpressionNode(result, rhs, op, "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Multiplicative
// --------------------------------------------------------
std::any ExpressionVisitor::visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext *ctx) {
    std::any result = visit(ctx->powerExpression(0));

    for (size_t i = 1; i < ctx->powerExpression().size(); ++i) {
        std::any rhs = visit(ctx->powerExpression(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        result = BinaryExpressionNode(result, rhs, op, "", "", {}, {});
    }

    return result;
}

// --------------------------------------------------------
// Power
// --------------------------------------------------------
std::any ExpressionVisitor::visitPowerExpression(Grammar::PowerExpressionContext *ctx) {
    std::any left = visit(ctx->unaryExpression());

    if (!ctx->powerExpression())
        return left;

    std::any right = visit(ctx->powerExpression());

    return BinaryExpressionNode(left, right, "**", "", "", {}, {});
}

// --------------------------------------------------------
// Unary
// --------------------------------------------------------
std::any ExpressionVisitor::visitUnaryExpression(Grammar::UnaryExpressionContext *ctx) {
    std::any value = visit(ctx->primaryExpression());

    if (ctx->PLUS())
        return UnaryExpressionNode("+", value, {}, {});

    if (ctx->MINUS())
        return UnaryExpressionNode("-", value, {}, {});

    if (ctx->NOT().size() > 0)
        return UnaryExpressionNode("!", value, {}, {});

    if (ctx->BIT_NOT())
        return UnaryExpressionNode("~", value, {}, {});

    return value;
}

// --------------------------------------------------------
// Primary
// --------------------------------------------------------
std::any ExpressionVisitor::visitPrimaryExpression(Grammar::PrimaryExpressionContext *ctx) {
    if (ctx->literals())
        return visit(ctx->literals());

    if (ctx->memberExpression())
        return visit(ctx->memberExpression());

    if (ctx->LPAREN())
        return visit(ctx->expression());

    throw std::runtime_error("Unknown primary expression");
}

} // namespace yogi::visitor