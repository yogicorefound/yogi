//
// Created by Brayhan De Aza on 11/27/25.
//

#include "ConditionsVisitor.h"
#include <visitors/nodes/nodes.h>

namespace yogi::visitor {

    std::any ConditionsVisitor::visitIfStatement(Grammar::IfStatementContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto ifStatement = nodes::IfStatementNode(start, end);

        // --- Visit main "if" branch ---
        enterScope();
        const auto condition = visit(ctx->expression());
        const auto body = visit(ctx->ifStatementBody());
        exitScope();

        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));

        // --- Visit "else if" branches ---
        for (const auto elseIfCtx : ctx->elseIfStatement()) {
            const auto elseIfNodeAny = visit(elseIfCtx);
            const auto elseIfNode = std::any_cast<nodes::IfStatementNode>(elseIfNodeAny);

            // Each else if branch gets its own scope already in visitElseIfStatement
            for (const auto& branch : elseIfNode.branches) {
                ifStatement.branches.push_back(branch);
            }
        }

        // --- Visit "else" branch ---
        if (const auto elseCtx = ctx->elseStatement()) {
            enterScope();
            const auto elseBodyAny = visit(elseCtx);
            exitScope();

            ifStatement.addElse(std::any_cast<std::vector<std::any>>(elseBodyAny));
        }

        return ifStatement;
    }

    std::any ConditionsVisitor::visitElseIfStatement(Grammar::ElseIfStatementContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto ifStatement = nodes::IfStatementNode(start, end);

        // Enter scope for this else-if branch
        enterScope();
        const auto condition = visit(ctx->expression());
        const auto body = visit(ctx->ifStatementBody());
        exitScope();

        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));
        return ifStatement;
    }

    std::any ConditionsVisitor::visitElseStatement(Grammar::ElseStatementContext* ctx) {
        // Enter scope for else branch
        enterScope();
        const auto body = visit(ctx->ifStatementBody());
        exitScope();

        return body;
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
