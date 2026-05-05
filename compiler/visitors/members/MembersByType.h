//
// Created by Brayhan De Aza on 12/17/25.
//

#pragma once
#include <semantic/scopes/Scope.h>
#include <any>
#include <string>
#include <vector>

namespace yogi::visitor {
    class MembersByType {
       public:
        struct ResolvedItem {
            std::string type;
            std::string value;
            std::any node;
        };

        static std::vector<std::string> strAvailableMembers();
        static nodes::MemberExpressionNode processMembers(const nodes::MemberExpressionNode& node, const nodes::StringLiteralNode& mNode, const bool& isMethod, const std::vector<std::any>& arguments, const std::string& source, semantic::Scope* scope);
        static ResolvedItem resolveItem(const std::any& itemResult, semantic::Scope* scope, const std::string& source);

       private:
        static nodes::MemberExpressionNode processStringMembers(const std::any& parentNode, const nodes::StringLiteralNode& mNode, const bool& isMethod, std::vector<std::any> arguments, const std::string& source, semantic::Scope* scope);
    };

} // namespace yogi::visitor
