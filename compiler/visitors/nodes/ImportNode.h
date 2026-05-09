//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once
#include "BaseNode.h"
#include <string>

namespace yogi::visitor::nodes {
    struct ImportNode : BaseNode {
        std::string path;
        std::vector<IdentifierLiteral> statements;

    };

    struct ImportWithBracketsNode : BaseNode {
        std::string path;
        std::vector<IdentifierLiteral> modules;

        ImportWithBracketsNode(const std::string &path, const std::vector<IdentifierLiteral> &modules, const Position start, const Position end) : BaseNode(Kind::IMPORT_STATEMENT, start, end), path(path), modules(modules) {
        }
    };

    struct ImportWithoutBracketsNode : BaseNode {
        std::string name;
        std::string path;

        ImportWithoutBracketsNode(const std::string &name, const std::string &path, const Position start, const Position end) : BaseNode(Kind::IMPORT_STATEMENT, start, end), name(name), path(path) {
        }
    };
}