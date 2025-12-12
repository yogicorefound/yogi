//
// Created by Brayhan De Aza on 10/19/25.
//

#include "ArraysVisitor.h"
#include "semantic/BaseSemantic.h"
#include "semantic/semantic.h"

namespace cromio::visitor {
    std::any ArraysVisitor::visitArrayDeclaration(Grammar::ArrayDeclarationContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get array type information
        const auto arrayType = visit(ctx->arrayType());
        const auto [first, second] = std::any_cast<std::pair<std::string, std::string>>(arrayType); // {elementType, size}
        const std::string elementType = first;
        const std::string arraySize = second;

        // Get identifier
        const std::string identifier = ctx->IDENTIFIER()->getText();

        // Check if array already declared
        if (scope->existsInCurrent(identifier)) {
            const auto message = "Array '" + identifier + "' is already declared";
            throwScopeError(message, identifier, arrayType, source);
        }

        // Create array declaration node
        auto arrayNode = nodes::ArrayDeclarationNode(identifier, elementType, start, end);

        parser->inVarMode = true;

        // Process array elements
        for (auto* exprCtx : ctx->expression()) {
            const auto itemResult = visit(exprCtx);

            // Extract value and type from the item
            std::string itemType;
            std::any itemValue;

            if (itemResult.type() == typeid(nodes::IntegerLiteralNode)) {
                auto item = std::any_cast<nodes::IntegerLiteralNode>(itemResult);
                itemType = "int";
                itemValue = itemResult;
            } else if (itemResult.type() == typeid(nodes::FloatLiteralNode)) {
                auto item = std::any_cast<nodes::FloatLiteralNode>(itemResult);
                itemType = "float";
                itemValue = itemResult;
            } else if (itemResult.type() == typeid(nodes::StringLiteralNode)) {
                auto item = std::any_cast<nodes::StringLiteralNode>(itemResult);
                itemType = "string";
                itemValue = itemResult;
            } else if (itemResult.type() == typeid(nodes::BooleanLiteralNode)) {
                auto item = std::any_cast<nodes::BooleanLiteralNode>(itemResult);
                itemType = "bool";
                itemValue = itemResult;
            } else if (itemResult.type() == typeid(nodes::BinaryExpressionNode)) {
                auto item = std::any_cast<nodes::BinaryExpressionNode>(itemResult);
                itemType = item.resultType;
                itemValue = itemResult;
            } else if (itemResult.type() == typeid(nodes::IdentifierLiteral)) {
                auto item = std::any_cast<nodes::IdentifierLiteral>(itemResult);

                auto varInfo = scope->lookup(item.value);
                if (!varInfo.has_value()) {
                    const auto message = "Variable '" + item.value + "' is not declared";
                    throwScopeError(message, item.value, item, source);
                }

                itemType = varInfo.value()->varType;
                itemValue = itemResult;
            } else {
                throwError("Error", "Unsupported array element type", start, source);
            }

            // Check type compatibility
            if (!checkArrayDataType(elementType, itemType)) {
                throwTypeError(identifier, elementType, itemType, source);
            }

            // Add element to array
            auto elementNode = nodes::ArrayElementNode(itemValue, start, end);
            arrayNode.elements.push_back(std::move(elementNode));
        }

        parser->inVarMode = false;

        // Set array size
        if (arraySize == "auto") {
            arrayNode.size = arrayNode.elements.size();
        } else {
            try {
                arrayNode.size = std::stoull(arraySize);

                // Check if declared size matches actual elements
                if (arrayNode.size != arrayNode.elements.size()) {
                    throwError("Error", "Array size mismatch: declared " + arraySize + " but provided " + std::to_string(arrayNode.elements.size()) + " elements", start, source);
                }
            } catch (const std::exception&) {
                throwError("Error", "Invalid array size: " + arraySize, arrayNode, source);
            }
        }

        // Perform semantic analysis
        // auto analyzedNode = analyzeArrayDeclaration(arrayNode, source);

        // Register in scope (wrap in VariableDeclarationNode)
        nodes::VariableDeclarationNode varNode(identifier, elementType + "[]", std::any(arrayNode), false, start, end);
        scope->declareVariable(identifier, varNode);

        return varNode;
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
        const std::string arraySize = std::any_cast<std::string>(arraySizeResult);

        // Return as pair: {elementType, size}
        return std::make_pair(elementType, arraySize);
    }

    std::any ArraysVisitor::visitArrayDataType(Grammar::ArrayDataTypeContext* ctx) {
        // Return the data type as string
        return ctx->getText();
    }

} // namespace cromio::visitor