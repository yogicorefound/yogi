//
// Created by Brayhan De Aza on 5/1/26.
//


#include <any>
#include <string>
#include "semantic/variables/helpers.h"
#include "utils/helpers/Helpers.h"
#include "utils/types/Types.h"

namespace yogi::utils::helpers {

    struct EvalExpressionResult {
        Types type;
        std::string value;
        bool error;
        std::string message;
    };


    inline double applyOperator(const double l, const double r, std::string op) {
        if (op == "+") return l + r;
        if (op == "-") return l - r;
        if (op == "*") return l * r;
        if (op == "/") return l / r;
        return 0;
    }


    inline  EvalExpressionResult evaluateExpression(const std::any &node) {
        // INTEGER
        if (const auto n = std::any_cast<visitor::nodes::IntegerLiteralNode>(&node)) {
            const Types type = semantic::inferIntegerType(Helpers::parseInteger(n->value));
            return {type, n->value, false, ""};
        }

        // FLOAT
        if (const auto n = std::any_cast<visitor::nodes::FloatLiteralNode>(&node)) {
            return { Types::Float, n->value, false, ""};
        }

        // STRING
        if (auto n = std::any_cast<visitor::nodes::StringLiteralNode>(&node)) {
            return { Types::String, n->value, false, ""};
        }

        // BOOLEAN → ERROR (for now strict)
        if (auto n = std::any_cast<visitor::nodes::BooleanLiteralNode>(&node)) {
            return { Types::Void, "", true, "Boolean not allowed"};
        }

        // BINARY
        if (const auto n = std::any_cast<visitor::nodes::BinaryExpressionNode>(&node)) {
            auto left = evaluateExpression(n->left);
            if (left.error) return left;

            auto right = evaluateExpression(n->right);
            if (right.error) return right;

            Types ltype = left.type;
            Types rtype = right.type;

            // ❌ BOOLEAN BLOCK
            if (ltype == Types::Boolean || rtype == Types::Boolean) {
                return { Types::Void, "", true, "Boolean cannot be used"};
            }

            // STRING RULE (STRICT)
            if (ltype == Types::String || rtype == Types::String) {
                if (ltype != Types::String || rtype != Types::String) {
                    return { Types::Void, "", true, "Cannot mix string with other types"};
                }

                return {
                    Types::String,
                    left.value + right.value,
                    false,
                    ""
                };
            }

            // NUMERIC RULE (INT + FLOAT + DOUBLE + SIGNED/UNSIGNED)
            if (semantic::isNumeric(ltype) && semantic::isNumeric(rtype)) {
                const double l = std::stod(left.value);
                const double r = std::stod(right.value);
                const double result = applyOperator(l, r, n->op);

                // determine resulting type
                const Types resultType = semantic::resolveNumericResultType(ltype, rtype);

                return {
                    resultType,
                    std::to_string(result),
                    false,
                    ""
                };
            }

            return { Types::Void, "", true, "Invalid binary operation"};
        }

        return { Types::Void, "", true, "Unknown node"};
    }
    
}