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
            // Properties
            "size",

            // Methods
            "lower",
            "upper",
            "title",
            "includes",

            "startWith",
            "endsWith",
            "index",
            "trim",
            "normalize",
        };

        return members;
    }

    std::any MembersByType::processStringMembers(
        nodes::VariableDeclarationNode& variable,
        const std::string& member,
        std::vector<std::any> arguments,
        const std::string& source) {
        // Check if member is available for strings
        if (const auto availableMembers = strAvailableMembers(); std::ranges::find(availableMembers, member) == availableMembers.end()) {
            std::cout << "start:ine: " << variable.start.line << " startColum: " << variable.end.line << std::endl;
            std::cout << "end:ine: " << variable.end.line << " endColum: " << variable.end.line << std::endl;

            utils::Errors::throwScopeError("'" + variable.identifier + "' has no member named '" + member, member, variable, source);
        }

        // ✅ Check type before casting
        if (variable.value.type() != typeid(nodes::StringLiteralNode)) {
            std::cout << "Error: variable.value is not a StringLiteralNode (actual type: " + std::string(variable.value.type().name()) + ")";
            std::exit(1);
        }

        auto stringLiteralNode = std::any_cast<nodes::StringLiteralNode>(variable.value);
        std::cout << "Processing string member '" << member << "' on value: " << stringLiteralNode.value << std::endl;

        // Properties (no arguments needed)
        if (member == "size") {
            nodes::IntegerLiteralNode node(std::to_string(stringLiteralNode.value.size()), variable.start, variable.end);
            return node;
        }

        if (member == "lower") {
            nodes::StringLiteralNode node(utils::Helpers::toLower(stringLiteralNode.value), variable.start, variable.end);
            std::cout << "Lower: " << stringLiteralNode.value << std::endl;
            return node;
        }

        if (member == "upper") {
            nodes::StringLiteralNode node(utils::Helpers::toUpper(stringLiteralNode.value), variable.start, variable.end);
            return node;
        }

        if (member == "title") {
            nodes::StringLiteralNode node(utils::Helpers::toTitle(stringLiteralNode.value), variable.start, variable.end);
            return node;
        }

        // Methods (require arguments)
        if (member == "includes") {
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'includes' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool isIncluded = stringLiteralNode.value.contains(expression.value);
                nodes::BooleanLiteralNode node(isIncluded ? "true" : "false", variable.start, variable.end);
                return node;
            }
            throw std::runtime_error("Error: argument[0] is not BinaryExpressionNode for 'includes'");
        }

        if (member == "startWith") {
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'startWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool starts = stringLiteralNode.value.starts_with(expression.value);
                nodes::BooleanLiteralNode node(starts ? "true" : "false", variable.start, variable.end);
                return node;
            }

            throw std::runtime_error("Error: argument[0] is not BinaryExpressionNode for 'startWith'");
        }

        if (member == "endsWith") {
            if (arguments.size() != 1) {
                throw std::runtime_error("Error: 'endsWith' requires exactly 1 argument, got " + std::to_string(arguments.size()));
            }

            if (auto exprPtr = std::any_cast<nodes::BinaryExpressionNode>(&arguments[0])) {
                auto& expression = *exprPtr;
                if (expression.resultType != "str") {
                    utils::Errors::throwError("Error", "Argument must be a string", expression, source);
                }

                bool ends = stringLiteralNode.value.ends_with(expression.value);
                nodes::BooleanLiteralNode node(ends ? "true" : "false", variable.start, variable.end);
                return node;
            }

            throw std::runtime_error("Error: argument[0] is not BinaryExpressionNode for 'endsWith'");
        }

        utils::Errors::throwScopeError("Error: member '" + member + "' not available for string type", member, variable, source);
        return {};
    }

    // COMPREHENSIVE FIX for processMembers
    std::any MembersByType::processMembers(
        nodes::VariableDeclarationNode& variable,
        const std::string& member,
        const std::vector<std::any>& arguments,
        const std::string& source) {
        std::any result;

        if (member.empty()) {
            throw std::runtime_error("Error: empty member name");
        }

        if (variable.varType == "str") {
            return processStringMembers(variable, member, arguments, source);
        }

        utils::Errors::throwScopeError("Error: member '" + member + "' not available for type '" + variable.varType + "'", member, variable, source);
        return {};
    }
} // namespace yogi::visitor
