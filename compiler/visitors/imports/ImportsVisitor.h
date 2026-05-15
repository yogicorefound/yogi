//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once
#include "visitors/base/BaseVisitor.h"
#include <any>


namespace yogi::visitor {
    class ImportsVisitor : public virtual BaseVisitor {
        public:
            std::any visitImportStatement(Grammar::ImportStatementContext *ctx) override;

            std::any visitImportStatementWithBrackets(Grammar::ImportStatementWithBracketsContext *ctx) override;

            std::any visitImportStatementWithoutBrackets(Grammar::ImportStatementWithoutBracketsContext *ctx) override;
    };
}