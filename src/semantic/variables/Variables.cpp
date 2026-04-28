//
// Created by Brayhan De Aza on 12/2/25.
//

#include "semantic/variables/Variables.h"
#include <visitors/nodes/nodes.h>
#include <string>
#include <unordered_set>
#include "semantic/BaseSemantic.h"
#include "utils/utils.h"

namespace yogi::semantic {
    using namespace yogi::visitor::nodes;

    // --------------------------------------------------------
    // TODO: Implement default variable initialization logic
    // --------------------------------------------------------
    void Variables::analyzeVariableWithoutAssignment(
        const VariableDeclarationNode& node,
        const Position& start,
        const Position& end
    ) {
        // TODO: semantic analysis disabled (placeholder)
        // This function will later assign default values based on type
        (void)node;
        (void)start;
        (void)end;
    }

    // --------------------------------------------------------
    // TODO: Implement full variable declaration type checking
    // --------------------------------------------------------
    void Variables::analyzeVariableDeclaration(
        VariableDeclarationNode& node,
        const std::string& source
    ) {
        // TODO: semantic analysis disabled (placeholder)
        // This will later:
        // - validate types
        // - validate BinaryExpressionNode structure
        // - ensure type compatibility

        (void)node;
        (void)source;
    }

    // --------------------------------------------------------
    // TODO: Implement reassignment type checking
    // --------------------------------------------------------
    void Variables::analyzeVariableReassignment(
        const VariableDeclarationNode& node,
        const std::string& source
    ) {
        // TODO: semantic analysis disabled (placeholder)
        // This will later:
        // - ensure variable exists
        // - ensure const rules
        // - validate type compatibility

        (void)node;
        (void)source;
    }

    // --------------------------------------------------------
    // KEEP FUNCTION (no-op fallback, safe default)
    // --------------------------------------------------------
    bool Variables::checkDataType(
        const std::string& dataType,
        const std::string& returnType,
        std::string& rValue
    ) {
        // TODO: implement proper type system later

        (void)dataType;
        (void)returnType;
        (void)rValue;

        // Temporary permissive behavior to avoid breaking compiler
        return true;
    }

} // namespace yogi::semantic