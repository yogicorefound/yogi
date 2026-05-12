//
// Created by Brayhan De Aza on 5/4/26.
//

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"
#include "parser/Parser.h"
#include "utils/helpers/Helpers.h"
#include <string>

int main(const int argc, const char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }


        // -------------------------
        // Build DFS tree
        // -------------------------
        std::unordered_set<std::string> visitedModules;
        auto dfs = yogi::compiler::parser::Parser::discoverModulesPaths(argv[1], visitedModules);

        // -------------------------
        // Build AST map
        // -------------------------
        std::unordered_map<std::string, bool> visitedAST;
        auto asts =yogi::compiler::parser::Parser::parseModules(dfs, visitedAST);

        yogi::visitor::nodes::YogiNode result{
            std::move(dfs),
            std::move(asts)
        };

        result.print();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}