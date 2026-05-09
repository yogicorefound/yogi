//
// Created by Brayhan De Aza on 5/7/26.
//

#include "cache.h"

namespace yogi::compiler::cache {
    
    // Constructor
    Cache::Cache(const std::filesystem::path &projectRoot) : projectRoot(projectRoot),
        cacheRoot(projectRoot / ".cache") {
    }


    std::optional<std::reference_wrapper<const visitor::nodes::CacheNode> > Cache::getCachedAST(const std::string &filePath) const {
        if (const auto it = asts.find(filePath); it != asts.end()) {
            return *it->second;
        }

        return std::nullopt;
    }

    void Cache::cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::CacheNode> ast) {
        asts[filePath] = std::move(ast);
    }

    std::unordered_map<std::string, std::unique_ptr<visitor::nodes::CacheNode> > &Cache::getAllCachedASTs() {
        return asts;
    }

    // -------------------------
    // Init
    // -------------------------
    void Cache::init() const {
        ensureCacheDir();
        ensureModulesDir();

        if (!fileExists(getCacheFile())) {
            std::ofstream file(getCacheFile());
            file << R"({"modules":{}})";
        }
    }

    // -------------------------
    // Directories
    // -------------------------
    void Cache::ensureCacheDir() const {
        if (!std::filesystem::exists(cacheRoot)) {
            std::filesystem::create_directories(cacheRoot);
        }
    }

    void Cache::ensureModulesDir() const {
        if (const std::filesystem::path modules = getModulesDir(); !std::filesystem::exists(modules)) {
            std::filesystem::create_directories(modules);
        }
    }

    std::filesystem::path Cache::getCacheDir() const {
        return cacheRoot;
    }

    std::filesystem::path Cache::getModulesDir() const {
        return cacheRoot / "modules";
    }

    std::filesystem::path Cache::getCacheFile() const {
        return cacheRoot / "cache.json";
    }

    std::filesystem::path Cache::getModuleDir(const std::string &moduleId) const {
        return getModulesDir() / moduleId;
    }

    // -------------------------
    // File helpers
    // -------------------------
    void Cache::writeFile(const std::filesystem::path &path, const std::string &content) {
        if (!std::filesystem::exists(path.parent_path())) {
            std::filesystem::create_directories(path.parent_path());
        }

        std::ofstream file(path, std::ios::out | std::ios::trunc);
        file << content;
    }

    bool Cache::fileExists(const std::filesystem::path &path) {
        return std::filesystem::exists(path);
    }

}