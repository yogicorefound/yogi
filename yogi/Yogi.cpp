//
// Created by Brayhan De Aza on 5/12/26.
//


#include "Yogi.h"

namespace yogi {
    void Yogi::init(const int argc, const char *argv[]) {

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
        auto asts = yogi::compiler::parser::Parser::parseModules(dfs, visitedAST);

        program = {
            std::move(dfs),
            std::move(asts)
        };

    }

    void Yogi::print() const {
        program.print();
    }
}