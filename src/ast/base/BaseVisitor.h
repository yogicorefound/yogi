//
// Created by Brayhan De Aza on 10/19/25.
//

#pragma once

#include "GrammarVisitor.h"
#include "llvm/IR/IRBuilder.h"
#include "semantic/scopes/Scope.h"
#include "semantic/semantic.h"

namespace yogi::visitor {

    class BaseVisitor : public GrammarVisitor, public utils::Errors, public utils::Helpers, public semantic::Semantic {
       protected:
        std::string& source;
        Grammar* parser;
        std::unique_ptr<semantic::Scope> rootScope;
        semantic::Scope* scope;

       public:
        explicit BaseVisitor(std::string& source, Grammar* parser)
            : source(source), parser(parser), rootScope(std::make_unique<semantic::Scope>(nullptr)), scope(rootScope.get()) {}

        void enterScope();
        void exitScope();

        semantic::Scope* getCurrentScope() const;
    };

} // namespace yogi::visitor
