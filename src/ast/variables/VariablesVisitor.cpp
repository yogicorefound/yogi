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
        const auto visitDataType = visit(ctx->variableDataType());
        const auto arrayTypeKind = resolveKind(visitDataType);
        const auto [dataType, _, dataTypeNode] = Helpers::resolveItem(visitDataType);
        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable '" + identifier + "' is already declared", identifier, visitDataType, source);
        }

        // Visit the expression instead of variableValue
        std::any value = visit(ctx->expression());
        parser->inVarMode = false;
        if (value.type() == typeid(nodes::MemberExpressionNode)) {
            const auto memberExpression = std::any_cast<nodes::MemberExpressionNode>(value);

            if (arrayTypeKind != memberExpression.kind) {
                throwTypeError(identifier, dataType, memberExpression.value, source);
            }

            // Store value AS-IS (BinaryExpressionNode, IdentifierLiteral, LiteralNode)
            const bool isConstant = toUpper(identifier) == identifier;
            const auto [memberType, memberValue, memberNode] = Helpers::resolveItem(memberExpression.value);
            const auto& node = nodes::VariableDeclarationNode(identifier, dataType, memberNode, isConstant, start, end);

            analyzeVariableDeclaration(node, source);

            scope->declareVariable(identifier, node);

            return node;
        }

        const bool isConstant = toUpper(identifier) == identifier;
        if (value.type() == typeid(nodes::IdentifierLiteral)) {
            if (auto identifierNode = std::any_cast<nodes::IdentifierLiteral>(value); !scope->lookupVariable(identifierNode.value).has_value()) {
                throwScopeError("variable '" + identifierNode.value + "' is not declared", identifierNode.value, value, source);
            }
        }

        if (value.type() == typeid(nodes::BinaryExpressionNode)) {
            auto node = std::any_cast<nodes::BinaryExpressionNode>(value);

            if (dataType.starts_with("float")) {
                auto floatLiteralNode = nodes::FloatLiteralNode(formatFloatNumberDecimal(node.value, -1), node.start, node.end);
                const auto& varNode = nodes::VariableDeclarationNode(identifier, dataType, floatLiteralNode, isConstant, start, end);
                analyzeVariableDeclaration(varNode, source);
                scope->declareVariable(identifier, varNode);

                return varNode;
            }

            auto floatLiteralNode = nodes::IntegerLiteralNode(std::to_string(parseInteger(node.value)), node.start, node.end);
            const auto& varNode = nodes::VariableDeclarationNode(identifier, dataType, floatLiteralNode, isConstant, start, end);

            analyzeVariableDeclaration(varNode, source);
            scope->declareVariable(identifier, varNode);

            return varNode;
        }

        const auto [type, resolveValue, __] = Helpers::resolveItem(value);
        if (value.type() == typeid(nodes::RegexLiteralNode)) {
            std::string rValue = resolveValue;
            if (rValue.size() >= 2) {
                rValue.erase(0, 1); // remove first character
                rValue.erase(rValue.size() - 1, 1); // remove last character
            }

            const auto regexNode = nodes::RegexLiteralNode(rValue, start, end);
            const auto& node = nodes::VariableDeclarationNode(identifier, type, regexNode, isConstant, start, end);

            analyzeVariableDeclaration(node, source);
            scope->declareVariable(identifier, node);

            return node;
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
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const auto dataType = ctx->getText();

        if (dataType == "str") {
            return nodes::StringLiteralNode(dataType, start, end);
        }

        if (dataType.starts_with("int") || dataType.starts_with("uint")) {
            return nodes::IntegerLiteralNode(dataType, start, end);
        }

        if (dataType.starts_with("float")) {
            return nodes::FloatLiteralNode(dataType, start, end);
        }

        if (dataType == "bool") {
            return nodes::BooleanLiteralNode(dataType, start, end);
        }

        return nodes::NoneLiteralNode("", start, end);
    }

} // namespace yogi::visitor