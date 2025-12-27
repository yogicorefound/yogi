#include "MembersVisitor.h"
#include <ast/nodes/nodes.h>

namespace yogi::visitor {

    std::any MembersVisitor::visitMemberExpression(Grammar::MemberExpressionContext* ctx) {
        // 1️⃣ Base value (identifier, literal, or parenthesized expression)
        const std::any atom = visit(ctx->valueAtom());

        // ✅ Validate atom before casting
        if (!atom.has_value()) {
            throw std::runtime_error("Error: valueAtom() returned empty value");
        }

        const auto identifier = std::any_cast<nodes::IdentifierLiteral>(atom);

        const auto lookupVariable = scope->lookupVariable(identifier.value);
        if (!lookupVariable.has_value()) {
            throwScopeError("variable '" + identifier.value + "' is not declared", identifier.value, atom, source);
        }

        const auto& variable = lookupVariable.value();

        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        variable->start = start;
        variable->end = end;

        // ✅ Initialize current with the variable itself as fallback
        std::any current = variable->value;

        // 2️⃣ Apply postfix chain
        auto postfixes = ctx->valuePostfix();
        if (postfixes.empty()) {
            // No postfix operations, return the variable's value
            return current;
        }

        for (size_t i = 0; i < postfixes.size(); i++) {
            auto* postfix = postfixes[i];
            if (!postfix)
                throw std::runtime_error("Null postfix at index " + std::to_string(i));

            std::string memberName;
            std::vector<std::any> arguments;
            bool isMethod = false;

            if (postfix->DOT()) {
                auto* identLiteral = postfix->identifierLiteral();
                memberName = identLiteral->getText();

                // Lookahead: is next postfix a LPAREN for method call?
                if (i + 1 < postfixes.size() && postfixes[i + 1]->LPAREN()) {
                    isMethod = true;
                    auto* callPostfix = postfixes[i + 1];
                    if (callPostfix->argumentList()) {
                        for (auto* expr : callPostfix->argumentList()->expression()) {
                            arguments.push_back(visit(expr));
                        }
                    }
                    i++; // Skip the LPAREN postfix, already processed
                }
            } else if (postfix->LPAREN()) {
                isMethod = true;
                if (postfix->argumentList()) {
                    for (auto* expr : postfix->argumentList()->expression()) {
                        arguments.push_back(visit(expr));
                    }
                }

                memberName = ""; // empty means "call current object"
            }

            current = processMembers(*variable, memberName, isMethod, arguments, source);
            if (!current.has_value())
                throw std::runtime_error("processMembers returned empty value");
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

} // namespace yogi::visitor