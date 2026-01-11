//
// Created by Brayhan De Aza on 12/2/25.
//

#pragma once

#include <semantic/scopes/Scope.h>
#include <visitors/nodes/nodes.h>
#include <string>

namespace yogi::semantic {
    class Variables : public virtual BaseSemantic {
       public:
        // Analyze variable declaration without initial assignment
        static void analyzeVariableWithoutAssignment(const visitor::nodes::VariableDeclarationNode& node, const visitor::nodes::Position& start, const visitor::nodes::Position& end);

        // Analyze variable declaration with value
        static void analyzeVariableDeclaration(visitor::nodes::VariableDeclarationNode& node, const std::string& source);

        static void analyzeVariableReassignment(const visitor::nodes::VariableDeclarationNode& node, const std::string& source);
        // Check if data type matches return type
        static bool checkDataType(const std::string& dataType, const std::string& returnType, std::string& rValue);
    };

} // namespace yogi::semantic
