//
// Created by Brayhan De Aza on 5/7/26.
//

#pragma once
#include "../visitors/nodes/ProgramNode.h"
#include <string>
#include <unordered_map>

namespace yogi::compiler::cache {
    class Cache {
        public:
            Cache() {
            }

            std::optional<visitor::nodes::ASTNode> getCachedAST (const std::string &filePath);

        private:
            visitor::nodes::ASTNode get(const std::string &filePath);
            void set(const std::string &filePath, visitor::nodes::ASTNode ast);
            std::unordered_map<std::string, visitor::nodes::ASTNode> caches;
    };
}