//
// Created by Brayhan De Aza on 11/27/25.
//

#include "ProgramVisitor.h"
#include <visitors/nodes/nodes.h>

std::any yogi::visitor::Visitor::visitProgram(Grammar::ProgramContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    // Cache AST
    if (const auto cachedAST = getCachedAST(filePath); cachedAST.has_value()) {
        return cachedAST.value().program;
    }

    // Create program node
    auto node = nodes::ProgramNode(start, end);
    for (const auto child : ctx->children) {
        if (auto statement = visit(child); statement.has_value()) {
            node.addStatement(std::move(statement));
        }
    }

    return node;
}

std::any yogi::visitor::Visitor::visitStatements(Grammar::StatementsContext* ctx) {
    // Expression statement
    if (ctx->expression()) {
        const auto expressionResult = visit(ctx->expression());
        return expressionResult;
    }

    // Variable declaration statement
    if (ctx->variables()) {
        const std::any variableStatement = visit(ctx->variables());
        return variableStatement;
    }

    // Array declaration statement
    if (ctx->arrays()) {
        const std::any arrayDeclaration = visit(ctx->arrays());
        return arrayDeclaration;
    }

    // Dictionary declaration statement
    if (ctx->dictionaryDeclaration()) {
        const std::any dictionaryDeclaration = visit(ctx->dictionaryDeclaration());
        return dictionaryDeclaration;
    }

    // Member expression statement
    if (ctx->memberExpression()) {
        const auto node = visit(ctx->memberExpression());
        return node;
    }

    // Boolean literal statement
    if (ctx->booleanLiteral()) {
        const std::any node = visit(ctx->booleanLiteral());
        return node;
    }

    // None literal statement
    if (ctx->noneLiteral()) {
        const std::any node = visit(ctx->noneLiteral());
        return node;
    }

    // None literal statement
    if (ctx->ifStatement()) {
        const std::any node = visit(ctx->ifStatement());
        return node;
    }

    // Return empty statement if nothing matches
    return nullptr;
}