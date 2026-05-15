//
// Created by Brayhan De Aza on 5/15/26.
//

#pragma once

#include "compiler/semantic/base/BaseSemantic.h"

namespace yogi::compiler::semantic {
    class ImportSemantic : public virtual BaseSemantic {
        public:
            static std::any analyzeImportStatement(const std::any &node);

    };
}