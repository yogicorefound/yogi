//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include <any>
#include <string>
#include <vector>
#include "BaseNode.h"

namespace yogi::visitor::nodes {
    // Array Element (for array initialization)
    struct ArrayElementNode {
        std::any value; // Puede ser un valor simple o std::vector<ArrayElementNode>
        std::string type;
        Position start;
        Position end;

        // Constructor para valor simple
        ArrayElementNode(std::any val, const std::string& t, const Position& s, const Position& e) : value(std::move(val)), type(t), start(s), end(e) {}

        // Constructor para sub-array
        ArrayElementNode(std::vector<ArrayElementNode> val, const std::string& t, const Position& s, const Position& e) : value(std::move(val)), type(t), start(s), end(e) {}
    };

    struct ArrayDeclarationNode {
        std::string identifier;
        std::string type; // tipo del elemento
        bool isConstant;
        std::vector<size_t> dimensions; // vacío si es dinámico
        std::vector<ArrayElementNode> elements;
        Position start;
        Position end;

        ArrayDeclarationNode(const std::string& id, const std::string& t, const bool constant, std::vector<size_t> dims, std::vector<ArrayElementNode> elems, const Position& s, const Position& e)
            : identifier(id), type(t), isConstant(constant), dimensions(std::move(dims)), elements(std::move(elems)), start(s), end(e) {}
    };

} // namespace yogi::visitor::nodes
