//
// Created by Brayhan De Aza on 12/29/25.
//

#include "StringMembers.h"

namespace yogi::utils::helpers {
    std::string StringMembers::toUpper(std::string s) {
        std::ranges::transform(s, s.begin(), [](const unsigned char c) { return std::toupper(c); });
        return s;
    }

    std::string StringMembers::trimStart(std::string s) {
        s.erase(s.begin(), std::ranges::find_if(s, [](const unsigned char ch) { return !std::isspace(ch); }));
        return s;
    }

    std::string StringMembers::trimEnd(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
        return s;
    }

    std::string StringMembers::trim(std::string s) {
        auto notSpace = [](const unsigned char ch) { return !std::isspace(ch); };

        // left trim
        s.erase(s.begin(), std::ranges::find_if(s, notSpace));

        // right trim
        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());

        return s;
    }

    std::string StringMembers::toLower(std::string s) {
        std::ranges::transform(s, s.begin(), [](const unsigned char c) { return std::tolower(c); });
        return s;
    }

    std::string StringMembers::toTitle(std::string s) {
        bool newWord = true;
        for (char& c : s) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                newWord = true;
            } else if (newWord) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                newWord = false;
            } else {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return s;
    }

    std::vector<std::string> StringMembers::split(const std::string& text, const std::variant<std::string, std::regex>& pattern) {
        std::vector<std::string> result;

        if (std::holds_alternative<std::string>(pattern)) {
            const std::string& sep = std::get<std::string>(pattern);

            if (sep.empty()) {
                // Optional: split into characters
                for (char c : text) {
                    result.emplace_back(1, c);
                }
                return result;
            }

            size_t start = 0;
            size_t pos;

            while ((pos = text.find(sep, start)) != std::string::npos) {
                result.push_back(text.substr(start, pos - start));
                start = pos + sep.length();
            }

            result.push_back(text.substr(start));
            return result;
        }

        const std::regex& rx = std::get<std::regex>(pattern);

        std::sregex_token_iterator it(text.begin(), text.end(), rx, -1);

        for (std::sregex_token_iterator end; it != end; ++it) {
            result.push_back(it->str());
        }

        return result;
    }

    std::string StringMembers::replace(const std::string& input, const std::variant<std::string, std::regex>& search, const std::string& replacement) {
        std::string result;
        if (std::holds_alternative<std::string>(search)) {
            // Reemplazo literal
            const std::string& literal = std::get<std::string>(search);
            if (literal.empty()) {
                throw std::runtime_error("replace(): search string cannot be empty");
            }

            size_t pos = 0;
            size_t found;
            while ((found = input.find(literal, pos)) != std::string::npos) {
                result.append(input, pos, found - pos);
                result.append(replacement);
                pos = found + literal.size();
            }
            result.append(input, pos, input.size() - pos);
        } else if (std::holds_alternative<std::regex>(search)) {
            // Reemplazo usando regex
            const std::regex& re = std::get<std::regex>(search);
            result = std::regex_replace(input, re, replacement);
        }

        return result;
    }

    std::string StringMembers::at(const std::string s, const long long i) {
        return std::string(1, s.at(i));
    }

    std::string StringMembers::repeat(const std::string& s, const int times) {
        if (times <= 0) return "";
        std::string result;
        result.reserve(s.size() * times);

        for (int i = 0; i < times; ++i) {
            result += s; // Concatenación directa
        }

        return result;
    }
} // namespace yogi::utils::helpers