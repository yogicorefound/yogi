//
// Created by Brayhan De Aza on 5/8/26.
//

#include "ModulesVisitor.h"

namespace yogi::visitor {
    std::any ModulesVisitor::visitImportStatement(Grammar::ImportStatementContext *ctx) {
        if (ctx->importStatementWithBrackets()) {
            return visit(ctx->importStatementWithBrackets());
        }

        if (ctx->importStatementWithoutBrackets()) {
            return visit(ctx->importStatementWithoutBrackets());
        }

        return nullptr;
    }

    std::any ModulesVisitor::visitImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto path = ctx->stringLiteral()->getText();
        const auto pathNode = std::any_cast<nodes::StringLiteralNode>(path);

        std::vector<nodes::IdentifierLiteral> modules;
        for (const auto module: ctx->identifierLiteral()) {
            const auto visitedModule = visit(module);
            const auto moduleNode = std::any_cast<nodes::IdentifierLiteral>(visitedModule);
            modules.push_back(moduleNode);
        }

        const auto node = nodes::ImportWithBracketsNode(path, modules, start, end);
        return node;
    }

    std::any ModulesVisitor::visitImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto name = ctx->identifierLiteral()->getText();
        const auto path = ctx->stringLiteral()->getText();

        const auto node = nodes::ImportWithoutBracketsNode(name, path, start, end);
        return node;
    }
}