//
// Created by Brayhan De Aza on 5/7/26.
//

#pragma once
#include "../visitors/nodes/ProgramNode.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <optional>

namespace yogi::compiler::cache {

    class Cache {
        public:
            Cache() = default;

            std::optional<std::reference_wrapper<const visitor::nodes::ASTNode> > getCachedAST(const std::string &filePath) const;

            void cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::ASTNode> ast);

            // get all cached ASTs
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::ASTNode> > &getAllCachedASTs();

        private:
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::ASTNode> > asts;
    };

}