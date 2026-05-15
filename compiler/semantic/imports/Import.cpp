//
// Created by Brayhan De Aza on 5/15/26.
//

#include "Import.h"
#include <iostream>

#include "visitors/nodes/nodes.h"

namespace yogi::compiler::semantic {
    std::any ImportSemantic::analyzeImportStatements(const std::any &node, const std::string &module) {
        std::cout << "Import statement: " << node.type().name() << std::endl;

        if (node.type() == typeid(visitor::nodes::ImportWithoutBracketsNode)) {
            auto importNode = std::any_cast<visitor::nodes::ImportWithoutBracketsNode>(node);
            const auto moduleParentPath = utils::Helpers::pathNormalizer(module).parent_path();
            const auto newImportPath = utils::Helpers::pathResolver(moduleParentPath, utils::Helpers::removeQuotes(importNode.path));

            importNode.path = newImportPath;
            return importNode;
        }

        if (node.type() == typeid(visitor::nodes::ImportWithBracketsNode)) {
            std::cout << "ImportWithBracketsNode: " << node.type().name() << std::endl;
        }

        return std::any();
    }
}