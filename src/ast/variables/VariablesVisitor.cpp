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

        if (ctx->variableAccessToMember()) {
            return visit(ctx->variableAccessToMember());
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
        const std::string dataType = std::any_cast<std::string>(visitDataType);

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
        const std::string dataType = std::any_cast<std::string>(visitDataType);

        // Get identifier
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // // Check if variable already exists in current scope
        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable '" + identifier + "' is already declared", identifier, visitDataType, source);
        }

        // Get initial value expression
        const std::any value = visit(ctx->expression());

        parser->inVarMode = false;

        // Determine if it's a constant (const keyword)
        const bool isConstant = toUpper(identifier) == identifier;

        // Create variable declaration node
        auto node = nodes::VariableDeclarationNode(identifier, dataType, value, isConstant, start, end);

        // Perform semantic analysis
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
        if (!scope->exists(identifier)) {
            throwScopeError("variable '" + identifier + "' is not declared", identifier, newValue, source);
        }

        // Get variable info from scope
        const auto variable = scope->lookup(identifier);

        auto node = nodes::VariableDeclarationNode(identifier, "", newValue, false, start, end);
        if (variable.has_value()) {
            if (const auto varNode = variable.value(); varNode->isConstant) {
                throwReassignmentError("cannot reassign constant variable '" + identifier + "'", newValue, source);
            }

            if (node.value.type() == typeid(nodes::IdentifierLiteral)) {
                node.value = variable.value()->value;
            }

            node.varType = variable.value()->varType;



            analyzeVariableReassignment(node, source);
            std::cout << "Reassigning variable '" << identifier << "'" << std::endl;
            scope->updateVariable(identifier, node);
            return node;
        }
        throwScopeError("variable '" + identifier + "' is not declared", identifier, newValue, source);
        return 0;
    }

    std::any VariablesVisitor::visitVariableDataType(Grammar::VariableDataTypeContext* ctx) {
        // Return the type as a string
        return ctx->getText();
    }

    std::any VariablesVisitor::visitVariableAccessToMember(Grammar::VariableAccessToMemberContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get identifier
        const auto identifier = ctx->IDENTIFIER()[0];
        const std::string identifierText = identifier->getText();

        // Get member
        const auto member = ctx->IDENTIFIER()[1];
        const std::string memberText = member->getText();

        // Create a member access node (you might want to create a specific node type for this)
        const auto identifierNode = nodes::IdentifierLiteral(identifierText, start, end);
        const auto memberNode = nodes::IdentifierLiteral(memberText, start, end);

        // For now, return as a tuple or create a MemberAccessNode
        // This is a placeholder - you should create a proper MemberAccessNode struct
        struct MemberAccessNode {
            nodes::IdentifierLiteral object;
            nodes::IdentifierLiteral member;
            nodes::Position start;
            nodes::Position end;
        };

        return MemberAccessNode{identifierNode, memberNode, start, end};
    }
} // namespace cromio::visitor