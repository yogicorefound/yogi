//
// Created by Brayhan De Aza on 5/12/26.
//

#pragma once

#include "compiler/compiler.h"
#include "utils/helpers/Helpers.h"
#include <string>
#include "visitors/nodes/ProgramNode.h"
#include <queue>


namespace yogi::compiler::parser {
    class Parser {
        public:
            using ModuleGraph = std::unordered_map<std::string, std::vector<std::string> >;

            using Components = std::vector<std::vector<std::string> >;

            static std::unordered_map<std::string, std::vector<std::string> > discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited);

            static std::vector<std::string> buildExecutionOrder(const ModuleGraph &sccGraph);

            static ModuleGraph buildSCCDAG(const ModuleGraph &graph, const Components &components);

            static std::unordered_map<std::string, visitor::nodes::ProgramNode> parseModules(const std::unordered_map<std::string, std::vector<std::string> > &dependencyGraph, std::unordered_set<std::string> &visited);

            static void print(const std::unordered_map<std::string, std::vector<std::string> > &graph);

            static Components build(const ModuleGraph &graph);
    };
}