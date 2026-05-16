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

            std::any visitExportIdentifier(Grammar::ExportIdentifierContext *ctx) override;

            std::any visitExportVariableDeclaration(Grammar::ExportVariableDeclarationContext *ctx) override;

            std::any visitExportMultipleIdentifiers(Grammar::ExportMultipleIdentifiersContext *ctx) override;
    };

}