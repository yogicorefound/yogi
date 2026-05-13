//
// Created by Brayhan De Aza on 11/27/25.
//

// #include <boost/multiprecision/cpp_int.hpp>
#ifdef EOF
#undef EOF
#endif
#include <visitors/nodes/nodes.h>
#include "ConditionsVisitor.h"

namespace yogi::visitor {

    bool isConstexprBool(const std::any& value) {
        if (value.type() == typeid(nodes::BooleanLiteralNode))
            return true;
        if (value.type() == typeid(nodes::IntegerLiteralNode))
            return true;
        return false;
    }

    bool isTruthy(const std::any& node) {
        const auto [t, v, n] = utils::Helpers::resolveItem(node);
        return v == "1";
    }

    std::any ConditionsVisitor::visitIfStatement(Grammar::IfStatementContext* ctx) {
        const std::any condAny = visit(ctx->ifStatementCondition());

        // Prepare AST node for the full if-statement tree
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        nodes::IfStatementNode ifStatement(start, end);

        bool executedBranch = false;

        // ---------- COMPILE-TIME FOLDING / EXECUTION ----------
        if (isConstexprBool(condAny)) {
            // IF
            if (isTruthy(condAny)) {
                enterScope();
                auto result = visit(ctx->ifStatementBody()); // Execute only this
                exitScope();
                executedBranch = true;

                ifStatement.addBranch(condAny, std::any_cast<std::vector<std::any>>(result));
            } else {
                // Still add the false branch to tree (but do not execute)
                ifStatement.addBranch(condAny, std::vector<std::any>{});
            }

            // ELSE IF
            for (const auto elseIfCtx : ctx->elseIfStatement()) {
                const std::any elseIfCond = visit(elseIfCtx->ifStatementCondition());
                if (isConstexprBool(elseIfCond) && isTruthy(elseIfCond) && !executedBranch) {
                    enterScope();
                    auto result = visit(elseIfCtx->ifStatementBody());
                    exitScope();
                    executedBranch = true;

                    ifStatement.addBranch(elseIfCond, std::any_cast<std::vector<std::any>>(result));
                } else {
                    // Add branch to tree but do NOT execute
                    ifStatement.addBranch(elseIfCond, std::vector<std::any>{});
                }
            }

            // ELSE
            if (ctx->elseStatement()) {
                if (!executedBranch) {
                    enterScope();
                    auto result = visit(ctx->elseStatement());
                    exitScope();
                    ifStatement.addElse(std::any_cast<std::vector<std::any>>(result));
                } else {
                    // Add else node but leave body empty
                    ifStatement.addElse(std::vector<std::any>{});
                }
            }

            return ifStatement; // Return full tree
        }

        // ---------- RUNTIME IF (cannot fold) ----------
        {
            enterScope();
            const auto body = visit(ctx->ifStatementBody());
            exitScope();
            ifStatement.addBranch(condAny, std::any_cast<std::vector<std::any>>(body));
        }

        for (const auto elseIfCtx : ctx->elseIfStatement()) {
            auto nodeAny = visit(elseIfCtx);
            auto node = std::any_cast<nodes::IfStatementNode>(nodeAny);
            for (const auto& b : node.branches)
                ifStatement.branches.push_back(b);
        }

        if (ctx->elseStatement()) {
            auto body = visit(ctx->elseStatement());
            ifStatement.addElse(std::any_cast<std::vector<std::any>>(body));
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
        // Return the expression node without evaluating it
        // The interpreter will evaluate it at runtime
        return visit(ctx->expression());
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