//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"

namespace yogi::visitor {
    class VariablesVisitor : public virtual BaseVisitor {
       public:
        std::any visitVariableDeclaration(Grammar::VariableDeclarationContext* ctx) override;
        std::any visitVariableDataType(Grammar::VariableDataTypeContext* ctx) override;
        std::any visitVariableReAssignment(Grammar::VariableReAssignmentContext* ctx) override;
        std::any visitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext* ctx) override;
        std::any visitVariables(Grammar::VariablesContext* ctx) override;
        std::any visitVariableValue(Grammar::VariableValueContext* ctx) override;
    };
} // namespace yogi::visitor
