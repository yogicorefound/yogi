//
// Created by Brayhan De Aza on 12/10/25.
//

#pragma once

#include "BaseNode.h"

namespace yogi::visitor::nodes {
    // Dictionary Key-Value Pair
    struct DictionaryPairNode : BaseNode {
        std::any key; // Key (usually string or identifier)
        std::any value; // Value (any literal or expression)

        explicit DictionaryPairNode(std::any k, std::any v, const Position start, const Position end) : BaseNode(Kind::DICTIONARY_PAIR, start, end), key(std::move(k)), value(std::move(v)) {}
    };

    struct DictionaryDeclarationNode : BaseNode {
        std::string identifier; // Dictionary name
        std::string keyType; // Type of keys
        std::string valueType; // Type of values
        std::vector<DictionaryPairNode> pairs; // Key-value pairs
        size_t size; // Number of pairs

        explicit DictionaryDeclarationNode(const std::string& id, const std::string& kType, const std::string& vType, const Position start, const Position end) : BaseNode(Kind::DICTIONARY_DECLARATION, start, end), identifier(id), keyType(kType), valueType(vType), size(0) {}
    };

    struct DataTypeNode : BaseNode {
        std::string typeName;

        DataTypeNode(const std::string& t, const Position& start, const Position& end) : BaseNode(Kind::DATA_TYPE, start, end), typeName(t) {}
    };

    struct DictionaryTypeNode : BaseNode {
        std::string keyType;
        std::string valueType;

        DictionaryTypeNode(const std::string& k, const std::string& v, const Position& start, const Position& end) : BaseNode(Kind::DICTIONARY_TYPE, start, end), keyType(k), valueType(v) {}
    };

} // namespace yogi::visitor::nodes
