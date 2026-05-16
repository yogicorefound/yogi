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
        const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportSymbol, variableDeclaration);

        return node;
    }

    std::any ExportVisitor::visitExportDefaultStatement(Grammar::ExportDefaultStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        if (ctx->expression()) {
            const auto declaration = visit(ctx->expression());
            const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportDefault, declaration);

            return node;
        }

        const auto exports = visit(ctx->exportSpecifierWithBraces());
        const auto exportListNode = std::any_cast<std::vector<nodes::ExportNode> >(exports);

        return nodes::ExportListNode(start, end, nodes::Kind::ExportDefault, exportListNode);
    }

    std::any ExportVisitor::visitExportNamedGroupStatement(Grammar::ExportNamedGroupStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto exports = visit(ctx->exportSpecifierWithBraces());
        const auto exportListNode = std::any_cast<std::vector<nodes::ExportNode> >(exports);

        return nodes::ExportListNode(start, end, nodes::Kind::ExportSymbol, exportListNode);
    }

    std::any ExportVisitor::visitExportSpecifierWithBraces(Grammar::ExportSpecifierWithBracesContext *ctx) {
        std::vector<nodes::ExportNode> exports;
        for (auto *specifier: ctx->exportSpecifier()) {
            auto spec = std::any_cast<nodes::ExportNode>(
                visit(specifier)
            );

            exports.push_back(spec);
        }

        return exports;
    }

    std::any ExportVisitor::visitExportSpecifier(Grammar::ExportSpecifierContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto identifiers = ctx->identifierLiteral();
        const auto identifier = visit(identifiers.at(0));

        std::string alias = "";
        bool hasAlias = false;
        if (identifiers.size() > 1) {
            alias = identifiers.at(1)->getText();
            hasAlias = true;
        }

        if (hasAlias) {
            const auto aliasNode = nodes::IdentifierLiteral(alias, start, end);
            const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportSymbol, identifier, aliasNode);
            return node;
        }

        const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportSymbol, identifier, std::nullopt);
        return node;
    }

    std::any ExportVisitor::visitExportDeclarationStatement(Grammar::ExportDeclarationStatementContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto variableDeclaration = visit(ctx->variableDeclaration());
        const auto node = nodes::ExportNode(start, end, nodes::Kind::ExportSymbol, variableDeclaration);

        return node;
    }

}