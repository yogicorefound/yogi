//
// Created by Brayhan De Aza on 12/17/25.
//

#include "MembersByType.h"

#include <string>

namespace yogi::visitor {
    using namespace yogi::visitor::nodes;

    MembersByType::ResolvedItem MembersByType::resolveItem(const std::any& itemResult, semantic::Scope* scope, const std::string& source) {
        if (itemResult.type() == typeid(IntegerLiteralNode)) {
            auto n = std::any_cast<IntegerLiteralNode>(itemResult);
            return {"int", n.value, itemResult};
        }

        if (itemResult.type() == typeid(FloatLiteralNode)) {
            auto n = std::any_cast<FloatLiteralNode>(itemResult);
            return {"float", n.value, itemResult};
        }

        if (itemResult.type() == typeid(StringLiteralNode)) {
            auto n = std::any_cast<StringLiteralNode>(itemResult);
            return {"str", n.value, itemResult};
        }

        if (itemResult.type() == typeid(BooleanLiteralNode)) {
            auto n = std::any_cast<BooleanLiteralNode>(itemResult);
            return {"bool", n.value, itemResult};
        }

        if (itemResult.type() == typeid(BinaryExpressionNode)) {
            auto n = std::any_cast<BinaryExpressionNode>(itemResult);
            return {n.resultType, n.value, itemResult};
        }

        if (itemResult.type() == typeid(IdentifierLiteral)) {
            auto id = std::any_cast<IdentifierLiteral>(itemResult);

            if (const auto varInfo = scope->lookupVariable(id.value); varInfo.has_value()) {
                auto varNode = std::any_cast<VariableDeclarationNode>(varInfo.value());
                return resolveItem(varNode.value, scope, source);
            }

            if (const auto varInfo = scope->lookupArray(id.value); varInfo.has_value()) {
                auto varNode = std::any_cast<ArrayDeclarationNode>(varInfo.value());
                return resolveItem(varNode.elements, scope, source);
            }

            utils::Errors::throwScopeError("Variable '" + id.value + "' is not declared", id.value, id, source);
        }

        utils::Errors::throwError("Error", "Unsupported array element type", itemResult, source);

        return {}; // unreachable
    }

    std::vector<std::string> MembersByType::strAvailableMembers() {
        const std::vector<std::string> members = {
            "size",
            "lower",
            "upper",
            "title",
            "includes",
            "startWith",
            "endsWith",
            "find",
            "trim",
            "trimStart",
            "trimEnd",
            "replace",
            "split",
            "slice",
        };

        return members;
    }

    MemberExpressionNode MembersByType::processStringMembers(const std::any& parentNode, const StringLiteralNode& mNode, const bool& isMethod, std::vector<std::any> arguments, const std::string& source, semantic::Scope* scope) {
        const auto [pType, pValue, resolveNode] = utils::Helpers::resolveItem(parentNode);
        auto member = mNode.value;

        // Check if member is available for strings
        if (const auto availableMembers = strAvailableMembers(); std::ranges::find(availableMembers, member) == availableMembers.end()) {
            utils::Errors::throwScopeError("'" + pValue + "' has no member named '" + member, member, resolveNode, source);
        }

        // ✅ Check type before casting
        if (pType != "str") {
            utils::Errors::throwTypeError(member, pType, resolveNode, source);
        }

        auto stringLiteralNode = std::any_cast<StringLiteralNode>(resolveNode);
        // Properties (no arguments needed)
        if (member == "size" && isMethod) {
            IntegerLiteralNode node(std::to_string(pValue.size()), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::INTEGER_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "lower" && isMethod) {
            StringLiteralNode node(utils::Helpers::toLower(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);

            return memberNode;
        }

        if (member == "upper" && isMethod) {
            StringLiteralNode node(utils::Helpers::toUpper(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "title" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 1 argument, but received " + std::to_string(arguments.size()), pValue, source);
            }

            StringLiteralNode node(utils::Helpers::toTitle(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "includes" && isMethod) {
            if (arguments.size() != 1) {
                utils::Errors::throwError("Error", "'includes' requires exactly 1 argument, but received " + std::to_string(arguments.size()), pValue, source);
            }

            const auto argument = arguments[0];
            if (argument.type() == typeid(BinaryExpressionNode)) {
                const auto& exprPtr = std::any_cast<BinaryExpressionNode>(&arguments[0]);
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = pValue.contains(expression.value);
                BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);

                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            if (argument.type() == typeid(IdentifierLiteral)) {
                const auto identifier = std::any_cast<IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }
                std::string isIncluded = pValue.contains(value) ? "1" : "0";
                BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);

                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = pValue.contains(value);

            BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "startWith" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = pValue.starts_with(expression.value);
                BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);
                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            if (argument.type() == typeid(IdentifierLiteral)) {
                const auto identifier = std::any_cast<IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }

                std::string isIncluded = pValue.starts_with(value) ? "1" : "0";
                BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);

                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = pValue.starts_with(value);
            BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);

            auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "endsWith" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = pValue.ends_with(expression.value);
                BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);

                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            if (argument.type() == typeid(IdentifierLiteral)) {
                const auto identifier = std::any_cast<IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }
                std::string isIncluded = pValue.ends_with(value) ? "1" : "0";
                BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);
                auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = pValue.ends_with(value);
            BooleanLiteralNode node(isIncluded ? "1" : "0", mNode.start, mNode.end);

            auto memberNode = MemberExpressionNode(node, Kind::BOOLEAN_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "find" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                size_t index = pValue.find(expression.value);
                std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
                IntegerLiteralNode node(indexOf, mNode.start, mNode.end);

                auto memberNode = MemberExpressionNode(node, Kind::INTEGER_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            if (argument.type() == typeid(IdentifierLiteral)) {
                const auto identifier = std::any_cast<IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }

                size_t index = pValue.find(value);
                std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
                IntegerLiteralNode node(indexOf, mNode.start, mNode.end);

                auto memberNode = MemberExpressionNode(node, Kind::INTEGER_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            size_t index = pValue.find(value);
            std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
            IntegerLiteralNode node(indexOf, mNode.start, mNode.end);

            auto memberNode = MemberExpressionNode(node, Kind::INTEGER_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "trim" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), stringLiteralNode, source);
            }

            StringLiteralNode node(utils::Helpers::trim(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "trimStart" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), stringLiteralNode, source);
            }

            StringLiteralNode node(utils::Helpers::trimStart(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "trimEnd" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), stringLiteralNode, source);
            }

