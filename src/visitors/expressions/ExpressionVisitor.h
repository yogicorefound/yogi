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

       private:
        std::function<std::pair<double, std::string>(const std::any&)> extractValue;
        struct Value {
            std::string value;
            std::string type; // "int", "float", "str", "bool"
        };

        Value extract(const std::any& anyValue) {
            if (anyValue.type() == typeid(nodes::IntegerLiteralNode)) {
                auto n = std::any_cast<nodes::IntegerLiteralNode>(anyValue);
                return {n.value, "int"};
            }
            if (anyValue.type() == typeid(nodes::FloatLiteralNode)) {
                auto n = std::any_cast<nodes::FloatLiteralNode>(anyValue);
                return {n.value, "float"};
            }
            if (anyValue.type() == typeid(nodes::StringLiteralNode)) {
                auto n = std::any_cast<nodes::StringLiteralNode>(anyValue);
                return {n.value, "str"};
            }
            if (anyValue.type() == typeid(nodes::BooleanLiteralNode)) {
                auto n = std::any_cast<nodes::BooleanLiteralNode>(anyValue);
                return {n.value, "bool"};
            }
            if (anyValue.type() == typeid(nodes::IdentifierLiteral)) {
                auto id = std::any_cast<nodes::IdentifierLiteral>(anyValue);
                auto var = scope->lookupVariable(id.value);
                if (!var)
                    throw std::runtime_error("Variable '" + id.value + "' not declared");
                return extract(var.value()->value);
            }
            if (anyValue.type() == typeid(nodes::BinaryExpressionNode)) {
                auto n = std::any_cast<nodes::BinaryExpressionNode>(anyValue);
                return {n.value, n.resultType};
            }

            throw std::runtime_error("Unsupported expression value");
        }
    };
} // namespace yogi::visitor
