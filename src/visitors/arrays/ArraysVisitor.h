//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "semantic/semantic.h"
#include "visitors/base/BaseVisitor.h"

namespace yogi::visitor {
    class ArraysVisitor : public virtual BaseVisitor {
       public:
        std::vector<nodes::ArrayElementNode> buildArrayElementsRecursively(Grammar::ArrayItemsWithBracketsContext* ctx, const std::string& elementType, const std::vector<size_t>& dimensions, const nodes::Position& start, const nodes::Position& end);
        std::any visitArrays(Grammar::ArraysContext* ctx) override;
        std::any visitArrayReAssignment(Grammar::ArrayReAssignmentContext* ctx) override;
        std::any visitArrayDeclaration(Grammar::ArrayDeclarationContext* ctx) override;
        std::any visitArrayType(Grammar::ArrayTypeContext* ctx) override;
        std::any visitArrayItem(Grammar::ArrayItemContext* ctx) override;
        std::any visitArrayElement(Grammar::ArrayElementContext* ctx) override;
        std::any visitArrayDeclarationTypeSizes(Grammar::ArrayDeclarationTypeSizesContext* ctx) override;
        std::any visitArrayDataType(Grammar::ArrayDataTypeContext* ctx) override;
        std::any visitArrayItemsWithBrackets(Grammar::ArrayItemsWithBracketsContext* ctx) override;
        std::any visitArrayValues(Grammar::ArrayValuesContext* ctx) override;
    };
} // namespace yogi::visitor
