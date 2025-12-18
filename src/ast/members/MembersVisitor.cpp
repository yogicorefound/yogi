#include "MembersVisitor.h"
#include <ast/nodes/nodes.h>

namespace cromio::visitor {

    std::any MembersVisitor::visitMemberExpression(Grammar::MemberExpressionContext* ctx) {
        // 1️⃣ Base value (identifier, literal, or parenthesized expression)
        const std::any atom = visit(ctx->valueAtom());

        // ✅ Validate atom before casting
        if (!atom.has_value()) {
            throw std::runtime_error("Error: valueAtom() returned empty value");
        }

        const auto identifier = std::any_cast<nodes::IdentifierLiteral>(atom);

        const auto lookupVariable = scope->lookup(identifier.value);
        if (!lookupVariable.has_value()) {
            throwScopeError("variable '" + identifier.value + "' is not declared", identifier.value, atom, source);
        }

        const std::shared_ptr<nodes::VariableDeclarationNode>& variable = lookupVariable.value();

        // ✅ Validate variable pointer
        if (!variable) {
            throw std::runtime_error("Error: variable pointer is null for '" + identifier.value + "'");
        }

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

            if (!postfix) {
                throw std::runtime_error("Error: null postfix in chain at index " + std::to_string(i));
            }

            // Check if this is a DOT access (.member)
            if (postfix->DOT()) {
                auto* identLiteral = postfix->identifierLiteral();
                if (!identLiteral) {
                    throw std::runtime_error("Error: DOT postfix has no identifier");
                }

                const std::string memberName = identLiteral->getText();

                // Check if the NEXT postfix is a function call on this member
                std::vector<std::any> arguments;

                if (i + 1 < postfixes.size()) {
                    auto* nextPostfix = postfixes[i + 1];
                    // If next postfix is LPAREN with no DOT, it's calling the current member
                    if (nextPostfix && nextPostfix->LPAREN() && !nextPostfix->DOT() && !nextPostfix->identifierLiteral()) {
                        // Get arguments from the next postfix
                        if (nextPostfix->argumentList()) {
                            for (auto* expr : nextPostfix->argumentList()->expression()) {
                                if (expr) {
                                    arguments.push_back(visit(expr));
                                }
                            }
                        }

                        i++; // Skip the next postfix since we already processed it
                    }
                }

                // Process as property or method
                current = processMembers(variable, memberName, arguments, source);
            }
            // Standalone method call (should have identifier)
            else if (postfix->LPAREN()) {
                auto* identLiteral = postfix->identifierLiteral();
                if (!identLiteral) {
                    throw std::runtime_error("Error: method call postfix has no identifier (this shouldn't happen - check grammar)");
                }

                const std::string memberName = identLiteral->getText();
                std::vector<std::any> arguments;

                if (postfix->argumentList()) {
                    for (auto* expr : postfix->argumentList()->expression()) {
                        if (expr) {
                            arguments.push_back(visit(expr));
                        }
                    }
                }

                std::cout << "Method call: " << memberName << "() with " << arguments.size() << " arguments" << std::endl;
                current = processMembers(variable, memberName, arguments, source);
            } else {
                // Unknown postfix type
                throw std::runtime_error("Error: Unknown postfix type at index " + std::to_string(i) + " (text: " + postfix->getText() + ")");
            }

            // ✅ Validate result after each operation
            if (!current.has_value()) {
                throw std::runtime_error("Error: processMembers returned empty value");
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