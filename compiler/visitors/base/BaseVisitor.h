//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "semantic/scopes/Scope.h"
#include "cache/cache.h"

namespace yogi::visitor {

    class BaseVisitor : public compiler::cache::Cache, public GrammarVisitor, public utils::Errors, public utils::Helpers {
        protected:
            std::string &source;
            std::string &filePath;
            std::string &entryPath;
            Grammar *parser;
            std::unique_ptr<compiler::semantic::Scope> rootScope;
            compiler::semantic::Scope *scope;
            std::string currentPath;

        public:
            explicit BaseVisitor(std::string &source, std::string &filePath, std::string &entryPath, Grammar *parser) : Cache(getBuildDirectory()), source(source), filePath(filePath), entryPath(entryPath), parser(parser), rootScope(std::make_unique<compiler::semantic::Scope>(nullptr)), scope(rootScope.get()), currentPath(pathResolver(getBuildDirectory(), filePath).parent_path()) {
            }

            void enterScope();

            void exitScope();

            compiler::semantic::Scope *getCurrentScope() const;
    };

} // namespace yogi::visitor