//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once

#include <string>
#include "BaseNode.h"
#include "LiteralNode.h"


namespace yogi::visitor::nodes {

    struct ExportItemNode {
        Kind kind = Kind::ExportSymbol;
        IdentifierLiteral identifier;
        std::optional<IdentifierLiteral> alias = std::nullopt;
        std::string modulePath;
        std::shared_ptr<BaseNode> declaration;

    };

    struct ExportNode : BaseNode {
        std::vector<ExportItemNode> exports;
    };

    // ----------------------------------------
    // export default App
    // ----------------------------------------
    struct ExportDefaultNode : BaseNode {
        IdentifierLiteral name;
    };

    // ----------------------------------------
    // export a
    // ----------------------------------------
    struct ExportIdentifierNode : BaseNode {
        IdentifierLiteral name;
    };

    // ----------------------------------------
    // export { a, b }
    // export { a as valueA }
    // ----------------------------------------
    struct ExportSpecifierNode : BaseNode {
        IdentifierLiteral localName;
        std::optional<IdentifierLiteral> exportedName;
    };

    struct ExportListNode : BaseNode {
        std::vector<std::any> exports;

        ExportListNode(const std::vector<std::any> &exports, const Position start, const Position end) : BaseNode(Kind::ExportList, start, end), exports(exports) {
        }
    };

    // ----------------------------------------
    // export fn hello() {}
    // export int a = 10
    // ----------------------------------------
    struct ExportDeclarationNode : BaseNode {
        std::any declaration;

        ExportDeclarationNode(const std::any &declaration, const Position start, const Position end) : BaseNode(Kind::ExportDeclaration, start, end), declaration(declaration) {
        }

    };

    // ----------------------------------------
    // export { a } from "math"
    // ----------------------------------------
    struct ReExportNode : BaseNode {
        std::vector<ExportSpecifierNode> exports;
        StringLiteralNode sourceModule;
    };

    // ----------------------------------------
    // export * from "math"
    // export * as math from "math"
    // ----------------------------------------
    struct ExportNamespaceNode : BaseNode {
        StringLiteralNode sourceModule;
        std::optional<IdentifierLiteral> alias;
    };

}