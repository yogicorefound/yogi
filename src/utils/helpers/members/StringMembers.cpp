//
// Created by Brayhan De Aza on 12/29/25.
//

#include "StringMembers.h"
#include <iostream>
#include <sstream>

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

    std::string StringMembers::at(const std::string& s, const long long i) {
        return std::string(1, s.at(i));
    }

    std::string StringMembers::repeat(const std::string& s, const int times) {
        if (times <= 0)
            return "";
        std::string result;
        result.reserve(s.size() * times);

        for (int i = 0; i < times; ++i) {
            result += s; // Concatenación directa
        }

        return result;
    }

    std::string StringMembers::slice(const std::string& str, long long start, long long end) {
        const int len = static_cast<int>(str.size());

        if (start < 0) {
            start += len;
        }

        if (end < 0) {
            end += len;
        }

        if (start < 0) {
            start = 0;
        }

        if (end > len) {
            end = len;
        }

        if (start > end) {
            return "";
        }

        return str.substr(start, end - start);
    }

    std::vector<std::string> StringMembers::match(const std::string& str, const std::regex& pattern) {
        std::vector<std::string> results;

        try {
            std::sregex_iterator begin(str.begin(), str.end(), pattern);
            std::sregex_iterator end;

            for (auto it = begin; it != end; ++it) {
                results.push_back(it->str());
            }
        } catch (const std::regex_error& e) {
            std::cerr << "Regex error: " << e.what() << std::endl;
            // Opcional: lanzar excepción en tu lenguaje
        }

        return results; // Retorna array, aunque sea vacío
    }

    StringMembers::UnicodeFormat StringMembers::resolveUnicodeFormat(const std::string& format) {
        if (format == "hex")
            return UnicodeFormat::HEX;
        if (format == "decimal")
            return UnicodeFormat::DECIMAL;
        if (format == "utf-8")
            return UnicodeFormat::UTF8;

        throw std::runtime_error("Invalid unicode format: " + format);
    }

    std::vector<uint32_t> StringMembers::utf8ToCodepoints(const std::string& text) {
        std::vector<uint32_t> result;

        for (size_t i = 0; i < text.size();) {
            uint32_t cp = 0;

            if (const unsigned char c = text[i]; (c & 0x80) == 0) {
                cp = c;
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                cp = (c & 0x1F) << 6 | text[i + 1] & 0x3F;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                cp = (c & 0x0F) << 12 | (text[i + 1] & 0x3F) << 6 | text[i + 2] & 0x3F;
                i += 3;
            } else {
                cp = (c & 0x07) << 18 | (text[i + 1] & 0x3F) << 12 | (text[i + 2] & 0x3F) << 6 | text[i + 3] & 0x3F;
                i += 4;
            }

            result.push_back(cp);
        }

        return result;
    }

    std::vector<std::string> StringMembers::unicode(const std::string& text, const UnicodeFormat format) {
        std::vector<std::string> result;
        if (format == UnicodeFormat::UTF8) {
            // UTF‑8 → bytes
            for (unsigned char c : text) {
                std::ostringstream oss;
                oss << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(c);
                result.push_back(oss.str());
            }
            return result;
        }

        // HEX / DECIMAL → codepoints

        for (auto codepoints = utf8ToCodepoints(text); uint32_t cp : codepoints) {
            std::ostringstream oss;

            if (format == UnicodeFormat::HEX) {
                oss << "U+" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << cp;
            } else if (format == UnicodeFormat::DECIMAL) {
                oss << cp;
            }

            result.push_back(oss.str());
        }

        return result;
    }

    std::string StringMembers::reverseString(const std::string& text) {
        std::vector<std::string> chars;
        for (size_t i = 0; i < text.size();) {
            const unsigned char c = text[i];
            size_t charLen;

            if ((c & 0x80) == 0)
                charLen = 1; // 1-byte ASCII
            else if ((c & 0xE0) == 0xC0)
                charLen = 2; // 2-byte
            else if ((c & 0xF0) == 0xE0)
                charLen = 3; // 3-byte
            else
                charLen = 4; // 4-byte

            chars.push_back(text.substr(i, charLen));
            i += charLen;
        }

        // Reverse the vector
        std::ranges::reverse(chars);

        // Join back into a string
        std::string result;
        for (const auto& s : chars)
            result += s;

        return result;
    }

} // namespace yogi::utils::helpers