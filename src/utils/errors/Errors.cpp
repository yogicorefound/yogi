//
// Created by Brayhan De Aza on 11/29/25.
//

#include "Errors.h"
#include <ast/nodes/nodes.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

namespace cromio::utils {

    // ------------------- Helper to extract position from any node -------------------
    struct NodePosition {
        size_t startLine;
        size_t startCol;
        size_t endLine;
        size_t endCol;
    };

    NodePosition extractPosition(const std::any& node) {
        using namespace cromio::visitor::nodes;

        try {
            // Try to extract BaseNode
            if (node.type() == typeid(IntegerLiteralNode)) {
                auto n = std::any_cast<IntegerLiteralNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(FloatLiteralNode)) {
                auto n = std::any_cast<FloatLiteralNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(StringLiteralNode)) {
                auto n = std::any_cast<StringLiteralNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(BooleanLiteralNode)) {
                auto n = std::any_cast<BooleanLiteralNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(NoneLiteralNode)) {
                auto n = std::any_cast<NoneLiteralNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(IdentifierLiteral)) {
                auto n = std::any_cast<IdentifierLiteral>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(BinaryExpressionNode)) {
                auto n = std::any_cast<BinaryExpressionNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(VariableDeclarationNode)) {
                auto n = std::any_cast<VariableDeclarationNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(ArrayDeclarationNode)) {
                auto n = std::any_cast<ArrayDeclarationNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(DictionaryDeclarationNode)) {
                auto n = std::any_cast<DictionaryDeclarationNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(StatementNode)) {
                auto n = std::any_cast<StatementNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
            if (node.type() == typeid(ProgramNode)) {
                auto n = std::any_cast<ProgramNode>(node);
                return NodePosition{n.start.line, n.start.column, n.end.line, n.end.column};
            }
        } catch (const std::bad_any_cast&) {
            // Return default position if cast fails
        }

        return NodePosition{1, 0, 1, 0};
    }

    // Overload for Position struct directly
    NodePosition extractPosition(const visitor::nodes::Position& start, const visitor::nodes::Position& end) {
        return NodePosition{start.line, start.column, end.line, end.column};
    }

    void Errors::printContext(const NodePosition& pos, const std::string& source, const std::string& hint) {
        constexpr int context = 2;
        int startLine = static_cast<int>(pos.startLine);
        int startCol = static_cast<int>(pos.startCol);
        int endLine = static_cast<int>(pos.endLine);
        int endCol = static_cast<int>(pos.endCol);

        std::istringstream stream(source);
        std::string lineText;
        std::vector<std::string> lines;
        while (std::getline(stream, lineText))
            lines.push_back(lineText);

        const int totalLines = static_cast<int>(lines.size());

        int from = std::max(1, startLine - context);
        int to = std::min(totalLines, endLine + context);

        for (int i = from; i <= to; i++) {
            std::string prefix = i >= startLine && i <= endLine ? "\033[1;37m>" : " ";
            std::cout << prefix << " \033[36m" << i << " | \033[0m" << lines[i - 1] << "\n";

            if (i == startLine) {
                std::cout << "    ";
                int underlineStart = startCol;
                int underlineSize = startLine == endLine ? std::max(1, endCol - startCol + 1) : static_cast<int>(lines[i - 1].size()) - startCol;

                std::cout << std::string(underlineStart, ' ');
                std::cout << "\033[1;31m" << std::string(underlineSize, '^') << "\033[0m";

                if (!hint.empty()) {
                    std::cout << " \033[33m" << hint << "\033[0m";
                }
                std::cout << "\n";
            }

            if (i > startLine && i <= endLine) {
                std::cout << "    ";
                std::cout << "\033[1;31m" << std::string(lines[i - 1].size(), '^') << "\033[0m\n";
            }
        }

        std::cout << "\n";
    }


    void Errors::throwError(const std::string& errorType, const std::string& message, const std::any& node, const std::string& source) {
        std::cerr << "\n\033[1;31m" << errorType << ": " << message << "\033[0m\n";
        const NodePosition pos = extractPosition(node);
        printContext(pos, source, "");
        std::exit(1);
    }

    void Errors::throwRangeError(const std::string& message, const std::any& node, const std::string& source) {
        throwError("RangeError", message, node, source);
    }

    void Errors::throwReassignmentError(const std::string& message, const std::any& node, const std::string& source) {
        throwError("ReassignmentError", message, node, source);
    }

    void Errors::throwTypeError(const std::string& identifier, const std::string& dataType, const std::any& node, const std::string& source) {
        const std::string typeMsg = getTypeMessage(dataType);
        const std::string message = "'" + identifier + "' expects " + typeMsg;
        throwError("TypeError", message, node, source);
    }

    void Errors::throwScopeError(const std::string& message, const std::string& identifier, const std::any& node, const std::string& source) {
        throwError("ScopeError", message, node, source);
        std::exit(1);
    }

    void Errors::throwTypeMismatchError(const std::string& identifier, const std::string& expectedType, const std::string& actualType, const std::any& node, const std::string& source) {
        const std::string expectedMsg = getTypeMessage(expectedType);
        const std::string actualMsg = getTypeMessage(actualType);

        const std::string message = "Type mismatch for '" + identifier +
            "'\n"
            "  Expected: " +
            expectedMsg +
            "\n"
            "  Actual:   " +
            actualMsg;

        throwError("TypeError", message, node, source);
    }

    std::string Errors::getTypeMessage(const std::string& dataType) {
        // SIGNED
        if (dataType == "int8")
            return "signed 8-bit integer";
        if (dataType == "int16")
            return "signed 16-bit integer";
        if (dataType == "int" || dataType == "int32")
            return "signed 32-bit integer";
        if (dataType == "int64")
            return "signed 64-bit integer";

        // UNSIGNED
        if (dataType == "uint8")
            return "unsigned 8-bit integer";
        if (dataType == "uint16")
            return "unsigned 16-bit integer";
        if (dataType == "uint" || dataType == "uint32")
            return "unsigned 32-bit integer";
        if (dataType == "uint64")
            return "unsigned 64-bit integer";

        // FLOAT
        if (dataType == "float" || dataType == "float32")
            return "32-bit float";
        if (dataType == "float64")
            return "64-bit float";

        // BOOLEAN
        if (dataType == "bool")
            return "boolean";

        // STRING
        if (dataType == "str")
            return "string";

        // ARRAY
        if (dataType == "int[]")
            return "int array";
        if (dataType == "uint[]")
            return "unsigned int array";
        if (dataType == "float[]")
            return "float array";
        if (dataType == "bool[]")
            return "boolean array";
        if (dataType == "str[]")
            return "string array";

        return "'" + dataType + "'";
    }

} // namespace cromio::utils