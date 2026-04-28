//
// Created by Brayhan De Aza on 10/19/25.
// CLEAN AST VISITOR VERSION
//

#include "VariablesVisitor.h"
#include <visitors/nodes/nodes.h>
#include "semantic/semantic.h"

namespace yogi::visitor {

    using namespace nodes;

    // --------------------------------------------------------
    std::any VariablesVisitor::visitVariables(Grammar::VariablesContext* ctx) {
        if (ctx->variableDeclaration())
            return visit(ctx->variableDeclaration());

        if (ctx->variableDeclarationWithoutAssignment())
            return visit(ctx->variableDeclarationWithoutAssignment());

        if (ctx->variableReAssignment())
            return visit(ctx->variableReAssignment());

        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        return NoneLiteralNode("None", start, end);
    }

    // --------------------------------------------------------
    std::any VariablesVisitor::visitVariableDeclarationWithoutAssignment(
        Grammar::VariableDeclarationWithoutAssignmentContext* ctx) {

        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        std::string type = std::any_cast<std::string>(visit(ctx->variableDataType()));
        std::string identifier = ctx->IDENTIFIER()->getText();

        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable already declared", identifier, type, source);
        }

        auto node = VariableDeclarationNode(identifier, type, std::any(), false, start, end);
        scope->declareVariable(identifier, node);

        return node;
    }

    // --------------------------------------------------------
    std::any VariablesVisitor::visitVariableDeclaration(
        Grammar::VariableDeclarationContext* ctx) {

        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        std::string identifier = ctx->IDENTIFIER()->getText();

        auto typeAny = visit(ctx->variableDataType());
        std::string typeValue = std::any_cast<std::string>(typeAny);

        if (scope->existsInCurrent(identifier)) {
            throwScopeError("variable already declared", identifier, typeValue, source);
        }

        // IMPORTANT: PURE AST ONLY
        std::any value = visit(ctx->expression());

        bool isConstant = toUpper(identifier) == identifier;

        auto node = VariableDeclarationNode(
            identifier,
            typeValue,
            value,          // ❗ PURE AST (no transformation)
            isConstant,
            start,
            end
        );

        analyzeVariableDeclaration(node, source);
        scope->declareVariable(identifier, node);

        return node;
    }

    // --------------------------------------------------------
    std::any VariablesVisitor::visitVariableReAssignment(
        Grammar::VariableReAssignmentContext* ctx) {

        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        std::string identifier = ctx->IDENTIFIER()->getText();

        std::any newValue = visit(ctx->expression());

        auto variable = scope->lookupVariable(identifier);
        if (!variable.has_value()) {
            throwScopeError("variable not declared", identifier, newValue, source);
        }

        const auto& varNode = variable.value();

        if (varNode->isConstant) {
            throwReassignmentError("constant cannot be modified", newValue, source);
        }

        auto node = VariableDeclarationNode(
            identifier,
            varNode->varType,
            newValue,   // ❗ PURE AST ONLY
            false,
            start,
            end
        );

        analyzeVariableReassignment(node, source);
        scope->updateVariable(identifier, node);

        return node;
    }

    // --------------------------------------------------------
    std::any VariablesVisitor::visitVariableDataType(
        Grammar::VariableDataTypeContext* ctx) {

        std::string type = ctx->getText();

        const Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        if (type == "str")
            return "str";

        if (type.starts_with("int") || type.starts_with("uint"))
            return "int";

        if (type.starts_with("float"))
            return "float";

        if (type == "bool")
            return "bool";

        return "unknown";
    }

} // namespace yogi::visitor