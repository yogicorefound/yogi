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

            std::any visitExportDefaultStatement(Grammar::ExportDefaultStatementContext *ctx) override;

            std::any visitExportNamedStatement(Grammar::ExportNamedStatementContext *ctx) override;

            std::any visitExportNamedGroupStatement(Grammar::ExportNamedGroupStatementContext *ctx) override;

            std::any visitExportDeclarationStatement(Grammar::ExportDeclarationStatementContext *ctx) override;

            std::any visitExportSpecifier(Grammar::ExportSpecifierContext *ctx) override;

            std::any visitExportSpecifierWithBraces(Grammar::ExportSpecifierWithBracesContext *ctx) override;
    };

}