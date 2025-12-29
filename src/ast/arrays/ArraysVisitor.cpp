//
// Created by Brayhan De Aza on 10/19/25.
//

#include "ArraysVisitor.h"
#include "semantic/BaseSemantic.h"
#include "semantic/semantic.h"

namespace yogi::visitor {
    std::any ArraysVisitor::visitArrays(Grammar::ArraysContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayDeclaration(Grammar::ArrayDeclarationContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get array type information
        const auto type = visit(ctx->arrayType());
        const auto [arrayType, arraySize] = std::any_cast<std::pair<std::string, std::string>>(type); // {elementType, size}
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // Check if array already declared
        if (scope->existsInCurrent(identifier)) {
            const auto message = "Array '" + identifier + "' is already declared";
            throwScopeError(message, identifier, type, source);
        }

        // Value by passing array of elements
        auto arrayValues = visit(ctx->arrayValues());
        std::cout << "array: " << arrayValues.has_value() << std::endl;

        if (arrayValues.has_value()) {
            std::vector<nodes::ArrayElementNode> elements;

            if (arrayValues.type() == typeid(std::vector<nodes::StringLiteralNode>)) {
                for (const auto& stringLiterals = std::any_cast<std::vector<nodes::StringLiteralNode>>(arrayValues); const auto& item : stringLiterals) {
                    const auto [itemType, itemValue, itemNode] = Helpers::resolveItem(item);
                    const auto elementNode = nodes::ArrayElementNode(itemNode, itemType, start, end);

                    elements.push_back(elementNode);
                }
            }

            if (arrayValues.type() == typeid(nodes::MemberExpressionNode)) {
                const auto& memberNode = std::any_cast<nodes::MemberExpressionNode>(arrayValues);

                if (memberNode.kind == nodes::Kind::ARRAY_STRING_ELEMENTS) {
                    if (arrayType != "str") {
                        throwTypeError(identifier, arrayType, memberNode, source);
                    }

                    for (const auto& stringLiterals = std::any_cast<std::vector<nodes::StringLiteralNode>>(memberNode.value); const auto& item : stringLiterals) {
                        const auto [itemType, itemValue, itemNode] = Helpers::resolveItem(item);
                        const auto elementNode = nodes::ArrayElementNode(itemNode, itemType, start, end);
                        elements.push_back(elementNode);
                    }
                }

                if (memberNode.kind == nodes::Kind::ARRAY_INTEGER_ELEMENTS) {
                    if (arrayType != "str") {
                        throwTypeError(identifier, arrayType, memberNode, source);
                    }
                    for (const auto& stringLiterals = std::any_cast<std::vector<nodes::IntegerLiteralNode>>(memberNode.value); const auto& item : stringLiterals) {
                        const auto [itemType, itemValue, itemNode] = Helpers::resolveItem(item);
                        const auto elementNode = nodes::ArrayElementNode(itemNode, itemType, start, end);
                        elements.push_back(elementNode);
                    }
                }

                if (memberNode.kind == nodes::Kind::ARRAY_BOOLEAN_ELEMENTS) {
                    if (arrayType != "str") {
                        throwTypeError(identifier, arrayType, memberNode, source);
                    }
                    for (const auto& stringLiterals = std::any_cast<std::vector<nodes::IntegerLiteralNode>>(memberNode.value); const auto& item : stringLiterals) {
                        const auto [itemType, itemValue, itemNode] = Helpers::resolveItem(item);
                        const auto elementNode = nodes::ArrayElementNode(itemNode, itemType, start, end);
                        elements.push_back(elementNode);
                    }
                }
            }

            // Register ArrayDeclarationNode in scope
            nodes::ArrayDeclarationNode node(identifier, arrayType, toUpper(identifier) == identifier, arraySize, elements, start, end);
            scope->declareArray(identifier, node);

            return node;
        }
        // Value by passing literal with brackets

        std::cout << "arrayValues: " << std::endl;

        if (const auto& arrayItemsWithBrackets = ctx->arrayValues()->arrayItemsWithBrackets()->expression(); !arrayItemsWithBrackets.empty()) {
            std::vector<nodes::ArrayElementNode> elements;
            // Create array declaration node

            parser->inVarMode = true;
            for (auto itemCtx : arrayItemsWithBrackets) {
                const auto item = visit(itemCtx);

                // Extract value and type from the item
                std::string itemType;
                std::any itemValue;

                if (item.type() == typeid(nodes::IdentifierLiteral)) {
                    auto node = std::any_cast<nodes::IdentifierLiteral>(item);
                    const auto variable = scope->lookupVariable(node.value);
                    if (!variable.has_value()) {
                        throwScopeError("Error: '" + node.value + "' is not declared", node.value, node, source);
                    }

                    const auto& varNode = variable.value();
                    itemValue = varNode->value;
                    itemType = varNode->varType;

                } else {
                    std::string boolValue;
                    std::string rValue;
                    processArrayItems(arrayType, itemType, itemValue, boolValue, rValue, item, scope, source);
                }

                // Add element to array
                auto elementNode = nodes::ArrayElementNode(itemValue, itemType, start, end);
                elements.push_back(std::move(elementNode));
            }
            parser->inVarMode = false;

            // Check if declared size matches actual elements

            if (arraySize != "auto") {
                if (elements.size() > std::stoull(arraySize)) {
                    throwError("ArraySizeViolation", "attempted to assign " + std::to_string(elements.size()) + " elements, but the array was declared with a maximum size of " + arraySize + ".", start, source);
                }
            }

            nodes::ArrayDeclarationNode node(identifier, arrayType, toUpper(identifier) == identifier, arraySize, elements, start, end);
            scope->declareArray(identifier, node);

            return node;
        }

        std::cout << "arrayItemsWithBrackets: " << std::endl;

        // const auto& arrayValues = visit(ctx->arrayValues());
        // std::cout << "arrayValues: " << arrayValues.type().name() << std::endl;

        throwTypeError(identifier, arrayType, type, source);
        return "";

        // Register ArrayDeclarationNode in scope
    }

    std::any ArraysVisitor::visitArrayItems(Grammar::ArrayItemsContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayValues(Grammar::ArrayValuesContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayReAssignment(Grammar::ArrayReAssignmentContext* ctx) {
        const auto identifier = ctx->IDENTIFIER()->getText();

        const auto array = scope->lookupArray("array:" + identifier);
        if (!array.has_value()) {
            const auto message = "Error: '" + identifier + "' is not declared";
            std::cout << message << std::endl;
            std::exit(1);
        }

        const auto arrayNode = std::any_cast<nodes::ArrayDeclarationNode>(array.value());
        if (arrayNode.isConstant) {
            throwReassignmentError("cannot reassign constant variable '" + identifier + "'", arrayNode, source);
        }

        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};
        const std::string arrayType = arrayNode.type;

        std::vector<nodes::ArrayElementNode> elements;

        parser->inVarMode = true;
        for (auto* exprCtx : ctx->expression()) {
            const auto itemResult = visit(exprCtx);

            std::string itemType;
            std::any itemValue;
            std::string boolValue;
            std::string rValue;

            processArrayItems(arrayType, itemType, itemValue, boolValue, rValue, itemResult, scope, source);

            // Add element to array
            auto elementNode = nodes::ArrayElementNode(itemValue, itemType, start, end);
            elements.push_back(std::move(elementNode));
        }
        parser->inVarMode = false;

        // Check if declared size matches actual elements
        if (arrayNode.size != "auto") {
            if (elements.size() > std::stoull(arrayNode.size)) {
                throwError("ArraySizeViolation", "attempted to assign " + std::to_string(elements.size()) + " elements, but the array was declared with a maximum size of " + arrayNode.size + ".", start, source);
            }
        }

        nodes::ArrayDeclarationNode node(identifier, arrayNode.type, arrayNode.isConstant, arrayNode.size, elements, start, end);
        scope->updateArray(identifier, node);

        return node;
    }

    std::any ArraysVisitor::visitArrayDeclarationTypeSize(Grammar::ArrayDeclarationTypeSizeContext* ctx) {
        // Return size as string: either "auto" or the actual size value
        if (ctx->expression() == nullptr) {
            return std::string("auto");
        }

        const auto expression = visit(ctx->expression());

        // Extract numeric value from expression
        if (expression.type() == typeid(nodes::IntegerLiteralNode)) {
            auto node = std::any_cast<nodes::IntegerLiteralNode>(expression);
            return node.value;
        }
        if (expression.type() == typeid(nodes::BinaryExpressionNode)) {
            auto node = std::any_cast<nodes::BinaryExpressionNode>(expression);
            return node.value;
        }

        return std::string("auto");
    }

    std::any ArraysVisitor::visitArrayType(Grammar::ArrayTypeContext* ctx) {
        // Get element type
        const std::string elementType = ctx->arrayDataType()->getText();

        // Get array size
        const auto arraySizeResult = visit(ctx->arrayDeclarationTypeSize());
        const auto arraySize = std::any_cast<std::string>(arraySizeResult);

        // Return as pair: {elementType, size}
        return std::make_pair(elementType, arraySize);
    }

    std::any ArraysVisitor::visitArrayDataType(Grammar::ArrayDataTypeContext* ctx) {
        // Return the data type as string
        return ctx->getText();
    }

} // namespace yogi::visitor