//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once
#include "visitors/base/BaseVisitor.h"
#include <any>


namespace yogi::visitor {
    class ExportVisitor : public virtual BaseVisitor {
        public:
            std::any visitExportStatement(Grammar::ExportStatementContext *ctx) override;

            std::any visitExportDeclaration(Grammar::ExportDeclarationContext *ctx) override;

            std::any visitReExportWithBrackets(Grammar::ReExportWithBracketsContext *ctx) override;

            std::any visitReExportAll(Grammar::ReExportAllContext *ctx) override;
    };

}