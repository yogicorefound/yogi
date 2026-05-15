//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <optional>
#include <utility>
#include "BaseNode.h"
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

        bool flagged = false;

        ModulesPathsNode() = default;

        explicit ModulesPathsNode(std::string path)
            : path(std::move(path)) {
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
                j["flagged"] = flagged;

                for (const auto &module: modules) {
                    j["modules"].push_back(module.toJson());
                }

                return j;
            }
    };

    // -------------------------
    // Final combined object
    // -------------------------
    struct YogiNode {
        std::unordered_map<std::string, std::vector<std::string> > sccGraph;
        std::vector<std::vector<std::string> > sccGroups;
        std::vector<std::string> executionOrder;
        std::unordered_map<std::string, std::vector<std::string> > dependencyGraph;
        std::unordered_map<std::string, ProgramNode> asts;
        std::unordered_map<std::string, ProgramNode> semanticAsts = {};

        // -----------------------------
        // Convert AST map to JSON
        // -----------------------------
        json astsToJson() const {
            json j = json::object();

            for (const auto &[path, program]: asts) {
                j[path] = utils::Helpers::nodeToJson(program);
            }

            return j;
        }

        json semanticAstsToJson() const {
            json j = json::object();

            for (const auto &[path, program]: semanticAsts) {
                j[path] = utils::Helpers::nodeToJson(program);
            }

            return j;
        }


        // -----------------------------
        // Final print function
        // -----------------------------
        void print() const {
            json j = {
                {"sccGraph", sccGraph},
                {"sccGroups", sccGroups},
                {"executionOrder", executionOrder},
                {"dependencyGraph", dependencyGraph},
                {"asts", astsToJson()},
                {"semanticAsts", semanticAstsToJson()}
            };

            std::cout << j.dump(1) << std::endl;
        }
    };

} // namespace yogi::visitor::nodes