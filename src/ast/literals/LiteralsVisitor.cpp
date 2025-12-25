//
// Created by Brayhan De Aza on 10/19/25.
//

#include "LiteralsVisitor.h"

#include <ast/nodes/nodes.h>
#include <catch2/catch_amalgamated.hpp>

std::any cromio::visitor::LiteralsVisitor::visitLiteral(Grammar::LiteralContext* ctx) {
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
    return nodes::NoneLiteralNode("None", start, end);
}

std::any cromio::visitor::LiteralsVisitor::visitNumberLiterals(Grammar::NumberLiteralsContext* ctx) {
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

std::any cromio::visitor::LiteralsVisitor::visitStringLiterals(Grammar::StringLiteralsContext* ctx) {
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

std::any cromio::visitor::LiteralsVisitor::visitIntegerLiteral(Grammar::IntegerLiteralContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    if (ctx->getText().starts_with("0b") || ctx->getText().starts_with("0x") || ctx->getText().starts_with("0o") || ctx->getText().contains("_")) {
        auto node = nodes::IntegerLiteralNode(std::to_string(parseInteger(ctx->getText())), start, end);
        return node;
    }

    auto node = nodes::IntegerLiteralNode(ctx->getText(), start, end);
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitFloatLiteral(Grammar::FloatLiteralContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    if (ctx->getText().contains("_")) {
        // ctx->getText()
        auto node = nodes::IntegerLiteralNode(std::to_string(parseFloat(ctx->getText())), start, end);
        return node;
    }

    auto node = nodes::FloatLiteralNode(ctx->getText(), start, end);
    if (!fitsInFloat64(ctx->getText())) {
        throwScopeError("<float> type is not in 64-bit range", ctx->getText(), node, source);
    }

    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitStringLiteral(Grammar::StringLiteralContext* ctx) {
    const std::string value = parseString(ctx->getText());
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    auto node = nodes::StringLiteralNode(value, start, end);
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitBooleanLiteral(Grammar::BooleanLiteralContext* ctx) {
    const std::string literal = parseString(ctx->getText());
    const std::string value = literal == "true" ? "1" : "0";
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    auto node = nodes::BooleanLiteralNode(value, start, end);
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitNoneLiteral(Grammar::NoneLiteralContext* ctx) {
    const std::string value = ctx->getText();
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    auto node = nodes::NoneLiteralNode(value, start, end);
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitIdentifierLiteral(Grammar::IdentifierLiteralContext* ctx) {
    const std::string identifier = ctx->getText();
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    auto node = nodes::IdentifierLiteral(identifier, start, end);
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitFormattedString(Grammar::FormattedStringContext* ctx) {
    const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
    const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

    // Create the formatted string node
    auto node = nodes::StringLiteralNode("", start, end);

    // Process all formatted string content parts

    for (const auto child : ctx->formattedStringContent()) {
        if (auto result = visit(child); result.has_value()) {
            std::cout << "contentNode.value: " << result.type().name() << std::endl;

            try {
                // Try to cast to different node types and add to params
                if (result.type() == typeid(nodes::StringLiteralNode)) {
                    auto contentNode = std::any_cast<nodes::StringLiteralNode>(result);
                    node.value += contentNode.value;
                } else if (result.type() == typeid(nodes::IntegerLiteralNode)) {
                    auto contentNode = std::any_cast<nodes::IntegerLiteralNode>(result);
                    node.value += contentNode.value;
                } else if (result.type() == typeid(nodes::FloatLiteralNode)) {
                    auto contentNode = std::any_cast<nodes::FloatLiteralNode>(result);
                    node.value += contentNode.value;
                } else if (result.type() == typeid(nodes::BooleanLiteralNode)) {
                    auto contentNode = std::any_cast<nodes::BooleanLiteralNode>(result);
                    node.value += contentNode.value;
                } else if (result.type() == typeid(nodes::IdentifierLiteral)) {
                    auto contentNode = std::any_cast<nodes::IdentifierLiteral>(result);
                    node.value += contentNode.value;
                } else if (result.type() == typeid(nodes::BinaryExpressionNode)) {
                    auto contentNode = std::any_cast<nodes::BinaryExpressionNode>(result);
                    node.value += contentNode.value;
                }


                // Add more types as needed (expressions, etc.)
            } catch (const std::bad_any_cast& _) {
                // ReSharper disable once CppRedundantControlFlowJump
                continue;
            }
        }
    }
    return node;
}

std::any cromio::visitor::LiteralsVisitor::visitFormattedStringContent(Grammar::FormattedStringContentContext* ctx) {
    // CASE 1: { expression }
    if (ctx->expression()) {
        return visit(ctx->expression());
    }

    // CASE 2: TEXT inside formatted string
    if (ctx->FORMATTED_STRING_TEXT()) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        auto node = nodes::StringLiteralNode(ctx->getText(), start, end);
        return node;
    }

    // Return empty if nothing matches
    return {};
}