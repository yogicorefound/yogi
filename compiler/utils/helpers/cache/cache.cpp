//
// Created by Brayhan De Aza on 5/7/26.
//

#include "cache.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

namespace fs = std::filesystem;

namespace yogi::utils::helper::cache {


    // Constructor
    Cache::Cache(const fs::path &projectRoot) : projectRoot(projectRoot),
        cacheRoot(projectRoot / ".cache") {
    }

    std::optional<std::reference_wrapper<const visitor::nodes::ASTNode> > Cache::getCachedAST(const std::string &filePath) const {
        if (const auto it = asts.find(filePath); it != asts.end()) {
            return *(it->second);
        }

        return std::nullopt;
    }

    void Cache::cacheAST(const std::string &filePath, std::unique_ptr<visitor::nodes::ASTNode> ast) {
        asts[filePath] = std::move(ast);
    }

    std::unordered_map<std::string, std::unique_ptr<visitor::nodes::ASTNode> > &Cache::getAllCachedASTs() {
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
        if (!fs::exists(cacheRoot)) {
            fs::create_directories(cacheRoot);
        }
    }

    void Cache::ensureModulesDir() const {
        if (const fs::path modules = getModulesDir(); !fs::exists(modules)) {
            fs::create_directories(modules);
        }
    }

    fs::path Cache::getCacheDir() const {
        return cacheRoot;
    }

    fs::path Cache::getModulesDir() const {
        return cacheRoot / "modules";
    }

    fs::path Cache::getCacheFile() const {
        return cacheRoot / "cache.json";
    }

    fs::path Cache::getModuleDir(const std::string &moduleId) const {
        return getModulesDir() / moduleId;
    }

    // -------------------------
    // File helpers
    // -------------------------
    void Cache::writeFile(const fs::path &path, const std::string &content) {
        if (!fs::exists(path.parent_path())) {
            fs::create_directories(path.parent_path());
        }

        std::ofstream file(path, std::ios::out | std::ios::trunc);
        file << content;
    }

    bool Cache::fileExists(const fs::path &path) {
        return fs::exists(path);
    }

    // -------------------------
    // Hash helpers
    // -------------------------
    std::string Cache::hashString(const std::string &input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(hash[i]);
        }

        return ss.str();
    }


} // namespace yogi::helper::cache