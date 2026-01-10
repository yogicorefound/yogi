//
// Created by Brayhan De Aza on 11/27/25.
//

#include <boost/multiprecision/cpp_int.hpp>
#ifdef EOF
#undef EOF
#endif
#include <visitors/nodes/nodes.h>
#include "ConditionsVisitor.h"

namespace yogi::visitor {
    using BigInt = boost::multiprecision::int128_t; // or cpp_int for arbitrary size

    std::any ConditionsVisitor::visitIfStatement(Grammar::IfStatementContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto ifStatement = nodes::IfStatementNode(start, end);

        // --- Visit main "if" branch ---
        enterScope();
        const auto condition = visit(ctx->ifStatementCondition());
        const auto body = visit(ctx->ifStatementBody());
        exitScope();

        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));

        // --- Visit "else if" branches ---
        for (const auto elseIfCtx : ctx->elseIfStatement()) {
            const auto elseIfNodeAny = visit(elseIfCtx);

            for (const auto elseIfNode = std::any_cast<nodes::IfStatementNode>(elseIfNodeAny); const auto& branch : elseIfNode.branches) {
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

        // Enter scope only for declarations inside this else-if
        enterScope();
        const auto condition = visit(ctx->ifStatementCondition());
        const auto body = visit(ctx->ifStatementBody());
        exitScope();

        ifStatement.addBranch(condition, std::any_cast<std::vector<std::any>>(body));
        return ifStatement;
    }

    std::any ConditionsVisitor::visitIfStatementCondition(Grammar::IfStatementConditionContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto expression = visit(ctx->expression());
        const auto [type, value, node] = resolveItem(expression);

        bool isTrue = true;
        if (type == "str" || type == "regex") {
            isTrue = value.size() > 0;

        } else {
            isTrue = std::stold(value) != 0;
        }

        return nodes::BooleanLiteralNode(isTrue ? "1" : "0", start, end);
    }

    std::any ConditionsVisitor::visitElseStatement(Grammar::ElseStatementContext* ctx) {
        // Enter scope only for declarations in else
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
