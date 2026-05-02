//
// Created by Brayhan De Aza on 12/2/25.
//

#include "semantic/variables/Variables.h"
#include <visitors/nodes/nodes.h>
#include <string>
#include <unordered_set>

#include "helpers.h"
#include "semantic/BaseSemantic.h"
#include "utils/utils.h"

namespace yogi::semantic {
    using namespace yogi::visitor::nodes;

    // --------------------------------------------------------
    // TODO: Implement default variable initialization logic
    // --------------------------------------------------------
    void Variables::analyzeVariableWithoutAssignment(
        const VariableDeclarationNode &node,
        const Position &start,
        const Position &end
    ) {
    }

    // utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);


    void Variables::analyzeVariableDeclaration(const VariableDeclarationNode &node, const std::string &source) {
        auto [exprType, value, error, message] = utils::Helpers::evaluateExpression(node.value);

        if (error) {
            utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);;
        }

        using T = utils::Types;

        T from = exprType;
        T to = node.varType;

        // =========================
        // ❌ FLOAT ↔ INT MIX (BLOCK)
        // =========================
        if ((isInteger(from) && isFloat(to)) || (isFloat(from) && isInteger(to))) {
            utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);
        }

        // =========================
        // ✔ INTEGER → INTEGER (ALLOW WIDENING)
        // =========================
        if (isInteger(from) && isInteger(to)) {

            long long v = std::stoll(value);

            // check range
            if (!fitsInRange(v, to)) {
                utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);
            }

            // insert cast if needed
            if (from != to) {
                // node.value = createCastNode(to, std::move(node.value));
            }

            return;
        }

        // =========================
        // ✔ FLOAT → FLOAT ONLY
        // =========================
        if (isFloat(from) && isFloat(to)) {

            if (from != to) {
                // node.value = createCastNode(to, std::move(node.value));
            }

            return;
        }

        // =========================
        // EXACT MATCH
        // =========================
        if (from == to) return;

        // =========================
        // EVERYTHING ELSE → ERROR
        // =========================
        utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);
    }

    // --------------------------------------------------------
    // TODO: Implement reassignment type checking
    // --------------------------------------------------------
    void Variables::analyzeVariableReassignment(const VariableDeclarationNode &node, const std::string &source) {
        // TODO: implement proper type system later
    }


    // --------------------------------------------------------
    // KEEP FUNCTION (no-op fallback, safe default)
    // --------------------------------------------------------
    bool Variables::checkDataType(const std::string &dataType, const std::string &returnType) {
        // TODO: implement proper type system later

        // Temporary permissive behavior to avoid breaking compiler
        return true;
    }
} // namespace yogi::semantic