            StringLiteralNode node(utils::Helpers::trimEnd(pValue), mNode.start, mNode.end);
            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "replace" && isMethod) {
            if (arguments.size() != 2) {
                throw std::runtime_error("Error: 'replace' requires exactly 2 arguments, but received " + std::to_string(arguments.size()));
            }

            // Helper lambda to extract string argument
            auto extractStringArg = [&](const std::any& arg, const std::string& param) -> std::pair<std::string, std::string> {
                if (arg.type() == typeid(IdentifierLiteral)) {
                    const auto identifier = std::any_cast<IdentifierLiteral>(&arg);
                    const auto variableScoped = scope->lookupVariable(identifier->value);

                    if (!variableScoped.has_value()) {
                        utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                    }

                    const auto varNode = variableScoped.value();
                    if (varNode->varType == "str" || varNode->varType == "regex") {
                        const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);
                        return {value, varNode->varType};
                    }

                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                    return {"", ""};
                }

                const auto [type, value, node] = utils::Helpers::resolveItem(arg);
                if (type == "str" || type == "regex") {
                    return {value, type};
                }

                utils::Errors::throwError("Error", param + " must be a string", node, source);
                return {"", ""};
            };

            // Extract both arguments
            const auto [search, searchType] = extractStringArg(arguments[0], "search");
            const auto [replacement, replacementType] = extractStringArg(arguments[1], "replacement");

            // Perform replacement on the target variable
            const auto varNode = utils::Helpers::resolveItem(pValue);

            if (searchType == "regex") {
                const std::regex value(search);
                const auto resultValue = utils::Helpers::replace(pValue, value, replacement);

                auto node = StringLiteralNode(resultValue, mNode.start, mNode.end);
                auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
                return memberNode;
            }

            const auto resultValue = utils::Helpers::replace(pValue, search, replacement);
            const auto node = StringLiteralNode(resultValue, mNode.start, mNode.end);

            auto memberNode = MemberExpressionNode(node, Kind::STRING_LITERAL, mNode.start, mNode.end);
            return memberNode;
        }

        if (member == "split" && isMethod) {
            if (arguments.size() != 1) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), stringLiteralNode, source);
            }

            const auto [type, value, node] = utils::Helpers::resolveItem(arguments[0]);
            const auto items = utils::Helpers::split(pValue, value);

            std::vector<StringLiteralNode> elements;
            for (auto child : items) {
                // Helper lambda to extract string argument

                if (arguments[0].type() == typeid(StringLiteralNode)) {
                    auto argument = std::any_cast<StringLiteralNode>(arguments[0]);

                    auto item = StringLiteralNode(child, argument.start, argument.end);
                    elements.push_back(item);
                }
            }

            auto memberNode = MemberExpressionNode(elements, Kind::ARRAY_ELEMENTS, mNode.start, mNode.end);
            return memberNode;
        }

        utils::Errors::throwScopeError("member '" + member + "' not available for string type", member, stringLiteralNode, source);
        return MemberExpressionNode("", Kind::NONE_LITERAL, mNode.start, mNode.end);
    }

    // COMPREHENSIVE FIX for processMembers
    MemberExpressionNode MembersByType::processMembers(const MemberExpressionNode& node, const StringLiteralNode& mNode, const bool& isMethod, const std::vector<std::any>& arguments, const std::string& source, semantic::Scope* scope) {
        std::any result;

        if (mNode.value.empty()) {
            throw std::runtime_error("Error: empty member name");
        }
        const auto [type, value, _] = utils::Helpers::resolveItem(node.value);
        if (type == "str") {
            return processStringMembers(node.value, mNode, isMethod, arguments, source, scope);
        }

        utils::Errors::throwScopeError("member '" + mNode.value + "' not available for type '" + type + "'", mNode.value, mNode, source);
        return MemberExpressionNode("", Kind::NONE_LITERAL, node.start, node.end);
    }
} // namespace yogi::visitor
