//
// ArraysVisitor.cpp
//

#include "ArraysVisitor.h"
#include "semantic/BaseSemantic.h"
#include "semantic/variables/helpers.h"
// #include "semantic/semantic.h"

namespace yogi::visitor {

    // -----------------------
    // Build array elements recursively for multidimensional arrays
    // -----------------------
    // -----------------------
    // Build array elements recursively for multidimensional arrays with default values
    // -----------------------
    std::vector<nodes::ArrayElementNode> ArraysVisitor::buildArrayElementsRecursively(Grammar::ArrayItemsWithBracketsContext *ctx, const utils::Types &elementType, const std::vector<size_t> &dimensions, const nodes::Position &start, const nodes::Position &end) {
        std::vector<nodes::ArrayElementNode> elements;

        // auto getDefaultValue = [start, end](const utils::Types &type) -> std::any {
        //     if (type == "int")
        //         return nodes::IntegerLiteralNode{"0", start, end};
        //     if (type == "float")
        //         return nodes::FloatLiteralNode{"0.0", start, end};
        //     if (type == "bool")
        //         return nodes::BooleanLiteralNode{"0", start, end};
        //     if (type == "str")
        //         return nodes::StringLiteralNode{"", start, end};
        //     if (type == "regex")
        //         return nodes::RegexLiteralNode{"", start, end};
        //     return nullptr;
        // };

        // ---------------------
        // Si ctx es nullptr, array vacío → llenar con valores by default
        // ---------------------
        if (!ctx) {
            if (!dimensions.empty()) {
                size_t expectedSize = dimensions[0];
                std::vector<size_t> subDimensions(dimensions.begin() + 1, dimensions.end());

                for (size_t i = 0; i < expectedSize; ++i) {
                    if (subDimensions.empty()) {
                        // auto defaultNode = getDefaultValue(elementType);
                        // elements.push_back(nodes::ArrayElementNode(defaultNode, elementType, start, end));
                    } else {
                        auto subElements = buildArrayElementsRecursively(nullptr, elementType, subDimensions, start, end);
                        elements.push_back(nodes::ArrayElementNode(subElements, elementType, start, end));
                    }
                }
            }
            return elements;
        }

        // ---------------------
        // Caso normal: ctx tiene elementos
        // ---------------------
        for (auto *itemCtx: ctx->arrayItem()) {
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

                // if (valueType != elementType) {
                //     throwTypeError("Array element type mismatch", elementType, itemCtx, source);
                // }

                // elements.push_back(nodes::ArrayElementNode(node, valueType, start, end));
            }
        }

        // ---------------------
        // Fill remaining elements con default values si es necesario
        // ---------------------
        if (!dimensions.empty()) {
            size_t expectedSize = dimensions[0];
            while (elements.size() < expectedSize) {
                std::vector<size_t> subDimensions(dimensions.begin() + 1, dimensions.end());
                if (subDimensions.empty()) {
                    throwTypeError("Array element type mismatch", semantic::convertTypeToString(elementType), elements, source);

                } else {
                    auto subElements = buildArrayElementsRecursively(nullptr, elementType, subDimensions, start, end);
                    elements.push_back(nodes::ArrayElementNode(subElements, elementType, start, end));
                }
            }
        }

