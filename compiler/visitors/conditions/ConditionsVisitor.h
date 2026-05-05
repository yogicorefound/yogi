//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "visitors/base/BaseVisitor.h"
#include "visitors/dictionaries/DictionaryVisitor.h"
#include "visitors/members/MembersVisitor.h"

namespace yogi::visitor {
    class ConditionsVisitor : public virtual BaseVisitor {
       public:
        std::any visitIfStatement(Grammar::IfStatementContext* ctx) override;
        std::any visitElseIfStatement(Grammar::ElseIfStatementContext* ctx) override;
        std::any visitIfStatementBody(Grammar::IfStatementBodyContext* ctx) override;
        std::any visitElseStatement(Grammar::ElseStatementContext* ctx) override;
        std::any visitIfStatementCondition(Grammar::IfStatementConditionContext* ctx) override;
    };
} // namespace yogi::visitor
