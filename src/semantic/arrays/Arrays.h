//
// Created by Brayhan De Aza on 12/2/25.
//

#pragma once

#include <semantic/scopes/Scope.h>
#include "semantic/BaseSemantic.h"
#include "utils/utils.h"

namespace yogi::semantic {
    class Arrays : public virtual BaseSemantic {
       public:
        static json analyzeArrayDeclaration(const json& node, const std::string& source);
        static void analyzeArrayItems(const std::string& identifier, const std::string& returnType, const std::string& rValue, const std::string& boolValue, const std::string& dataType, const std::any& node, const std::string& source);
        static bool checkArrayDataType(const std::string& dataType, const std::string& returnType, const std::string& value);
        static void processArrayItems(const std::string& arrayType, std::string& itemType, std::any& itemValue, std::string& boolValue, std::string& rValue, const std::any& itemResult, Scope* scope, const std::string& source);

        struct ResolvedItem {
            std::string type;
            std::string value;
            std::any node;
        };

        static ResolvedItem resolveItem(const std::any& itemResult, Scope* scope, const std::string& source);
    };
} // namespace yogi::semantic
