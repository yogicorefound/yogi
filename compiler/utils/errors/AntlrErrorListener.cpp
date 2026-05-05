//
// Created by Brayhan De Aza on 11/30/25.
//

#include "AntlrErrorListener.h"

namespace yogi::utils::errors {
    AntlrErrorListener::AntlrErrorListener(const std::string& source) {
        // Split content into lines
        std::string line;
        for (const char c : source) {
            if (c == '\n') {
                lines.push_back(line);
                line.clear();
            } else {
                line += c;
            }
        }
        // Push last line
        if (!line.empty())
            lines.push_back(line);
    }

    void AntlrErrorListener::syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, const size_t line, const size_t charPos, const std::string& msg, std::exception_ptr) {
        std::cerr << "\n\033[1;31mSyntaxError: at line " << line << ", columns " << charPos  << "\n\033[0m";

        if (line > 0 && line <= lines.size()) {
            const std::string l = lines[line - 1];
            std::cerr << "\033[37m" << l << "\033[0m\n";

            std::string arrow(charPos, ' ');
            arrow += "^";
            std::cerr << "\033[37m" << arrow << "\n";
        }

        std::exit(1);
    }
} // namespace yogi::utils::errors