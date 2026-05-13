//
// Created by Brayhan De Aza on 5/12/26.
//

#pragma once

#include "parser/Parser.h"
#include "visitors/nodes/nodes.h"

namespace yogi {
    class Yogi final {
        public:
            explicit Yogi(const int argc, const char *argv[]) {
                init(argc, argv);
            }

            void print() const;

        private:
            void init(int argc, const char *argv[]);
            visitor::nodes::YogiNode program;
    };
}