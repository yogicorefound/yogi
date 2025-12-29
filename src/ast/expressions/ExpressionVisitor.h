//
// Created by Brayhan De Aza on 12/4/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "ast/base/BaseVisitor.h"

namespace yogi::visitor {
    class ExpressionVisitor : public virtual BaseVisitor {
       public:
        std::any visitExpression(Grammar::ExpressionContext* ctx) override;
        std::any visitBinaryExpression(Grammar::BinaryExpressionContext* ctx) override;
        std::any visitConcatenationExpression(Grammar::ConcatenationExpressionContext* ctx) override;

       private:
        std::function<std::pair<double, std::string>(const std::any&)> extractValue;
    };
} // namespace yogi::visitor
