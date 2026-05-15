//
// Created by Brayhan De Aza on 12/2/25.
//

#include "semantic/variables/Variables.h"
#include <visitors/nodes/nodes.h>
#include <string>
#include "../base/BaseSemantic.h"
#include "utils/utils.h"
#include "utils/helpers/visitor/variables.h"


namespace yogi::compiler::semantic {
    using namespace yogi::visitor::nodes;
    using namespace yogi::utils::helpers;

    // --------------------------------------------------------
    // TODO: Implement default variable initialization logic
    // --------------------------------------------------------
    void Variables::analyzeVariableWithoutAssignment(const VariableDeclarationNode &node, const Position &start, const Position &end) {
    }

    // utils::Errors::throwTypeError(node.identifier, convertTypeToString(node.varType), node, source);


    void Variables::analyzeVariableDeclaration(const VariableDeclarationNode &node, const std::string &source) {
        auto [exprType, value, error, message] = utils::Helpers::evaluateExpression(node.value);

        const utils::Types from = exprType;
        const utils::Types to = node.varType;


        if (error) {
            utils::Errors::throwTypeError(node.identifier, utils::VisitorHelpers::convertTypeToString(node.varType), node, source);;
        }

        // =========================
        // ❌ FLOAT ↔ INT MIX (BLOCK)
        // =========================
        if ((utils::VisitorHelpers::isInteger(from) && utils::VisitorHelpers::isFloat(to)) || (utils::VisitorHelpers::isFloat(from) && utils::VisitorHelpers::isInteger(to))) {
            utils::Errors::throwTypeError(node.identifier, utils::VisitorHelpers::convertTypeToString(node.varType), node, source);
        }

        // =========================
        // ✔ INTEGER → INTEGER (ALLOW WIDENING)
        // =========================
        if (utils::VisitorHelpers::isInteger(from) && utils::VisitorHelpers::isInteger(to)) {

            // check range
            if (const long long v = std::stoll(value); !utils::VisitorHelpers::fitsInRange(v, to)) {
                utils::Errors::throwTypeError(node.identifier, utils::VisitorHelpers::convertTypeToString(node.varType), node, source);
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
        if (utils::VisitorHelpers::isFloat(from) && utils::VisitorHelpers::isFloat(to)) {
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
        utils::Errors::throwTypeError(node.identifier, utils::VisitorHelpers::convertTypeToString(node.varType), node, source);
    }

    // --------------------------------------------------------
    // TODO: Implement reassignment type checking
    // --------------------------------------------------------
    void Variables::analyzeVariableReassignment(const VariableDeclarationNode &node, const std::string &source) {
        // TODO: implement proper type system later
    }

} // namespace yogi::semantic