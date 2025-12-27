//
// Created by Brayhan De Aza on 12/17/25.
//

#include "MembersByType.h"

#include <string>

namespace yogi::visitor {
    MembersByType::ResolvedItem MembersByType::resolveItem(const std::any& itemResult, semantic::Scope* scope, const std::string& source) {
        if (itemResult.type() == typeid(nodes::IntegerLiteralNode)) {
            auto n = std::any_cast<nodes::IntegerLiteralNode>(itemResult);
            return {"int", n.value, itemResult};
        }

        if (itemResult.type() == typeid(nodes::FloatLiteralNode)) {
            auto n = std::any_cast<nodes::FloatLiteralNode>(itemResult);
            return {"float", n.value, itemResult};
        }

        if (itemResult.type() == typeid(nodes::StringLiteralNode)) {
            auto n = std::any_cast<nodes::StringLiteralNode>(itemResult);
            return {"str", n.value, itemResult};
        }

        if (itemResult.type() == typeid(nodes::BooleanLiteralNode)) {
            auto n = std::any_cast<nodes::BooleanLiteralNode>(itemResult);
            return {"bool", n.value, itemResult};
        }

        if (itemResult.type() == typeid(nodes::BinaryExpressionNode)) {
            auto n = std::any_cast<nodes::BinaryExpressionNode>(itemResult);
            return {n.resultType, n.value, itemResult};
        }

        if (itemResult.type() == typeid(nodes::IdentifierLiteral)) {
            auto id = std::any_cast<nodes::IdentifierLiteral>(itemResult);

            if (const auto varInfo = scope->lookupVariable(id.value); varInfo.has_value()) {
                auto varNode = std::any_cast<nodes::VariableDeclarationNode>(varInfo.value());
                return resolveItem(varNode.value, scope, source);
            }

            if (const auto varInfo = scope->lookupArray(id.value); varInfo.has_value()) {
                auto varNode = std::any_cast<nodes::ArrayDeclarationNode>(varInfo.value());
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

    std::any MembersByType::processStringMembers(nodes::VariableDeclarationNode& variable, const std::string& member, const bool& isMethod, std::vector<std::any> arguments, const std::string& source, semantic::Scope* scope) {
        // Check if member is available for strings
        if (const auto availableMembers = strAvailableMembers(); std::ranges::find(availableMembers, member) == availableMembers.end()) {
            utils::Errors::throwScopeError("'" + variable.identifier + "' has no member named '" + member, member, variable, source);
        }

        // ✅ Check type before casting
        if (variable.value.type() != typeid(nodes::StringLiteralNode)) {
            std::cout << "Error: variable.value is not a StringLiteralNode (actual type: " + std::string(variable.value.type().name()) + ")";
            std::exit(1);
        }

        auto stringLiteralNode = std::any_cast<nodes::StringLiteralNode>(variable.value);

        // Properties (no arguments needed)
        if (member == "size" && isMethod) {
            nodes::IntegerLiteralNode node(std::to_string(stringLiteralNode.value.size()), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::INTEGER_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "lower" && isMethod) {
            nodes::StringLiteralNode node(utils::Helpers::toLower(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "upper" && isMethod) {
            nodes::StringLiteralNode node(utils::Helpers::toUpper(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "title" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 1 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            nodes::StringLiteralNode node(utils::Helpers::toTitle(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "includes" && isMethod) {
            if (arguments.size() != 1) {
                utils::Errors::throwError("Error", "'includes' requires exactly 1 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            const auto argument = arguments[0];
            if (argument.type() == typeid(nodes::BinaryExpressionNode)) {
                const auto& exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0]);
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = stringLiteralNode.value.contains(expression.value);
                nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            if (argument.type() == typeid(nodes::IdentifierLiteral)) {
                const auto identifier = std::any_cast<nodes::IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }
                std::string isIncluded = stringLiteralNode.value.contains(value) ? "1" : "0";
                nodes::BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = stringLiteralNode.value.contains(value);

            nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "startWith" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = stringLiteralNode.value.starts_with(expression.value);
                nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);
                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            if (argument.type() == typeid(nodes::IdentifierLiteral)) {
                const auto identifier = std::any_cast<nodes::IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }

                std::string isIncluded = stringLiteralNode.value.starts_with(value) ? "1" : "0";
                nodes::BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = stringLiteralNode.value.starts_with(value);
            nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);

            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "endsWith" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = stringLiteralNode.value.ends_with(expression.value);
                nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            if (argument.type() == typeid(nodes::IdentifierLiteral)) {
                const auto identifier = std::any_cast<nodes::IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }
                std::string isIncluded = stringLiteralNode.value.ends_with(value) ? "1" : "0";
                nodes::BooleanLiteralNode node(isIncluded, varNode->start, varNode->end);
                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            bool isIncluded = stringLiteralNode.value.ends_with(value);
            nodes::BooleanLiteralNode node(isIncluded ? "1" : "0", variable.start, variable.end);

            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::BOOLEAN_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "find" && isMethod) {
            const auto argument = arguments[0];
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                size_t index = stringLiteralNode.value.find(expression.value);
                std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
                nodes::IntegerLiteralNode node(indexOf, variable.start, variable.end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::INTEGER_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            if (argument.type() == typeid(nodes::IdentifierLiteral)) {
                const auto identifier = std::any_cast<nodes::IdentifierLiteral>(&arguments[0]);
                const auto variableScoped = scope->lookupVariable(identifier->value);

                if (!variableScoped.has_value()) {
                    utils::Errors::throwScopeError("Variable '" + identifier->value + "' is not declared", identifier->value, identifier, source);
                }

                const auto varNode = variableScoped.value();
                const auto [type, value, _] = utils::Helpers::resolveItem(varNode->value);

                if (varNode->varType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", varNode, source);
                }

                size_t index = stringLiteralNode.value.find(value);
                std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
                nodes::IntegerLiteralNode node(indexOf, variable.start, variable.end);

                auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::INTEGER_LITERAL, variable.start, variable.end);
                return memberNode;
            }

            const auto& [type, value, arrNode] = utils::Helpers::resolveItem(arguments[0]);
            if (type != "str") {
                utils::Errors::throwError("Error", "Argument must be a string", arrNode, source);
            }

            size_t index = stringLiteralNode.value.find(value);
            std::string indexOf = index != std::string::npos ? std::to_string(index) : std::to_string(-1);
            nodes::IntegerLiteralNode node(indexOf, variable.start, variable.end);

            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::INTEGER_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "trim" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            nodes::StringLiteralNode node(utils::Helpers::trim(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "trimStart" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            nodes::StringLiteralNode node(utils::Helpers::trimStart(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "trimEnd" && isMethod) {
            if (arguments.size() > 0) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            nodes::StringLiteralNode node(utils::Helpers::trimEnd(stringLiteralNode.value), variable.start, variable.end);
            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "replace" && isMethod) {
            if (arguments.size() != 2) {
                throw std::runtime_error("Error: 'replace' requires exactly 2 arguments, but received " + std::to_string(arguments.size()));
            }

            // Helper lambda to extract string argument
            auto extractStringArg = [&](const std::any& arg, const std::string& param) -> std::pair<std::string, std::string> {
                if (arg.type() == typeid(nodes::IdentifierLiteral)) {
                    const auto identifier = std::any_cast<nodes::IdentifierLiteral>(&arg);
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
            const auto varNode = utils::Helpers::resolveItem(variable.value);

            if (searchType == "regex") {
                const std::regex value(search);
                const auto resultValue = utils::Helpers::replace(varNode.value, value, replacement);

                return nodes::StringLiteralNode(resultValue, variable.start, variable.end);
            }

            const auto resultValue = utils::Helpers::replace(varNode.value, search, replacement);
            const auto node = nodes::StringLiteralNode(resultValue, variable.start, variable.end);

            auto memberNode = nodes::MemberExpressionNode(node, nodes::Kind::STRING_LITERAL, variable.start, variable.end);
            return memberNode;
        }

        if (member == "split" && isMethod) {
            if (arguments.size() != 1) {
                utils::Errors::throwError("Error", "'title' requires exactly 0 argument, but received " + std::to_string(arguments.size()), variable, source);
            }

            const auto [type, value, node] = utils::Helpers::resolveItem(arguments[0]);
            const auto items = utils::Helpers::split(stringLiteralNode.value, value);

            std::vector<nodes::StringLiteralNode> elements;
            for (auto child : items) {
                // Helper lambda to extract string argument

                if (arguments[0].type() == typeid(nodes::StringLiteralNode)) {
                    auto argument = std::any_cast<nodes::StringLiteralNode>(arguments[0]);

                    auto item = nodes::StringLiteralNode(child, argument.start, argument.end);
                    elements.push_back(item);
                }
            }

            auto memberNode = nodes::MemberExpressionNode(elements, nodes::Kind::ARRAY_ELEMENTS, variable.start, variable.end);
            return memberNode;
        }

        utils::Errors::throwScopeError("Error: member '" + member + "' not available for string type", member, variable, source);
        return {};
    }

    // COMPREHENSIVE FIX for processMembers
    std::any MembersByType::processMembers(nodes::VariableDeclarationNode& variable, const std::string& member, const bool& isMethod, const std::vector<std::any>& arguments, const std::string& source, semantic::Scope* scope) {
        std::any result;

        if (member.empty()) {
            throw std::runtime_error("Error: empty member name");
        }

        if (variable.varType == "str") {
            return processStringMembers(variable, member, isMethod, arguments, source, scope);
        }

        utils::Errors::throwScopeError("Error: member '" + member + "' not available for type '" + variable.varType + "'", member, variable, source);
        return {};
    }
} // namespace yogi::visitor
