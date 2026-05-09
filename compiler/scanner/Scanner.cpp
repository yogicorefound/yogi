//
// Created by Brayhan De Aza on 5/8/26.
//

#include "Scanner.h"
#include "Tokens.h"

namespace yogi::compiler::scanner {
    visitor::nodes::ModulesPathsNode Scanner::scan() {
        antlr4::ANTLRInputStream input(content);

        // ---------------------------------------------
        // Feed ANTLR into Tokens
        // ---------------------------------------------
        Tokens lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        Grammar grammar(&tokens);

        // ---------------------------------------------
        // Setup error listeners
        // ---------------------------------------------
        lexer.removeErrorListeners();
        grammar.removeErrorListeners();

        utils::errors::AntlrErrorListener errorListener(content);
        lexer.addErrorListener(&errorListener);
        grammar.addErrorListener(&errorListener);

        // ---------------------------------------------
        // Feed Tokens into Grammar
        // ---------------------------------------------
        auto *tree = grammar.program();
        visitor::Visitor visitor(content, filePath, &grammar, true);

        auto ast = visitor.visit(tree);
        auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        return modulesPaths;
    }

    void Scanner::print(const std::optional<uint8_t> indent = 2) const {
        using json = nlohmann::json;

        std::function<json(const visitor::nodes::ModulesPathsNode &)> serializeModule;

        serializeModule = [&](const visitor::nodes::ModulesPathsNode &module) -> json {
            json result = {
                {"path", module.path},
                {"modules", json::array()}
            };

            if (!module.modules.empty()) {
                for (const auto &child: module.modules) {
                    result["modules"].push_back(serializeModule(child));
                }
            }

            return result;
        };

        const json output = serializeModule(modulesPaths);
        std::cout << output.dump(indent.value_or(2)) << std::endl;
    }

    void Scanner::getContent(const int argc, const char *argv[]) {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
            std::exit(1);
        }

        const std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            std::exit(1);
        }


        filePath = argv[1];
        fileName = filePath.substr(filePath.find_last_of('/') + 1);

        std::stringstream buffer;
        buffer << file.rdbuf();
        this->content = buffer.str();
    }

}