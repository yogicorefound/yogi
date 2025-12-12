//
// Created by Brayhan De Aza on 12/4/25.
//

#ifndef CROMIO_EXPRESSION_VISITOR_H
#define CROMIO_EXPRESSION_VISITOR_H

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"

namespace cromio::visitor {
    class ExpressionVisitor : public virtual BaseVisitor {
       public:
        std::any visitExpression(Grammar::ExpressionContext* ctx) override;
    };
} // namespace cromio::visitor

#endif // CROMIO_EXPRESSION_VISITOR_H
