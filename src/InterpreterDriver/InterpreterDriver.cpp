#include "InterpreterDriver/InterpreterDriver.hpp"
#include "FileReader/FileReader.hpp"
#include "Scanner/Scanner.hpp"

#include <iostream>

namespace vibeCompiler {

    InterpreterDriver::InterpreterDriver() {}

    int InterpreterDriver::runScript(const std::string& filename) {
        if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".yow") {
            std::cout << "L + ratio + wrong file type: " << filename << std::endl;
            std::cout << "Expected a .yow file, no cap." << std::endl;
            return 64;
        }
        vibeCompiler::FileReader fileReader(filename);

        std::string code = fileReader.readAll();
        if (code.empty()) {
            return 65;
        }

        runCode(code);
        return 0;
    }

    void InterpreterDriver::runPrompt() {
        std::string line;
        std::cout << R"(
                Greetings! I am the Interactive mode for the Vibe language
                    inspired by Bob Nystrom's Crafting Interpreters.
                        http://www.craftinginterpreters.com/
                            Developed by Code with Gem

Type "exit" or press CTRL-C to exit.
                        )"
                  << std::endl;
        while (true) {
            std::cout << "> " << std::flush;
            if (!std::getline(std::cin, line)) {
                std::cout << "\nBruh, not the ghosting... X_X" << std::endl;
                break; // Stop if the input stream is closed
            }
            if (line == "exit") {
                std::cout << "Valid. Catch you on the flip side!" << std::endl;
                break;
            }

            if (line.empty())
                continue;

            runCode(line);
            errorReporter.clearErrors();
        }
    }

    void InterpreterDriver::runCode(const std::string& source) {
        vibeCompiler::Scanner scanner(source, errorReporter);

        std::vector<vibeCompiler::Token> tokens = scanner.scanTokens();

        // Add a check to see if errors were found during scanning
        if (errorReporter.getStatus() == vibeCompiler::VibeStatus::ERROR) {
            errorReporter.printError();
            errorReporter.clearErrors(); // Important for the Interactive Prompt (REPL)
            return;
        }

        for (const auto& token : tokens) {
            std::cout << token.toString() << std::endl;
        }
    }
} // namespace vibeCompiler