//
// Created by Brayhan De Aza on 5/14/26.
//


#include "compiler/semantic/semantic.h"

namespace yogi::compiler::semantic {
   std::unordered_map<std::string, visitor::nodes::ProgramNode>  Semantic::analyze() const {
        std::unordered_map<std::string, visitor::nodes::ProgramNode> asts;

        for (const auto &order: program.executionOrder) {

            for (const auto index = utils::Helpers::parseNumberString(order); auto module: program.sccGroups[index]) {
                const auto ast = program.asts.at(module);
                const auto body = analyzeNodes(ast, module);
                asts.insert({module, body});
            }
        }

        return asts;
    }

    visitor::nodes::ProgramNode Semantic::analyzeNodes(const visitor::nodes::ProgramNode &program, const std::string &module) {
        auto moduleNode = visitor::nodes::ProgramNode(program.start, program.end);

        for (const auto node: program.body) {
            if (node.type() == typeid(visitor::nodes::ImportWithoutBracketsNode) || node.type() == typeid(visitor::nodes::ImportWithBracketsNode)) {
                const auto import = analyzeImportStatements(node, module);
                moduleNode.addStatement(import);
            }
        }

        return moduleNode;
    }
}