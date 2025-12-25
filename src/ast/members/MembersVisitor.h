//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "MembersByType.h"
#include "ast/base/BaseVisitor.h"

namespace yogi::visitor {

    class MembersVisitor : public virtual BaseVisitor, MembersByType {
       public:
        std::any visitMemberExpression(Grammar::MemberExpressionContext* ctx) override;
        std::any visitValueAtom(Grammar::ValueAtomContext* ctx) override;
        std::any visitArgumentList(Grammar::ArgumentListContext* ctx) override;
        std::any visitValuePostfix(Grammar::ValuePostfixContext* ctx) override;
    };

} // namespace yogi::visitor
