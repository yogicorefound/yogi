//
// Created by Brayhan De Aza on 5/8/26.
//

#include "ExportVisitor.h"
#include "Grammar.h"

namespace yogi::visitor {

    std::any ExportVisitor::visitExportStatement(
        Grammar::ExportStatementContext *ctx
    ) {
        if (ctx->exportDeclarationStatement()) {
            return visit(ctx->exportDeclarationStatement());
        }

        if (ctx->exportNamedStatement()) {
            return visit(ctx->exportNamedStatement());
        }

        if (ctx->exportNamedGroupStatement()) {
            return visit(ctx->exportNamedGroupStatement());
        }

        if (ctx->exportDefaultStatement()) {
            return visit(ctx->exportDefaultStatement());
        }

        return std::any();
    }

    std::any ExportVisitor::visitExportNamedStatement(Grammar::ExportNamedStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->exportSpecifier());
        const auto node = nodes::ExportNode(start, end, variableDeclaration);

        return node;
    }

    std::any ExportVisitor::visitExportDefaultStatement(Grammar::ExportDefaultStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto declaration = visit(ctx->expression());
        const auto node = nodes::ExportNode(start, end, declaration);

        return node;
    }

    std::any ExportVisitor::visitExportNamedGroupStatement(Grammar::ExportNamedGroupStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        std::vector<nodes::ExportNode> exports;
        for (auto *specifier: ctx->exportSpecifier()) {
            auto spec = std::any_cast<nodes::ExportNode>(
                visit(specifier)
            );

            exports.push_back(spec);
        }

        return nodes::ExportListNode(exports, start, end);
    }

    std::any ExportVisitor::visitExportSpecifier(Grammar::ExportSpecifierContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto identifiers = ctx->identifierLiteral();
        const auto identifier = visit(identifiers.at(0));

        std::string alias = "";
        if (identifiers.size() > 1) {
            alias = identifiers.at(1)->getText();
        }

        const auto aliasNode = nodes::IdentifierLiteral(alias, start, end);
        const auto node = nodes::ExportNode(start, end, identifier, aliasNode);

        return node;
    }

    std::any ExportVisitor::visitExportDeclarationStatement(Grammar::ExportDeclarationStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->variableDeclaration());
        const auto node = nodes::ExportNode(start, end, variableDeclaration);

        return node;
    }

}