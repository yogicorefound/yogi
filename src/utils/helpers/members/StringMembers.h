//
// Created by Brayhan De Aza on 12/29/25.
//

#pragma once

#include <regex>
#include "libs/json.hpp"

namespace yogi::utils::helpers {
    class StringMembers {
       public:
        static std::string toUpper(std::string s);
        static std::string toLower(std::string s);
        static std::string toTitle(std::string s);
        static std::string trim(std::string s);
        static std::string trimStart(std::string s);
        static std::string trimEnd(std::string s);
        static std::string replace(const std::string& input, const std::variant<std::string, std::regex>& search, const std::string& replacement);
        static std::string at(std::string s, long long i);
        static std::string repeat(const std::string& s, int times);
        static std::string slice(const std::string& str, long long start, long long end);
        static std::vector<std::string> split(const std::string& text, const std::variant<std::string, std::regex>& pattern);
    };
} // namespace yogi::utils::helpers