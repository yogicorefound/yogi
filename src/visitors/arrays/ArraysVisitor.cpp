//
// ArraysVisitor.cpp
//

#include "ArraysVisitor.h"
#include "semantic/BaseSemantic.h"
#include "semantic/semantic.h"

namespace yogi::visitor {

    // -----------------------
    // Build array elements recursively for multidimensional arrays
    // -----------------------
    std::vector<nodes::ArrayElementNode>
    ArraysVisitor::buildArrayElementsRecursively(Grammar::ArrayItemsWithBracketsContext* ctx, const std::string& elementType, const std::vector<size_t>& dimensions, const nodes::Position& start, const nodes::Position& end) {
        std::vector<nodes::ArrayElementNode> elements;

        for (auto* itemCtx : ctx->arrayItem()) {
            if (itemCtx->arrayItemsWithBrackets()) {
                std::vector<size_t> subDimensions;
                if (!dimensions.empty()) {
                    subDimensions.assign(dimensions.begin() + 1, dimensions.end());
                }
                const auto subElements = buildArrayElementsRecursively(itemCtx->arrayItemsWithBrackets(), elementType, subDimensions, start, end);
                elements.push_back(nodes::ArrayElementNode(subElements, elementType, start, end));
            } else {
                const auto valueAny = visit(itemCtx);
                const auto [valueType, value, node] = resolveItem(valueAny);

                if (valueType != elementType) {
                    throwTypeError("Array element type mismatch", elementType, itemCtx, source);
                }

                elements.push_back(nodes::ArrayElementNode(node, valueType, start, end));
            }
        }

        if (!dimensions.empty() && elements.size() != dimensions[0]) {
            throwError("ArraySizeViolation", "expected " + std::to_string(dimensions[0]) + " elements, but got " + std::to_string(elements.size()), start, source);
        }

        return elements;
    }

    // -----------------------
    // Visitor implementations
    // -----------------------
    std::any ArraysVisitor::visitArrays(Grammar::ArraysContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayDeclaration(Grammar::ArrayDeclarationContext* ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get type and dimensions
        const auto typeResult = visit(ctx->arrayType());
        const auto [elementType, dimensions] = std::any_cast<std::pair<std::string, std::vector<size_t>>>(typeResult);
        const std::string identifier = ctx->IDENTIFIER()->getText();

        if (scope->existsInCurrent(identifier)) {
            throwScopeError("Array '" + identifier + "' is already declared", identifier, typeResult, source);
        }

        // Build elements recursively
        std::vector<nodes::ArrayElementNode> elements;
        if (ctx->arrayValues()->arrayItemsWithBrackets()) {
            elements = buildArrayElementsRecursively(ctx->arrayValues()->arrayItemsWithBrackets(), elementType, dimensions, start, end);
        }

        // Register array in scope
        nodes::ArrayDeclarationNode node(identifier, elementType, toUpper(identifier) == identifier, dimensions, elements, start, end);
        scope->declareArray(identifier, node);

        return node;
    }

    std::any ArraysVisitor::visitArrayReAssignment(Grammar::ArrayReAssignmentContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayType(Grammar::ArrayTypeContext* ctx) {
        const std::string elementType = ctx->arrayDataType()->getText();
        std::vector<size_t> dimensions;

        if (ctx->arrayDeclarationTypeSizes()) {
            for (auto* exprCtx : ctx->arrayDeclarationTypeSizes()->expression()) {
                const auto exprAny = visit(exprCtx);
                if (exprAny.type() == typeid(nodes::IntegerLiteralNode)) {
                    auto node = std::any_cast<nodes::IntegerLiteralNode>(exprAny);
                    dimensions.push_back(std::stoul(node.value));
                } else {
                    throwError("InvalidArrayDimension", "Array dimensions must be integer literals", ctx->start->getLine(), source);
                }
            }
        }

        return std::make_pair(elementType, dimensions);
    }

    std::any ArraysVisitor::visitArrayItem(Grammar::ArrayItemContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayElement(Grammar::ArrayElementContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext* ctx) {
        std::vector<size_t> dimensions;
        for (auto* exprCtx : ctx->expression()) {
            const auto exprAny = visit(exprCtx);
            if (exprAny.type() == typeid(nodes::IntegerLiteralNode)) {
                dimensions.push_back(std::stoul(std::any_cast<nodes::IntegerLiteralNode>(exprAny).value));
            } else {
                throwError("InvalidArrayDimension", "Array dimensions must be integer literals", ctx->start->getLine(), source);
            }
        }
        return dimensions;
    }

    std::any ArraysVisitor::visitArrayDataType(Grammar::ArrayDataTypeContext* ctx) {
        return ctx->getText();
    }

    std::any ArraysVisitor::visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext* ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayValues(Grammar::ArrayValuesContext* ctx) {
        return visitChildren(ctx);
    }

} // namespace yogi::visitor
