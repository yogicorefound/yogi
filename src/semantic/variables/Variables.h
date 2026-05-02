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
        struct EvalExpressionResult {
            utils::Types type;
            std::string value;
            bool error;
            std::string message;
        };

        enum class Type {
            Int8,
            Int16,
            Int32,
            Int64,
            Float,
            Double,
            Bool,
            String,
            Void
        };


        // Analyze variable declaration without initial assignment
        static void analyzeVariableWithoutAssignment(const visitor::nodes::VariableDeclarationNode& node, const visitor::nodes::Position& start, const visitor::nodes::Position& end);
        static void analyzeVariableDeclaration(const visitor::nodes::VariableDeclarationNode& node, const std::string& source);
        static void analyzeVariableReassignment(const visitor::nodes::VariableDeclarationNode& node, const std::string& source);

        // Helpers
        static bool isImplicitlyAssignable( utils::Types from,  utils::Types to, long long value) ;
        static bool checkDataType(const std::string& dataType, const std::string& returnType);

    };

} // namespace yogi::semantic
