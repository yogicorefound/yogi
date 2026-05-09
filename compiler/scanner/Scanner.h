//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once
#include <vector>
#include <string>
#include <visitors/program/ProgramVisitor.h>

namespace yogi::compiler::scanner {
    class Scanner {
        public:
            Scanner(const int argc, const char *argv[]) {
                getContent(argc, argv);
            };

            visitor::nodes::ModulesPathsNode scan();

            void print(std::optional<uint8_t> indent) const;

        private:
            void getContent(int argc, const char *argv[]);

            visitor::nodes::ModulesPathsNode modulesPaths;
            std::string content;
            std::string fileName;
            std::string filePath;
    };
}