//
// Created by Brayhan De Aza on 10/19/25.
//

#ifndef CROMIO_VARIABLES_VISITOR_H
#define CROMIO_VARIABLES_VISITOR_H

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"

namespace cromio::visitor {
    class VariablesVisitor : public virtual BaseVisitor {
       public:
        std::any visitVariableDeclaration(Grammar::VariableDeclarationContext* ctx) override;
        std::any visitVariableDataType(Grammar::VariableDataTypeContext* ctx) override;
        std::any visitVariableReAssignment(Grammar::VariableReAssignmentContext* ctx) override;
        std::any visitVariableDeclarationWithoutAssignment(Grammar::VariableDeclarationWithoutAssignmentContext* ctx) override;
        std::any visitVariables(Grammar::VariablesContext* ctx) override;
        std::any visitVariableAccessToMember(Grammar::VariableAccessToMemberContext* ctx) override;
    };
} // namespace cromio::visitor

#endif // CROMIO_VARIABLES_VISITOR_H