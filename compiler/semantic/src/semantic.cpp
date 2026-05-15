//
// Created by Brayhan De Aza on 5/14/26.
//


#include "compiler/semantic/semantic.h"

namespace yogi::compiler::semantic {
    void Semantic::analyze() const {
        // for (const auto &order: program.executionOrder) {
        //     const auto index = utils::Helpers::parseNumberString(order);
        //     std::cout << "Index: " << index << std::endl;
        //
        //     for (auto module: program.sccGroups[index]) {
        //         std::cout << "Module: " << module << std::endl;
        //
        //         const auto ast = program.asts.at(module);
        //         analyzeNode(ast);
        //
        //         std::cout << std::endl;
        //     }
        //
        //     std::cout << std::endl;
        // }
    }

    void Semantic::analyzeNode(const visitor::nodes::ProgramNode &program) {
        // for (const auto node: program.body) {
        //     std::cout << "Node: " << node.type().name() << std::endl;
        //     if (node.type() == typeid(visitor::nodes::Kind::IMPORT_STATEMENT)) {
        //         analyzeImportStatement(node);
        //     }
        // }
    }
}