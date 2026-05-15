//
// Created by Brayhan De Aza on 5/15/26.
//

#include "Import.h"
#include <iostream>

namespace yogi::compiler::semantic {
    std::any ImportSemantic::analyzeImportStatement(const std::any &node) {
        std::cout << "Import statement: " << node.type().name() << std::endl;
        return std::any();
    }
}