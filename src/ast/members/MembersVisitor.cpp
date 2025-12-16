#include "MembersVisitor.h"
#include <ast/nodes/nodes.h>

namespace cromio::visitor {

    std::any MembersVisitor::visitMemberExpression(Grammar::MemberExpressionContext* ctx) {
        // 1️⃣ Base value (identifier, literal, or parenthesized expression)
        std::any current = visit(ctx->valueAtom());

        // 2️⃣ Apply postfix chain
        for (auto* postfix : ctx->valuePostfix()) {
            const nodes::Position pStart{postfix->start->getLine(), postfix->start->getCharPositionInLine()};
            const nodes::Position pEnd{postfix->stop->getLine(), postfix->stop->getCharPositionInLine()};

            // PROPERTY ACCESS: .name
            if (postfix->DOT()) {
                const std::string memberName = postfix->identifierLiteral()->getText();

                current = nodes::MemberExpressionNode(current, memberName, {}, false, pStart, pEnd);
            }
            // CALL: (args)
            else {
                std::vector<std::any> args;
                if (postfix->argumentList()) {
                    for (auto* expr : postfix->argumentList()->expression()) {
                        args.push_back(visit(expr));
                    }
                }

                current = nodes::MemberExpressionNode(current, "", args, true, pStart, pEnd);
            }
        }

        return current;
    }

    std::any MembersVisitor::visitValueAtom(Grammar::ValueAtomContext* ctx) {
        if (ctx->identifierLiteral())
            return visit(ctx->identifierLiteral());

        if (ctx->stringLiteral())
            return visit(ctx->stringLiteral());

        if (ctx->numberLiterals())
            return visit(ctx->numberLiterals());

        if (ctx->booleanLiteral())
            return visit(ctx->booleanLiteral());

        // (expression)
        return visit(ctx->expression());
    }

    std::any MembersVisitor::visitValuePostfix(Grammar::ValuePostfixContext* ctx) {
        return visitChildren(ctx);
    }

    std::any MembersVisitor::visitArgumentList(Grammar::ArgumentListContext* ctx) {
        return visitChildren(ctx);
    }

} // namespace cromio::visitor