        return elements;
    }

    // -----------------------
    // Visitor implementations
    // -----------------------
    std::any ArraysVisitor::visitArrays(Grammar::ArraysContext *ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayAccess(Grammar::ArrayAccessContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        const std::string identifier = ctx->IDENTIFIER()->getText();
        const auto arrayIndexList = visit(ctx->arrayIndexList());
        const auto indexes = std::any_cast<std::vector<size_t> >(arrayIndexList);

        const auto array = scope->lookupArray(identifier);
        if (!array.has_value()) {
            throwScopeError("Array '" + identifier + "' is not declared", identifier, nodes::IdentifierLiteral(identifier, start, end), source);
        }

        std::any current = array.value()->elements;

        std::cout << identifier << std::endl;

        // Navigate through each dimension using the indices
        for (size_t i = 0; i < indexes.size(); ++i) {
            size_t index = indexes[i];

            // Try to cast as vector of ArrayElementNode
            try {
                auto vec = std::any_cast<std::vector<nodes::ArrayElementNode> >(current);

                if (index >= vec.size()) {
                    throwScopeError("Array index " + std::to_string(index) + " out of bounds (size: " + std::to_string(vec.size()) + ") for dimension " + std::to_string(i), identifier, nodes::IdentifierLiteral(identifier, start, end), source);
                }

                // Get the value from the ArrayElementNode
                current = vec[index].value;
                continue;
            } catch (const std::bad_any_cast &) {
                // Not a vector<ArrayElementNode>, try vector<any>
            }

            // Try to cast as vector of std::any
            try {
                auto vec = std::any_cast<std::vector<std::any> >(current);

                if (index >= vec.size()) {
                    throwScopeError("Array index " + std::to_string(index) + " out of bounds (size: " + std::to_string(vec.size()) + ") for dimension " + std::to_string(i), identifier, nodes::IdentifierLiteral(identifier, start, end), source);
                }

                current = vec[index];
                continue;
            } catch (const std::bad_any_cast &) {
                // Not a vector<any>, try vector<int>
            }

            // Try vector of int
            try {
                auto vec = std::any_cast<std::vector<int> >(current);

                if (index >= vec.size()) {
                    throwScopeError("Array index " + std::to_string(index) + " out of bounds (size: " + std::to_string(vec.size()) + ") for dimension " + std::to_string(i), identifier, nodes::IdentifierLiteral(identifier, start, end), source);
                }

                if (i == indexes.size() - 1) {
                    return vec[index];
                } else {
                    throwScopeError("Cannot index further: reached atomic value at dimension " + std::to_string(i), identifier, nodes::IdentifierLiteral(identifier, start, end), source);
                }
            } catch (const std::bad_any_cast &) {
                // Not a vector<int> either
            }

            // Current is an atomic value - if it's the last index, return it
            if (i == indexes.size() - 1) {
                throwScopeError("Too many indices: cannot index into atomic value", identifier, nodes::IdentifierLiteral(identifier, start, end), source);
            }

            throwScopeError("Cannot index into atomic value at dimension " + std::to_string(i), identifier, nodes::IdentifierLiteral(identifier, start, end), source);
        }

        return current;
    }

    std::any ArraysVisitor::visitArrayIndexList(Grammar::ArrayIndexListContext *ctx) {
        std::vector<size_t> indexes;
        for (const auto expression: ctx->expression()) {
            const auto index = visit(expression);
            auto [type, value, node] = resolveItem(index);

            indexes.push_back(std::stoul(value));
        }

        return indexes;
    }

    std::any ArraysVisitor::visitArrayDeclaration(Grammar::ArrayDeclarationContext *ctx) {
        const nodes::Position start{ctx->start->getLine(), ctx->start->getCharPositionInLine()};
        const nodes::Position end{ctx->stop->getLine(), ctx->stop->getCharPositionInLine()};

        // Get type and dimensions
        const auto typeResult = visit(ctx->arrayType());
        const auto [elementType, dimensions] = std::any_cast<std::pair<std::string, std::vector<size_t> > >(typeResult);
        const std::string identifier = ctx->IDENTIFIER()->getText();

        if (scope->existsInCurrent(identifier)) {
            throwScopeError("Array '" + identifier + "' is already declared", identifier, typeResult, source);
        }

        // Build elements recursively
        std::vector<nodes::ArrayElementNode> elements;

        // ✨ Si se proporcionan valores explícitos
        if (ctx->arrayValues() && ctx->arrayValues()->arrayItemsWithBrackets()) {
            // elements = buildArrayElementsRecursively(ctx->arrayValues()->arrayItemsWithBrackets(), elementType, dimensions, start, end);
        }
        // ✨ Si no hay valores, llenar con valores by default según dimensiones
        else if (!dimensions.empty()) {
            // Creamos un contexto ficticio vacío para la recursión
            // elements = buildArrayElementsRecursively(nullptr, elementType, dimensions, start, end);
        }

        // Register array in scope
        // nodes::ArrayDeclarationNode node(identifier, elementType, toUpper(identifier) == identifier, dimensions, elements, start, end);
        // scope->declareArray(identifier, node);

        return {};
    }

    std::any ArraysVisitor::visitArrayReAssignment(Grammar::ArrayReAssignmentContext *ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayType(Grammar::ArrayTypeContext *ctx) {
        const std::string elementType = ctx->arrayDataType()->getText();
        std::vector<size_t> dimensions;

        if (ctx->arrayDeclarationTypeSizes()) {
            for (auto *exprCtx: ctx->arrayDeclarationTypeSizes()->expression()) {
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

    std::any ArraysVisitor::visitArrayItem(Grammar::ArrayItemContext *ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayElement(Grammar::ArrayElementContext *ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext *ctx) {
        std::vector<size_t> dimensions;
        for (auto *exprCtx: ctx->expression()) {
            const auto exprAny = visit(exprCtx);
            if (exprAny.type() == typeid(nodes::IntegerLiteralNode)) {
                dimensions.push_back(std::stoul(std::any_cast<nodes::IntegerLiteralNode>(exprAny).value));
            } else {
                throwError("InvalidArrayDimension", "Array dimensions must be integer literals", ctx->start->getLine(), source);
            }
        }
        return dimensions;
    }

    std::any ArraysVisitor::visitArrayDataType(Grammar::ArrayDataTypeContext *ctx) {
        return ctx->getText();
    }

    std::any ArraysVisitor::visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext *ctx) {
        return visitChildren(ctx);
    }

    std::any ArraysVisitor::visitArrayValues(Grammar::ArrayValuesContext *ctx) {
        return visitChildren(ctx);
    }

} // namespace yogi::visitor