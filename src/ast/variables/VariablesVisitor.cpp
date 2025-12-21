//
// Created by Brayhan De Aza on 10/19/25.
//

#include "VariablesVisitor.h"
#include <ast/nodes/nodes.h>
#include "semantic/semantic.h"

namespace cromio::visitor {
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

        parser->inVarMode = true;

        // Get data type
        const auto visitDataType = visit(ctx->variableDataType());
        const auto dataType = std::any_cast<std::string>(visitDataType);

        // Get identifier
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // // Check if variable already exists in current scope
        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable '" + identifier + "' is already declared", identifier, visitDataType, source);
        }

        std::any value = visit(ctx->expression());

        // auto valueNode = std::any_cast<nodes::BinaryExpressionNode>(value);
        std::cout << value.type().name() << std::endl;

        parser->inVarMode = false;
        // Determine if it's a constant (const keyword)
        const bool isConstant = toUpper(identifier) == identifier;

        if (value.type() == typeid(nodes::ConcatenationExpressionNode)) {
            const auto conNode = std::any_cast<nodes::ConcatenationExpressionNode>(value);
            value = conNode.value;

        } else if (value.type() == typeid(nodes::BinaryExpressionNode)) {
            const auto binNode = std::any_cast<nodes::BinaryExpressionNode>(value);
            if (dataType == "int") {
                nodes::IntegerLiteralNode intNode(std::to_string(parseNumberString(binNode.value)), binNode.start, binNode.end);
                value = intNode;
            } else {
                nodes::FloatLiteralNode floatNode(std::to_string(parseNumberString(binNode.value)), binNode.start, binNode.end);
                value = floatNode;
            }

        } else if (value.type() == typeid(nodes::IntegerLiteralNode)) {
            const auto binNode = std::any_cast<nodes::IntegerLiteralNode>(value);

            if (dataType == "int") {
                nodes::IntegerLiteralNode intNode(binNode.value, binNode.start, binNode.end);
                value = intNode;
            } else {
                nodes::FloatLiteralNode floatNode(binNode.value, binNode.start, binNode.end);
                value = floatNode;
            }

            std::cout << "binNode.value" << std::endl;
        } else if (value.type() == typeid(nodes::FloatLiteralNode)) {
            const auto binNode = std::any_cast<nodes::FloatLiteralNode>(value);

            if (dataType == "int") {
                nodes::IntegerLiteralNode intNode(binNode.value, binNode.start, binNode.end);
                value = intNode;
            } else {
                nodes::FloatLiteralNode floatNode(binNode.value, binNode.start, binNode.end);
                value = floatNode;
            }
        }

        const auto v = value;
        const auto [varType, reVlue, varName] = Helpers::resolveItem(v);
        std::cout << "binNode.value " << reVlue << std::endl;

        auto node = nodes::VariableDeclarationNode(identifier, dataType, value, isConstant, start, end);

        analyzeVariableDeclaration(node, source);
        scope->declareVariable(identifier, node);

        return node;
    }

    std::any VariablesVisitor::visitVariableReAssignment(Grammar::VariableReAssignmentContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        parser->inVarMode = true;
        const std::any newValue = visit(ctx->expression());
        parser->inVarMode = false;

        // Get identifier
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // Check if variable exists
        // Get variable info from scope
        const auto variable = scope->lookup(identifier);
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

} // namespace cromio::visitor