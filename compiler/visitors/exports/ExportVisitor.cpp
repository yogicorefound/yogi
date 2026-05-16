//
// Created by Brayhan De Aza on 5/8/26.
//

#include "ExportVisitor.h"
#include "Grammar.h"

namespace yogi::visitor {

    std::any ExportVisitor::visitExportStatement(Grammar::ExportStatementContext *ctx) {
        if (ctx->exportDeclaration()) {
            return visit(ctx->exportDeclaration());
        }

        if (ctx->reExportAll()) {
            return visit(ctx->reExportAll());
        }

        if (ctx->reExportWithBrackets()) {
            return visit(ctx->reExportWithBrackets());
        }

        return std::any();
    }


    std::any ExportVisitor::visitExportDeclaration(Grammar::ExportDeclarationContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->variableDeclaration());
        const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportSymbol, variableDeclaration);

        return node;
    }


    std::any ExportVisitor::visitReExportAll(Grammar::ReExportAllContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        std::cout << "reExportAll";

        const auto stringLiteral = visit(ctx->stringLiteral());
        const auto stringLiteralNode = std::any_cast<nodes::StringLiteralNode>(stringLiteral);
        const auto node = nodes::ReExportModuleNode(start, end, stringLiteralNode);

        return node;
    }


    std::any ExportVisitor::visitReExportWithBrackets(Grammar::ReExportWithBracketsContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto path = ctx->stringLiteral()->getText();

        std::vector<nodes::IdentifierLiteral> modules;
        for (const auto module: ctx->identifierLiteral()) {
            const auto visitedModule = visit(module);
            const auto moduleNode = std::any_cast<nodes::IdentifierLiteral>(visitedModule);
            modules.push_back(moduleNode);
        }

        const auto node = nodes::ImportWithBracketsNode(path, modules, start, end);
        return node;
    }

}