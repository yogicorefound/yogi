//
// Created by Brayhan De Aza on 5/8/26.
//

#include "Scanner.h"
#include "Tokens.h"

namespace yogi::compiler::scanner {
    visitor::nodes::ModulesPathsNode Scanner::scan() const {
        std::string content = setContentFromFilePath(utils::Helpers::pathResolver(utils::Helpers::getBuildDirectory(), filePath));
        antlr4::ANTLRInputStream input(setContentFromFilePath(content));

        // currentDirectory = std::move(utils::Helpers::pathResolver(filePath, "./").parent_path());

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

        std::string fileUrl = filePath;
        visitor::Visitor visitor(content, fileUrl, &grammar, true);

        auto ast = visitor.visit(tree);
        auto node = std::any_cast<visitor::nodes::ModulesPathsNode>(ast);

        node.print();

        return node;
    }

    void Scanner::print(const std::optional<uint8_t> indent) const {
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


    std::string Scanner::setContentFromFilePath(const std::string &fileUrl) const {
        // std::cout << "setContentFromDirectoryPath: " << utils::Helpers::pathResolver(currentDirectory, fileUrl) << std::endl;
        // // std::cout << "setContentFromFilePath: " << fileUrl << std::endl;
        const std::ifstream file(fileUrl);
        if (!file) {
            std::cerr << "Error: Could not open file " << fileUrl << std::endl;
            std::exit(1);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

}