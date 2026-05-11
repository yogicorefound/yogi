//
// Created by Brayhan De Aza on 5/8/26.
//

#pragma once
#include <vector>
#include <string>
#include <visitors/program/ProgramVisitor.h>
#include "utils/helpers/Helpers.h"

namespace yogi::compiler::scanner {
    class Scanner {
        public:
            explicit Scanner(const std::string &filePath) : filePath(utils::Helpers::pathResolver(utils::Helpers::getBuildDirectory(), filePath)) {
            }

            visitor::nodes::ModulesPathsNode scan() const;

            void print(std::optional<uint8_t> indent) const;

            std::string setContentFromFilePath(const std::string &fileUrl) const;

        private:
            visitor::nodes::ModulesPathsNode modulesPaths;
            std::string currentDirectory = utils::Helpers::pathNormalizer(utils::Helpers::getBuildDirectory());
            std::string filePath;
    };
}