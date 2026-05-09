//
// Created by Brayhan De Aza on 5/7/26.
//

#pragma once
#include "../visitors/nodes/ProgramNode.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <optional>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>


// {
//     "9fa13b2gertfgb7ryg7byr87gyb78ryb7ybtgj5tgj56jy36": {
//         "hash": "89879878877568gryjtjthtjb7ybtgj5tgj8998989tgrthetyjtyjtyy67657u5",
//         "isMain": true,
//         "ast": [
//             {
//                 "kind": "VariableDeclaration",
//                 "identifier": "a",
//                 "type": 1,
//                 "isConstant": false,
//                 "value": {
//                     "kind": "StringLiteral",
//                     "value": "Hello"
//                 }
//             }
//         ]
//     }
// }

namespace yogi::compiler::cache {


    class Cache {
        public:
            explicit Cache(const std::filesystem::path &projectRoot);


            std::optional<std::reference_wrapper<const visitor::nodes::CacheNode> > getCachedAST(const std::string &filePath) const;

            void cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::CacheNode> ast);

            // get all cached ASTs
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::CacheNode> > &getAllCachedASTs();

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



        private:
            std::unordered_map<std::string, std::unique_ptr<visitor::nodes::CacheNode> > asts;
            std::filesystem::path projectRoot;
            std::filesystem::path cacheRoot;
    };

}