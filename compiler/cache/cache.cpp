//
// Created by Brayhan De Aza on 5/7/26.
//

#include "cache.h"

namespace yogi::compiler::cache {
    std::optional<visitor::nodes::ASTNode> Cache::getCachedAST(const std::string &filePath) {
        const auto it = caches.find(filePath);
        if (it != caches.end()) {
            return it->second;
        }

        return std::nullopt;
    }

}