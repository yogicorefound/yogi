//
// Created by Brayhan De Aza on 12/12/25.
//

#include "compiler.h"

#include <Grammar.h>
#include <Tokens.h>
#include <core/llvm/emitter/CodeEmitter.h>
#include <core/llvm/ir/IR.h>
#include <utils/errors/AntlrErrorListener.h>
#include <visitors/program/ProgramVisitor.h>
#include "antlr4-runtime.h"

#include <lld/Common/Driver.h>

#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <unistd.h>

namespace yogi::compiler {

    std::any Compiler::compile(std::string modulePath) {
        try {
            const std::ifstream file(modulePath);

            if (!file) {
                std::cerr << "Error: Could not open file " << modulePath << std::endl;
                std::exit(1);
            }

            std::stringstream buffer;
            buffer << file.rdbuf();

            // ---------------------------------------------
            // Feed file content into ANTLR
            // ---------------------------------------------
            antlr4::ANTLRInputStream input(buffer.str());

            // ---------------------------------------------
            // Feed ANTLR into Tokens
            // ---------------------------------------------
            Tokens lexer(&input);
            antlr4::CommonTokenStream tokens(&lexer);
            Grammar grammar(&tokens);

            // grammar.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());

            // ---------------------------------------------
            // Setup error listeners
            // ---------------------------------------------
            lexer.removeErrorListeners();
            grammar.removeErrorListeners();

            utils::errors::AntlrErrorListener errorListener(content);
            lexer.addErrorListener(&errorListener);

            grammar.addErrorListener(&errorListener);
            grammar.setErrorHandler(std::make_shared<utils::errors::SafeErrorStrategy>());


            // ---------------------------------------------
            // Feed Tokens into Grammar
            // ---------------------------------------------
            // auto *tree = grammar.program();
            antlr4::tree::ParseTree *tree = nullptr;
            try {
                tree = grammar.program();
            } catch (antlr4::NoViableAltException &e) {
                std::cerr << "Caught in program(): " << e.what() << std::endl;
                return nullptr;
            } catch (antlr4::ParseCancellationException &e) {
                std::cerr << "Caught ParseCancellation in program(): " << e.what() << std::endl;
                return nullptr;
            } catch (...) {
                std::cerr << "Caught unknown in program()" << std::endl;
                return nullptr;
            }


            if (errorListener.hasError) {
                std::cout << "errorListener: \n";
                return nullptr; // error already printed, exit cleanly
            }


            visitor::Visitor visitor(content, filePath, &grammar, false);

            // ---------------------------------------------
            // Feed Grammar into Visitor and generate AST
            // ---------------------------------------------
            auto ast = visitor.visit(tree);
            return ast;

        } catch (antlr4::ParseCancellationException &e) {
            std::cerr << "Parse error: " << e.what() << std::endl;

        } catch (antlr4::RecognitionException &e) {
            std::cerr << "RecognitionException: " << e.what() << std::endl;

        } catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        return nullptr;
    }

