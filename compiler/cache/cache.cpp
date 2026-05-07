//
// Created by Brayhan De Aza on 5/7/26.
//

#include "cache.h"

namespace yogi::compiler::cache {

    std::optional<std::reference_wrapper<const visitor::nodes::ASTNode> >
        Cache::getCachedAST(const std::string &filePath) const {
        if (const auto it = asts.find(filePath); it != asts.end()) {
            return *(it->second);
        }

        return std::nullopt;
    }

    void Cache::cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::ASTNode> ast) {
        asts[filePath] = std::move(ast);
    }

}