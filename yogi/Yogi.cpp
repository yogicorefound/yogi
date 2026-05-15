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
        const auto dependencyGraph = compiler::parser::Parser::discoverModulesPaths(argv[1], visitedModules);
        const auto sccGroups = compiler::parser::Parser::build(dependencyGraph);
        auto sccGraph = compiler::parser::Parser::buildSCCDAG(dependencyGraph, sccGroups);
        auto executionOrder = compiler::parser::Parser::buildExecutionOrder(sccGraph);

        // json j = {
        //     {"executionOrder", executionOrder}
        // };
        //
        // std::cout << j.dump(1);

        // -------------------------
        // Build AST map
        // -------------------------
        std::unordered_set<std::string> visited;
        auto asts = compiler::parser::Parser::parseModules(dependencyGraph, visited);

        // -------------------------
        // Semantic analysis
        // -------------------------
        compiler::semantic::Semantic semantic({
            sccGraph,
            sccGroups,
            executionOrder,
            dependencyGraph,
            asts
        });

        semantic.analyze();


        program = {
            sccGraph,
            sccGroups,
            executionOrder,
            dependencyGraph,
            asts
        };

    }

    void Yogi::print() const {
        program.print();
    }
}