    void Compiler::getModuleContent(std::string fPath) {
        const std::ifstream file(fPath);

        if (!file) {
            std::cerr << "Error: Could not open file " << fPath << std::endl;
            std::exit(1);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        this->content = buffer.str();
    }

    void Compiler::getContent(const int argc, const char *argv[]) {
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

    visitor::nodes::ProgramNode Compiler::testAST(std::string &text, std::string &filePath) {
        // ---------------------------------------------
        // Feed file content into ANTLR
        // ---------------------------------------------
        antlr4::ANTLRInputStream input(text);

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

        utils::errors::AntlrErrorListener errorListener(text);
        lexer.addErrorListener(&errorListener);
        grammar.addErrorListener(&errorListener);

        // ---------------------------------------------
        // Feed Tokens into Grammar
        // ---------------------------------------------
        auto *tree = grammar.program();
        visitor::Visitor visitor(text, filePath, &grammar, false);

        // ---------------------------------------------
        // Feed Grammar into Visitor and generate AST
        // ---------------------------------------------
        auto ast = visitor.visit(tree);
        auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        return node;
    }


    std::any Compiler::getAST(bool justScan) {
        // ---------------------------------------------
        // Feed file content into ANTLR
        // ---------------------------------------------
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
        visitor::Visitor visitor(content, filePath, &grammar, justScan);

        // ---------------------------------------------
        // Feed Grammar into Visitor and generate AST
        // ---------------------------------------------
        auto ast = visitor.visit(tree);
        // auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        return ast;
    }


    std::any Compiler::scan(std::string fPath) {
        const std::ifstream file(fPath);
        if (!file) {
            std::cerr << "Error: Could not open file " << fPath << std::endl;
            std::exit(1);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();


        // ---------------------------------------------
        // Feed file content into ANTLR
        // ---------------------------------------------
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
        visitor::Visitor visitor(content, fPath, &grammar, true);

        // ---------------------------------------------
        // Feed Grammar into Visitor and generate AST
        // ---------------------------------------------
        auto ast = visitor.visit(tree);

        return ast;
    }


    void Compiler::printAST(const std::any &ast) {
        std::cout << "=== AST ===" << std::endl;
        utils::Helpers::printNode(ast, 1);
    }

    void Compiler::processLLVM(const std::any &ast) const {
        const auto node = std::any_cast<visitor::nodes::ProgramNode>(ast);

        core::ir::IR ir(fileName);
        llvm::Module *module = ir.generate(node);

        module->print(llvm::outs(), nullptr);

        namespace fs = std::filesystem;
        const fs::path buildDir = fs::current_path();

        fs::create_directories(buildDir);
        fs::path output = buildDir / "app";
        fs::path objFile = buildDir / "main.o";

        lowering::CodeEmitter::toObjectFile(module, objFile.string());


        // Verify the object file was written correctly
        {
            std::ifstream f(objFile.string(), std::ios::binary);
            uint8_t magic[4] = {};
            f.read(reinterpret_cast<char *>(magic), 4);
        }

        // Get SDK path
        FILE *pipe = popen("xcrun --show-sdk-path 2>/dev/null", "r");
        std::string sdkPath;
        if (pipe) {
            char buf[512];
            if (fgets(buf, sizeof(buf), pipe)) {
                sdkPath = buf;
                if (!sdkPath.empty() && sdkPath.back() == '\n')
                    sdkPath.pop_back();
            }
            pclose(pipe);
        }
        if (sdkPath.empty())
            sdkPath = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk";

        std::string lSystem = sdkPath + "/usr/lib/libSystem.tbd";
        std::string objStr = objFile.string();
        std::string outputStr = output.string();
        std::string runtime = utils::Helpers::getBuildDirectory() + "/runtime/libyogi_runtime.a";

        // ld64.lld is the Mach-O linker — NOT ld.lld (which is ELF)
        std::vector<char *> args = {
            (char *) "ld64.lld",
            (char *) "-arch",
            (char *) "arm64",
            (char *) "-platform_version",
            (char *) "macos",
            (char *) "26.0.0",
            (char *) "26.0.0",
            (char *) "-syslibroot",
            (char *) sdkPath.c_str(),
            (char *) lSystem.c_str(), // link libSystem directly via .tbd
            (char *) objStr.c_str(),
            (char *) runtime.c_str(),
            (char *) "-o",
            (char *) outputStr.c_str(),
            nullptr
        };

        pid_t pid = fork();
        if (pid == 0) {
            // ld64.lld lives next to ld.lld in the LLVM bin dir
            execv("/opt/homebrew/opt/llvm@16/bin/ld.lld", args.data());
            perror("execv ld64.lld failed");
            exit(1);
        }

        int status;
        waitpid(pid, &status, 0);
    }

} // namespace yogi