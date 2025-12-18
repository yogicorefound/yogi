//
// Created by Brayhan De Aza on 12/17/25.
//

#pragma once
#include <semantic/scopes/Scope.h>

#include <any>
#include <string>
#include <vector>

namespace cromio::visitor {
    class MembersByType {
       public:
        static std::vector<std::string> strAvailableMembers();
        static std::any processMembers(std::shared_ptr<nodes::VariableDeclarationNode> variable, const std::string& member, const std::vector<std::any>& arguments, const std::string& source);

        struct ResolvedItem {
            std::string type;
            std::string value;
            std::any node;
        };

        static ResolvedItem resolveItem(const std::any& itemResult, semantic::Scope* scope, const std::string& source);

       private:
        static std::any processStringMembers(std::shared_ptr<nodes::VariableDeclarationNode>& variable, const std::string& member, std::vector<std::any> arguments, const std::string& source);
    };

} // namespace cromio::visitor
