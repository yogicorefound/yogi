//
// Created by Brayhan De Aza on 11/27/25.
//

#include "ConditionsVisitor.h"
#include <visitors/nodes/nodes.h>

namespace yogi::visitor {

    std::any ConditionsVisitor::visitIfStatement(Grammar::IfStatementContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Visit the main "if" condition and body
        const auto condition = visit(ctx->expression());
        const auto body = visit(ctx->ifStatementBody());

        auto ifStatement = nodes::IfStatementNode(start, end);
        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));

        // Add else if branches
        for (const auto elseIfCtx : ctx->elseIfStatement()) {
            const auto elseIfNodeAny = visit(elseIfCtx);

            // Each else if node may have multiple branches; usually just one
            for (const auto elseIfNode = std::any_cast<nodes::IfStatementNode>(elseIfNodeAny); const auto& branch : elseIfNode.branches) {
                ifStatement.branches.push_back(branch);
            }
        }

        // Add else branch if it exists
        if (const auto elseCtx = ctx->elseStatement()) {
            const auto elseBodyAny = visit(elseCtx);
            ifStatement.addElse(std::any_cast<std::vector<std::any>>(elseBodyAny));
        }

        return ifStatement;
    }

    std::any ConditionsVisitor::visitElseIfStatement(Grammar::ElseIfStatementContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto condition = visit(ctx->expression());
        const auto body = visit(ctx->ifStatementBody());

        auto ifStatement = nodes::IfStatementNode(start, end);
        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));

        return ifStatement;
    }

    std::any ConditionsVisitor::visitElseStatement(Grammar::ElseStatementContext* ctx) {
        // Just return the body; the parent "if" will attach it
        return visit(ctx->ifStatementBody());
    }

    std::any ConditionsVisitor::visitIfStatementBody(Grammar::IfStatementBodyContext* ctx) {
        std::vector<std::any> node;

        for (const auto child : ctx->children) {
            if (auto statement = visit(child); statement.has_value()) {
                node.push_back(std::move(statement));
            }
        }

        return node;
    }

} // namespace yogi::visitor
