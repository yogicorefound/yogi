//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"
#include "utils/helpers/Helpers.h"


yogi::visitor::nodes::ModulesPathsNode discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited) {

    using yogi::visitor::nodes::ModulesPathsNode;

    // -------------------------------------------------
    // Normalize absolute path
    // -------------------------------------------------
    const auto normalizedPath =
            std::filesystem::weakly_canonical(filePath).string();

    // -------------------------------------------------
    // Prevent infinite circular recursion
    // -------------------------------------------------
    if (visited.contains(normalizedPath)) {
        return ModulesPathsNode(normalizedPath);
    }

    visited.insert(normalizedPath);

    // -------------------------------------------------
    // Check file exists
    // -------------------------------------------------
    if (const std::ifstream file(normalizedPath); !file) {

        std::cerr
                << "Error: Could not open file "
                << normalizedPath
                << std::endl;

        std::exit(1);
    }

    // -------------------------------------------------
    // Scan current file
    // -------------------------------------------------
    const auto ast =
            yogi::compiler::Compiler::scan(normalizedPath);

    auto modules =
            std::any_cast<ModulesPathsNode>(ast);

    // ensure normalized absolute path
    modules.path = normalizedPath;

    // -------------------------------------------------
    // Resolve imports relative to current file
    // -------------------------------------------------
    const auto currentDirectory =
            std::filesystem::path(normalizedPath).parent_path();

    std::vector<ModulesPathsNode> resolvedModules;

    // -------------------------------------------------
    // Prevent duplicate imports
    // -------------------------------------------------
    std::unordered_set<std::string> uniqueModules;

    for (const auto &module: modules.modules) {

        // resolve relative import path
        const auto resolvedPath =
                std::filesystem::weakly_canonical(
                    currentDirectory / module.path
                ).string();

        // skip duplicate imports
        if (uniqueModules.contains(resolvedPath) || resolvedPath == modules.path) {
            continue;
        }


        uniqueModules.insert(resolvedPath);

        // recursively discover child modules
        auto child =
                discoverModulesPaths(
                    resolvedPath,
                    visited
                );

        resolvedModules.push_back(child);
    }

    // replace shallow imports with recursive tree
    modules.modules = resolvedModules;
    return modules;
}

int main(const int argc, const char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }


        if constexpr (constexpr auto justScan = true) {
            std::unordered_set<std::string> visited;
            const auto modules = discoverModulesPaths(argv[1], visited);
            modules.print();

        } else {
            yogi::compiler::Compiler compiler(argc, argv);
            const auto ast = compiler.compile(justScan);
            const auto res = std::any_cast<yogi::visitor::nodes::ProgramNode>(ast);

            compiler.printAST(res);
        }


    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}