//
// Created by Brayhan De Aza on 10/19/25.
//

#include "LiteralsVisitor.h"
#include <catch2/catch_amalgamated.hpp>
#include <visitors/nodes/nodes.h>

namespace yogi::visitor {
    std::any LiteralsVisitor::visitLiterals(Grammar::LiteralsContext *ctx) {
        if (ctx->numberLiterals()) {
            return visit(ctx->numberLiterals());
        }
        if (ctx->stringLiterals()) {
            return visit(ctx->stringLiterals());
        }

        if (ctx->booleanLiteral()) {
            return visit(ctx->booleanLiteral());
        }

        if (ctx->identifierLiteral()) {
            return visit(ctx->identifierLiteral());
        }

        // Return a NoneLiteralNode as default
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("Unknown", start, end);
    }

    std::any LiteralsVisitor::visitNumberLiterals(Grammar::NumberLiteralsContext *ctx) {
        if (ctx->integerLiteral()) {
            return visit(ctx->integerLiteral());
        }
        if (ctx->floatLiteral()) {
            return visit(ctx->floatLiteral());
        }

        // Return a NoneLiteralNode as default
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("None", start, end);
    }

    std::any LiteralsVisitor::visitStringLiterals(Grammar::StringLiteralsContext *ctx) {
        if (ctx->stringLiteral()) {
            return visit(ctx->stringLiteral());
        }
        if (ctx->formattedString()) {
            return visit(ctx->formattedString());
        }

        if (ctx->identifierLiteral()) {
            return visit(ctx->identifierLiteral());
        }

        // Return a NoneLiteralNode as default
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("None", start, end);
    }

    std::any LiteralsVisitor::visitIntegerLiteral(Grammar::IntegerLiteralContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto rValue = ctx->getText();

        if (rValue.starts_with("0b") || rValue.starts_with("0x") || rValue.starts_with("0o") || rValue.contains("_")) {
            auto node = nodes::IntegerLiteralNode(std::to_string(parseInteger(rValue)), start, end);
            return node;
        }

        if (rValue.contains("e") || rValue.contains("E")) {
            auto node = nodes::FloatLiteralNode(rValue, start, end);
            return node;
        }

        auto node = nodes::IntegerLiteralNode(rValue, start, end);
        return node;
    }

    std::any LiteralsVisitor::visitFloatLiteral(Grammar::FloatLiteralContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        if (ctx->getText().contains("_")) {
            // ctx->getText()
            auto node = nodes::IntegerLiteralNode(ctx->getText(), start, end);
            return node;
        }

        auto node = nodes::FloatLiteralNode(ctx->getText(), start, end);
        if (!fitsInFloat64(ctx->getText())) {
            throwScopeError("<float> type is not in 64-bit range", ctx->getText(), node, source);
        }

        return node;
    }

    std::any LiteralsVisitor::visitStringLiteral(Grammar::StringLiteralContext *ctx) {
        const std::string value = parseString(ctx->getText());
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto node = nodes::StringLiteralNode(value, start, end);
        return node;
    }

    std::any LiteralsVisitor::visitBooleanLiteral(Grammar::BooleanLiteralContext *ctx) {
        const std::string literal = parseString(ctx->getText());

        const std::string value = literal == "true" ? "1" : "0";
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto node = nodes::BooleanLiteralNode(value, start, end);
        return node;
    }

    std::any LiteralsVisitor::visitNoneLiteral(Grammar::NoneLiteralContext *ctx) {
        const std::string value = ctx->getText();
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto node = nodes::NoneLiteralNode(value, start, end);
        return node;
    }

    std::any LiteralsVisitor::visitIdentifierLiteral(Grammar::IdentifierLiteralContext *ctx) {
        const std::string identifier = ctx->getText();
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        return nodes::IdentifierLiteral(identifier, start, end);
    }

    std::any LiteralsVisitor::visitFormattedString(
        Grammar::FormattedStringContext *ctx
    ) {
        const nodes::Position start{
            ctx->start->getLine(),
            ctx->start->getCharPositionInLine()
        };

        const nodes::Position end{
            ctx->stop->getLine(),
            ctx->stop->getCharPositionInLine()
        };

        // Regex literal
        if (const auto prefix = ctx->FORMATTED_STRING_START()->getText();
            prefix == "r\"") {

            std::string value;

            for (const auto child: ctx->formattedStringContent()) {
                value += child->getText();
            }

            return nodes::RegexLiteralNode(value, start, end);
        }

        std::vector<std::any> parts = {};
        for (const auto child: ctx->formattedStringContent()) {

            auto result = visit(child);

            if (!result.has_value()) {
                continue;
            }

            // preserve order
            parts.push_back(result);

        }

        nodes::FormattedStringNode node(parts, start, end);
        return node;
    }


    LiteralsVisitor::EvalExpressionResult LiteralsVisitor::evaluateExpressionWithScope(const std::any &node) const {
        std::unordered_set<std::string> visited;
        return evaluateExpressionWithScopeImplementation(node, visited);
    }

    LiteralsVisitor::EvalExpressionResult LiteralsVisitor::evaluateExpressionWithScopeImplementation(const std::any &node, std::unordered_set<std::string> &visited) const {
        // Check if node is an identifier
        if (const auto n = std::any_cast<nodes::IdentifierLiteral>(&node)) {

            // Detect circular reference
            if (visited.contains(n->value)) {
                throw std::runtime_error("Circular reference detected: " + n->value);
            }

            visited.insert(n->value);

            // Look up in scope
            if (const auto variable = scope->lookupVariable(n->value); variable.has_value()) {
                return std::any_cast<EvalExpressionResult>(
                    evaluateExpressionWithScopeImplementation(variable.value(), visited)
                );
            }

            // Not found → evaluate as normal expression
            return std::any_cast<EvalExpressionResult>(
                evaluateExpression(node)
            );
        }

        // Not an identifier → evaluate normally
        return std::any_cast<EvalExpressionResult>(
            evaluateExpression(node)
        );
    }

    std::any LiteralsVisitor::visitFormattedStringContent(Grammar::FormattedStringContentContext *ctx) {
        // CASE 1: { expression }
        if (ctx->expression()) {
            return visit(ctx->expression());
        }

        // CASE 2: TEXT inside formatted string
        if (ctx->FORMATTED_STRING_TEXT() || ctx->REGEX_LITERAL()) {
            const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
            const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

            auto node = nodes::StringLiteralNode(ctx->getText(), start, end);
            return node;
        }

        // Return empty if nothing matches
        return {};
    }
} // namespace yogi::visitor