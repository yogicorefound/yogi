//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"

namespace yogi::visitor {
    class DictionaryVisitor : public virtual BaseVisitor {
       public:
        std::any visitDictionaryDeclaration(Grammar::DictionaryDeclarationContext* ctx) override;
        std::any visitDictionaryAssignmentBody(Grammar::DictionaryAssignmentBodyContext* ctx) override;
        std::any visitDictionaryDeclarationType(Grammar::DictionaryDeclarationTypeContext* ctx) override;
        std::any visitDictionaryDeclarationTypeArray(Grammar::DictionaryDeclarationTypeArrayContext* ctx) override;
        std::any visitDictionaryTypeElement(Grammar::DictionaryTypeElementContext* ctx) override;
        std::any visitDictionaryDataType(Grammar::DictionaryDataTypeContext* ctx) override;
    };
} // namespace yogi::visitor
