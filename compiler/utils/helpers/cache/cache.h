//
// Created by Brayhan De Aza on 5/7/26.
//

#pragma once


#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

#include "visitors/nodes/ProgramNode.h"

namespace yogi::utils::helper::cache {

    class Cache {
        public:
            explicit Cache(const std::filesystem::path &projectRoot);

            std::optional<std::reference_wrapper<const visitor::nodes::ASTNode> > getCachedAST(const std::string &filePath) const;

            void cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::ASTNode> ast);

            // get all cached ASTs
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::ASTNode> > &getAllCachedASTs();

            // Initialization
            void init() const;

            // Directory helpers
            void ensureCacheDir() const;

            void ensureModulesDir() const;

            std::filesystem::path getCacheDir() const;

            std::filesystem::path getModulesDir() const;

            std::filesystem::path getCacheFile() const;

            std::filesystem::path getModuleDir(const std::string &moduleId) const;

            // File helpers
            static void writeFile(const std::filesystem::path &path, const std::string &content);

            static bool fileExists(const std::filesystem::path &path);

            static std::string hashString(const std::string &input);

        private:
            std::filesystem::path projectRoot;
            std::filesystem::path cacheRoot;
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::ASTNode> > asts;
    };

} // namespace yogi::helper::cache