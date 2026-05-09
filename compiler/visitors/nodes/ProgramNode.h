//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <optional>
#include <utility>

#include "BaseNode.h"
#include "StatementNode.h"
#include "utils/helpers/Helpers.h"

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

    struct FullProgramASTSNode {
        std::string hash;
        bool isMain{};
        std::vector<std::any> ast;

        FullProgramASTSNode() = default;

        explicit FullProgramASTSNode(
            const std::string &hash,
            const bool isMain,
            const std::vector<std::any> &ast)
            : hash(hash), isMain(isMain), ast(ast) {
        }
    };

    struct CacheNode {
        std::string hash;
        bool isMain;
        ProgramNode ast;

        explicit CacheNode(std::string hash, const bool isMain, ProgramNode &ast) : hash(std::move(hash)), isMain(isMain), ast(std::move(ast)) {
        }
    };

    struct ModulesPathsNode {
        std::string path;
        std::vector<ModulesPathsNode> modules;

        ModulesPathsNode() = default;

        explicit ModulesPathsNode(std::string p)
            : path(std::move(p)) {
        }

        void addModule(ModulesPathsNode module) {
            modules.push_back(std::move(module));
        }


        void print() const {
            std::cout << toJson().dump(4) << std::endl;
        }

        private:
            json toJson() const {
                json j;
                j["path"] = path;
                j["modules"] = json::array();

                for (const auto &module: modules) {
                    j["modules"].push_back(module.toJson());
                }

                return j;
            }
    };

} // namespace yogi::visitor::nodes