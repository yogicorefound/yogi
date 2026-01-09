//
// Created by Brayhan De Aza on 12/4/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "visitors/base/BaseVisitor.h"

namespace yogi::visitor {
    class ExpressionVisitor : public virtual BaseVisitor {
       public:
        std::any visitExpression(Grammar::ExpressionContext* ctx) override;
        std::any visitAdditiveExpression(Grammar::AdditiveExpressionContext* ctx) override;
        std::any visitMultiplicativeExpression(Grammar::MultiplicativeExpressionContext* ctx) override;
        std::any visitPowerExpression(Grammar::PowerExpressionContext* ctx) override;
        std::any visitUnaryExpression(Grammar::UnaryExpressionContext* ctx) override;
        std::any visitPrimaryExpression(Grammar::PrimaryExpressionContext* ctx) override;
        std::any visitRelationalExpression(Grammar::RelationalExpressionContext* ctx) override;

        std::any visitBitwiseOrExpression(Grammar::BitwiseOrExpressionContext* ctx) override;
        std::any visitBitwiseAndExpression(Grammar::BitwiseAndExpressionContext* ctx) override;
        std::any visitBitwiseXorExpression(Grammar::BitwiseXorExpressionContext* ctx) override;
        std::any visitEqualityExpression(Grammar::EqualityExpressionContext* ctx) override;
        std::any visitShiftExpression(Grammar::ShiftExpressionContext* ctx) override;
        std::any visitLogicalAndExpression(Grammar::LogicalAndExpressionContext* ctx) override;
        std::any visitLogicalOrExpression(Grammar::LogicalOrExpressionContext* ctx) override;

       private:
        std::function<std::pair<double, std::string>(const std::any&)> extractValue;
    };
} // namespace yogi::visitor
