//
// Created by Brayhan De Aza on 5/8/26.
//

#include "ExportVisitor.h"

namespace yogi::visitor {

    std::any ExportVisitor::visitExportStatement(Grammar::ExportStatementContext *ctx) {
        if (ctx->exportVariableDeclaration()) {
            return visit(ctx->exportVariableDeclaration());
        }

        if (ctx->exportIdentifier()) {
            return visit(ctx->exportIdentifier());
        }

        if (ctx->exportMultipleIdentifiers()) {
            std::cout << "exportMultipleIdentifiers" << std::endl;
            return visit(ctx->exportMultipleIdentifiers());
        }

        return std::any();
    }

    std::any ExportVisitor::visitExportIdentifier(Grammar::ExportIdentifierContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->identifierLiteral());
        const auto node = nodes::ExportDeclarationNode(variableDeclaration, start, end);

        return node;
    }

    std::any ExportVisitor::visitExportVariableDeclaration(Grammar::ExportVariableDeclarationContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->variableDeclaration());
        const auto node = nodes::ExportDeclarationNode(variableDeclaration, start, end);

        return node;
    }

    std::any ExportVisitor::visitExportMultipleIdentifiers(Grammar::ExportMultipleIdentifiersContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto declarations = std::vector<std::any>();
        for (const auto identifier: ctx->identifierLiteral()) {
            const auto variableDeclaration = visit(identifier);
            declarations.push_back(variableDeclaration);
        }

        const auto node = nodes::ExportListNode(declarations, start, end);
        return node;
    }


}