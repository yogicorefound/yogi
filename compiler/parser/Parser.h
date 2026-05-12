//
// Created by Brayhan De Aza on 5/12/26.
//

#pragma once

#include <iostream>
#include <filesystem>
#include "compiler/compiler.h"
#include "utils/helpers/Helpers.h"
#include <string>
#include "visitors/nodes/ProgramNode.h"


namespace yogi::compiler::parser {
    class Parser {
        public:
            static visitor::nodes::ModulesPathsNode discoverModulesPaths(const std::string &filePath, std::unordered_set<std::string> &visited);

            static std::unordered_map<std::string, visitor::nodes::ProgramNode> parseModules(const visitor::nodes::ModulesPathsNode &modules, std::unordered_map<std::string, bool> &visited);
    };
}