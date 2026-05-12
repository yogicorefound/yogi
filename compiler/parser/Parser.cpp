//
// Created by Brayhan De Aza on 5/12/26.
//

#include "Parser.h"


namespace yogi::compiler::parser {

    visitor::nodes::ModulesPathsNode Parser::discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited) {
        using visitor::nodes::ModulesPathsNode;

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
        const auto ast = Compiler::scan(normalizedPath);
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


    std::unordered_map<std::string, visitor::nodes::ProgramNode> Parser::parseModules(const visitor::nodes::ModulesPathsNode &modules, std::unordered_map<std::string, bool> &visited) {
        std::unordered_map<std::string, visitor::nodes::ProgramNode> asts;
        Compiler compiler;

        // Compile current module
        const auto ast = compiler.compile(modules.path);
        const auto program = std::any_cast<visitor::nodes::ProgramNode>(ast);

        asts.emplace(modules.path, program);

        // Recurse into submodules
        for (const auto &child: modules.modules) {
            if (child.flagged || visited.contains(child.path)) continue;

            auto childAsts = parseModules(child, visited);
            asts.insert(childAsts.begin(), childAsts.end());
            visited.insert({child.path, true});
        }

        return asts;
    }


}