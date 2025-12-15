//
// Created by Brayhan De Aza on 10/19/25.
//

#ifndef CROMIO_ARRAYS_VISITOR_H
#define CROMIO_ARRAYS_VISITOR_H

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"
#include "semantic/semantic.h"

namespace cromio::visitor {
    class ArraysVisitor : public virtual BaseVisitor {
       public:
        std::any visitArrays(Grammar::ArraysContext* ctx) override;
        std::any visitArrayItems(Grammar::ArrayItemsContext* ctx) override;
        std::any visitArrayReAssignment(Grammar::ArrayReAssignmentContext* ctx) override;
        std::any visitArrayDeclaration(Grammar::ArrayDeclarationContext* ctx) override;
        std::any visitArrayDeclarationTypeSize(Grammar::ArrayDeclarationTypeSizeContext* ctx) override;
        std::any visitArrayType(Grammar::ArrayTypeContext* ctx) override;
        std::any visitArrayDataType(Grammar::ArrayDataTypeContext* ctx) override;
    };
} // namespace cromio::visitor

#endif // CROMIO_ARRAYS_VISITOR_H