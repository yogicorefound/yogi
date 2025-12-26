//
// Created by Brayhan De Aza on 10/19/25.
//

#include "VariablesVisitor.h"
#include <ast/nodes/nodes.h>
#include "semantic/semantic.h"

namespace yogi::visitor {
    std::any VariablesVisitor::visitVariables(Grammar::VariablesContext* ctx) {
        if (ctx->variableDeclaration()) {
            return visit(ctx->variableDeclaration());
        }

        if (ctx->variableDeclarationWithoutAssignment()) {
            return visit(ctx->variableDeclarationWithoutAssignment());
        }

        if (ctx->variableReAssignment()) {
            return visit(ctx->variableReAssignment());
        }

        // Return empty node
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return nodes::NoneLiteralNode("None", start, end);
    }

    std::any VariablesVisitor::visitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get data type
        const auto visitDataType = visit(ctx->variableDataType());
        const auto dataType = std::any_cast<std::string>(visitDataType);

        // Get identifier
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // Check if variable already exists in current scope
        if (scope->existsInCurrent(identifier)) {
            const auto message = "variable '" + identifier + "' is already declared";
            throwScopeError(message, identifier, visitDataType, source);
        }

        // Create variable declaration node with no initial value
        auto node = nodes::VariableDeclarationNode(identifier, dataType, std::any(), false, start, end);

        // Register variable in scope
        scope->declareVariable(identifier, node);

        return node;
    }

    std::any VariablesVisitor::visitVariableDeclaration(Grammar::VariableDeclarationContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const std::string identifier = ctx->IDENTIFIER()->getText();

        parser->inVarMode = true;

        // Get data type
        const auto visitDataType = visit(ctx->variableDataType());
        const auto dataType = std::any_cast<std::string>(visitDataType);

        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable '" + identifier + "' is already declared", identifier, visitDataType, source);
        }

        // Visit the expression instead of variableValue
        std::any value = visit(ctx->expression());

        parser->inVarMode = false;

        const bool isConstant = toUpper(identifier) == identifier;

        // If it's an identifier, check it exists in scope (optional)
        if (value.type() == typeid(nodes::IdentifierLiteral)) {
            if (auto identifierNode = std::any_cast<nodes::IdentifierLiteral>(value); !scope->lookupVariable(identifierNode.value).has_value()) {
                throwScopeError("variable '" + identifierNode.value + "' is not declared", identifierNode.value, value, source);
            }
        }

        if (value.type() == typeid(nodes::BinaryExpressionNode)) {
            auto node = std::any_cast<nodes::BinaryExpressionNode>(value);

            std::any floatLiteralNode;

            if (dataType.starts_with("float")) {
                floatLiteralNode = nodes::FloatLiteralNode(formatFloatNumberDecimal(node.value, -1), node.start, node.end);

            } else {
                floatLiteralNode = nodes::IntegerLiteralNode(std::to_string(parseInteger(node.value)), node.start, node.end);
            }

            const auto& varNode = nodes::VariableDeclarationNode(identifier, dataType, floatLiteralNode, isConstant, start, end);
            analyzeVariableDeclaration(varNode, source);
            scope->declareVariable(identifier, varNode);

            return varNode;
        }

        // Store value AS-IS (BinaryExpressionNode, IdentifierLiteral, LiteralNode)
        const auto& node = nodes::VariableDeclarationNode(identifier, dataType, value, isConstant, start, end);
        analyzeVariableDeclaration(node, source);
        scope->declareVariable(identifier, node);

        return node;
    }

    std::any VariablesVisitor::visitVariableReAssignment(Grammar::VariableReAssignmentContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const std::string identifier = ctx->IDENTIFIER()->getText();

        parser->inVarMode = true;
        const std::any newValue = visit(ctx->expression());
        std::cout << newValue.type().name() << std::endl;
        parser->inVarMode = false;

        // Get identifier

        // Check if variable exists
        // Get variable info from scope
        const auto variable = scope->lookupVariable(identifier);
        if (!variable.has_value()) {
            throwScopeError("variable '" + identifier + "' is not declared", identifier, newValue, source);
        }

        const auto& varNode = variable.value();
        auto node = nodes::VariableDeclarationNode(identifier, "", newValue, false, start, end);

        if (varNode->isConstant) {
            throwReassignmentError("cannot reassign constant variable '" + identifier + "'", newValue, source);
        }

        if (varNode->value.type() == typeid(nodes::BinaryExpressionNode)) {
            node.value = varNode->value;
        }

        node.varType = varNode->varType;

        analyzeVariableReassignment(node, source);
        scope->updateVariable("var:" + identifier, node);
        return node;
    }

    std::any VariablesVisitor::visitVariableDataType(Grammar::VariableDataTypeContext* ctx) {
        // Return the type as a string
        return ctx->getText();
    }

} // namespace yogi::visitor