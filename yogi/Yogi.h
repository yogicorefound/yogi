//
// Created by Brayhan De Aza on 5/12/26.
//

#pragma once

#include "compiler/semantic/semantic.h"
#include "parser/Parser.h"

namespace yogi {
    class Yogi final {
        public:
            explicit Yogi(const int argc, const char *argv[]) {
                init(argc, argv);
            }

            void print() const;

            visitor::nodes::YogiNode program;

        private:
            void init(int argc, const char *argv[]);
    };
}