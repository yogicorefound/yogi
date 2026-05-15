//
// Created by Brayhan De Aza on 12/2/25.
//

#pragma once

#include <semantic/scopes/Scope.h>
#include "compiler/semantic/base/BaseSemantic.h"

namespace yogi::compiler::semantic {
    class Arrays : public virtual BaseSemantic {
       public:
        static visitor::nodes::ArrayDeclarationNode analyzeArrayDeclaration(visitor::nodes::ArrayDeclarationNode& node, const std::string& source);
        static void analyzeArrayItems(const std::string& identifier, const std::string& returnType, const std::string& rValue, const std::string& dataType, const std::any& node, const std::string& source);
        static bool checkArrayDataType(const std::string& dataType, const std::string& returnType, const std::string& value);
        static void processArrayItems(const std::string& identifier, const std::string& arrayType, std::string& itemType, std::any& itemValue, std::string& boolValue, std::string& rValue, const std::any& itemResult, const std::string& source);
        static void checkArrayItemFloatRange(const std::string& arrayType, const std::any& value, const std::any& node, const std::string& source);
        static void checkNumberRange(const std::string& dataType, const std::string& rValue, const std::any& node, const std::string& source);

       private:
        static void analyzeUnOrSingedInteger(const std::string& dataType, const std::string& rValue, const std::string& identifier, const std::string& returnType, visitor::nodes::ArrayDeclarationNode& node, const std::string& source);
    };
} // namespace yogi::semantic
