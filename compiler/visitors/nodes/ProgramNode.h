//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <utility>

#include "BaseNode.h"
#include "StatementNode.h"

namespace yogi::visitor::nodes {
    struct ProgramNode : BaseNode {
        std::vector<std::any> body;

        explicit ProgramNode(
            const Position start,
            const Position end
        ) : BaseNode(Kind::PROGRAM, start, end) {
        }

        void addStatement(std::any statement) {
            body.push_back(std::move(statement));
        }
    };

    struct ASTNode {
        std::string path;
        const ProgramNode program;

        explicit ASTNode(ProgramNode program, std::string path) : path(std::move(path)), program(std::move(program)) {
        }
    };

} // namespace yogi::visitor::nodes