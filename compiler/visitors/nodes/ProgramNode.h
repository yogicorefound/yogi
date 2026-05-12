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
        yogi::visitor::nodes::ModulesPathsNode dfs;
        std::unordered_map<std::string, yogi::visitor::nodes::ProgramNode> asts;

        // -----------------------------
        // Convert AST map to JSON
        // -----------------------------
        json astsToJson() const {
            json j = json::object();

            for (const auto &[path, program]: asts) {
                // NOTE: assumes ProgramNode is serializable OR you adapt this
                j[path] = yogi::utils::Helpers::nodeToJson(program);
            }

            return j;
        }

        // -----------------------------
        // Convert DFS tree to JSON
        // (reuses ModulesPathsNode::toJson idea)
        // -----------------------------
        static json dfsToJson(const yogi::visitor::nodes::ModulesPathsNode &node) {
            json j;
            j["path"] = node.path;
            j["flagged"] = node.flagged;
            j["modules"] = json::array();

            for (const auto &child: node.modules) {
                j["modules"].push_back(dfsToJson(child));
            }

            return j;
        }

        // -----------------------------
        // Final print function
        // -----------------------------
        void print() const {
            json root;

            root["dfs"] = dfsToJson(dfs);
            root["asts"] = astsToJson();

            std::cout << root.dump(4) << std::endl;
        }
    };

} // namespace yogi::visitor::nodes