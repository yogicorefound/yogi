//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once

#include <string>
#include "BaseNode.h"
#include "LiteralNode.h"


namespace yogi::visitor::nodes {
    // ----------------------------------------
    // export fn hello() {}
    // export int a = 10
    // ----------------------------------------
    struct ExportNode : BaseNode {
        std::any declaration;
        std::optional<IdentifierLiteral> alias = std::nullopt;

        ExportNode(const Position start, const Position end, const std::any &declaration, const std::optional<IdentifierLiteral> &alias = std::nullopt) : BaseNode(Kind::ExportDeclaration, start, end), declaration(declaration), alias(alias) {
        }

    };


    struct ExportListNode : BaseNode {
        std::vector<ExportNode> exports;

        ExportListNode(const std::vector<ExportNode> &exports, const Position start, const Position end) : BaseNode(Kind::ExportList, start, end), exports(exports) {
        }
    };


}