//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"
#include "utils/helpers/Helpers.h"
#include <fstream>
#include <sstream>
#include <string>


yogi::visitor::nodes::ModulesPathsNode discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited) {
    using yogi::visitor::nodes::ModulesPathsNode;

    // -------------------------------------------------
    // Normalize absolute path
    // -------------------------------------------------
    const auto normalizedPath = std::filesystem::weakly_canonical(filePath).string();

    // -------------------------------------------------
    // Prevent infinite circular recursion
    // -------------------------------------------------
    if (visited.contains(normalizedPath)) {
        return ModulesPathsNode(normalizedPath);
    }

    visited.insert(normalizedPath);

    // -------------------------------------------------
    // Open current file
    // -------------------------------------------------
    if (std::ifstream file(normalizedPath); !file) {
        std::cerr << "Error: Could not open file " << normalizedPath << std::endl;
        std::exit(1);
    }

    // -------------------------------------------------
    // Scan AST
    // -------------------------------------------------
    const auto ast = yogi::compiler::Compiler::scan(normalizedPath);
    auto modules = std::any_cast<ModulesPathsNode>(ast);


    modules.path = normalizedPath;

    const auto currentDirectory = std::filesystem::path(normalizedPath).parent_path();

    // -------------------------------------------------
    // Resolve imports
    // -------------------------------------------------
    std::vector<ModulesPathsNode> resolvedModules;
    std::unordered_set<std::string> uniqueModules;

    for (const auto &module: modules.modules) {
        // resolve path of imported module
        const auto resolvedPath = std::filesystem::weakly_canonical(
            currentDirectory / module.path
        ).string();

        // skip duplicates
        if (uniqueModules.contains(resolvedPath)) {
            continue;
        }

        // recursive discovery
        uniqueModules.insert(resolvedPath);
        auto child = discoverModulesPaths(resolvedPath, visited);

        if (resolvedPath == normalizedPath) {
            child.flagged = true;
        }

        resolvedModules.push_back(child);
    }

    // replace shallow imports with full tree
    modules.modules = resolvedModules;

    return modules;
}

std::unordered_map<std::string, yogi::visitor::nodes::ProgramNode> parseModules(const yogi::visitor::nodes::ModulesPathsNode &modules) {
    std::unordered_map<std::string, yogi::visitor::nodes::ProgramNode> asts;
    yogi::compiler::Compiler compiler;

    // Compile current module
    const auto ast = compiler.compile(modules.path);
    const auto program = std::any_cast<yogi::visitor::nodes::ProgramNode>(ast);

    asts.emplace(modules.path, program);

    // Recurse into submodules
    for (const auto &child: modules.modules) {
        if (child.flagged || asts.contains(child.path)) continue;

        auto childAsts = parseModules(child);
        asts.insert(childAsts.begin(), childAsts.end());
    }

    return asts;
}

int main(const int argc, const char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }

        std::unordered_set<std::string> visited;

        // -------------------------
        // Build DFS tree
        // -------------------------
        auto dfs = discoverModulesPaths(argv[1], visited);

        // -------------------------
        // Build AST map
        // -------------------------
        auto asts = parseModules(dfs);

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

        YogiNode result{
            std::move(dfs),
            std::move(asts)
        };

        result.print();

        // OPTIONAL: debug print
        std::cout << "Compilation finished successfully\n";

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}