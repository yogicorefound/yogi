//
// Dictionaries.h
// Created by Brayhan De Aza on 12/2/25.
//

#ifndef CROMIO_DICTIONARIES_SEMANTIC_ANALYZE_H
#define CROMIO_DICTIONARIES_SEMANTIC_ANALYZE_H

#include "ast/nodes/nodes.h"
#include "semantic/BaseSemantic.h"
#include "semantic/scopes/Scope.h"
#include "utils/utils.h"

namespace cromio::semantic {

    class Dictionaries : public virtual BaseSemantic {
       public:
        // Now strongly typed — NO JSON
        static std::shared_ptr<visitor::nodes::DictionaryDeclarationNode> analyzeDictionariesDeclaration(std::shared_ptr<visitor::nodes::DictionaryDeclarationNode> decl, Scope* scope, const std::string& source);

        static void analyzeDictionaryItem(const std::shared_ptr<visitor::nodes::DictionaryDeclarationNode>& decl, visitor::nodes::DictionaryPairNode& pair, Scope* scope, const std::string& source);
    };

} // namespace cromio::semantic

#endif // CROMIO_DICTIONARIES_SEMANTIC_ANALYZE_H
