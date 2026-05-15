//
// Created by Brayhan De Aza on 11/27/25.
//

#pragma once

#include "semantic/arrays/Arrays.h"
#include "semantic/dictionaries/Dictionaries.h"
#include "semantic/variables/Variables.h"
#include "semantic/imports/Import.h"

namespace yogi::compiler::semantic {
    class Semantic final : public virtual Variables, public virtual Arrays, public virtual Dictionaries, public virtual ImportSemantic {
        public:
            explicit Semantic(const visitor::nodes::YogiNode &program) : Variables(), Arrays(), Dictionaries(), ImportSemantic(), program(program) {
            };

            void analyze() const;

            std::unordered_map<std::string, visitor::nodes::ProgramNode> asts;

        private:
            visitor::nodes::YogiNode program;

            static void analyzeNode(const visitor::nodes::ProgramNode &program);

    };
} // namespace yogi::semantic