//
// Created by Brayhan De Aza on 11/27/25.
//

#include "ProgramVisitor.h"
#include <ast/nodes/nodes.h>
#include <utils/utils.h>

std::any cromio::visitor::Visitor::visitProgram(Grammar::ProgramContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    // Create program node
    auto programNode = nodes::ProgramNode(start, end);

    // Visit all children and add them to the program body
    for (antlr4::tree::ParseTree* child : ctx->children) {
        if (std::any statement = visit(child); statement.has_value()) {
            // Check if it's a StatementNode
            if (statement.type() == typeid(nodes::StatementNode)) {
                auto stmtNode = std::any_cast<nodes::StatementNode>(statement);
                programNode.addStatement(std::move(stmtNode));
            }
            // If it's a direct node (expression, literal, etc.), wrap it in StatementNode
            else {
                auto wrappedStmt = nodes::StatementNode(start, end);
                wrappedStmt.addChild(statement);
                programNode.addStatement(std::move(wrappedStmt));
            }
        }
    }

    return programNode;
}

std::any cromio::visitor::Visitor::visitStatements(Grammar::StatementsContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    // Create a statement node that will hold the child
    auto statementNode = nodes::StatementNode(start, end);

    // Expression statement
    if (ctx->expression()) {
        const std::any expressionResult = visit(ctx->expression());
        statementNode.addChild(expressionResult);
        return statementNode;
    }

    // Variable declaration statement
    if (ctx->variables()) {
        const std::any variableStatement = visit(ctx->variables());
        statementNode.addChild(variableStatement);
        return statementNode;
    }

    // Array declaration statement
    if (ctx->arrayDeclaration()) {
        const std::any arrayDeclaration = visit(ctx->arrayDeclaration());
        statementNode.addChild(arrayDeclaration);
        return statementNode;
    }

    // Dictionary declaration statement
    if (ctx->dictionaryDeclaration()) {
        const std::any dictionaryDeclaration = visit(ctx->dictionaryDeclaration());
        statementNode.addChild(dictionaryDeclaration);
        return statementNode;
    }

    // Return empty statement if nothing matches
    return statementNode;
}