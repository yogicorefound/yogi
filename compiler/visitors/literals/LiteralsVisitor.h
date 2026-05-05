//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once
#include "GrammarVisitor.h"
#include "visitors/base/BaseVisitor.h"

namespace yogi::visitor {
    class LiteralsVisitor : public virtual BaseVisitor {
        struct EvalExpressionResult {
            utils::Types type;
            std::string value;
            bool error;
            std::string message;
        };

    public:
        std::any visitLiterals(Grammar::LiteralsContext *ctx) override;

        std::any visitIntegerLiteral(Grammar::IntegerLiteralContext *ctx) override;

        std::any visitFloatLiteral(Grammar::FloatLiteralContext *ctx) override;

        std::any visitStringLiteral(Grammar::StringLiteralContext *ctx) override;

        std::any visitBooleanLiteral(Grammar::BooleanLiteralContext *ctx) override;

        std::any visitNoneLiteral(Grammar::NoneLiteralContext *ctx) override;

        std::any visitFormattedString(Grammar::FormattedStringContext *ctx) override;

        std::any visitFormattedStringContent(Grammar::FormattedStringContentContext *ctx) override;

        std::any visitNumberLiterals(Grammar::NumberLiteralsContext *ctx) override;

        std::any visitStringLiterals(Grammar::StringLiteralsContext *ctx) override;

        std::any visitIdentifierLiteral(Grammar::IdentifierLiteralContext *ctx) override;

        [[nodiscard]] EvalExpressionResult evaluateExpressionWithScope(const std::any &node) const;

        EvalExpressionResult evaluateExpressionWithScopeImplementation(const std::any &node, std::unordered_set<std::string> &visited) const;
    };
} // namespace yogi::visitor