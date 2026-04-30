#include "InterpreterDriver.hpp"
#include "FileReader/FileReader.hpp"
#include "Scanner/Scanner.hpp"

#include <iostream>

namespace vibeCompiler {

    int InterpreterDriver::runScript(const std::string& filename) {
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
                        # Greetings! I am the Interactive mode for the Vibe language
                        # inspired by Bob Nystrom's Crafting Interpreters.
                        # http://www.craftinginterpreters.com/
                        # Developed by Code with Gem
                        # Type "exit" or press CTRL-D to exit.
                        )"
                  << std::endl;
        while (true) {
            std::cout << "> ";
            if (!std::getline(std::cin, line)) {
                break; // Stop if the input stream is closed
            }
            if (line == "exit")
                break;
            runCode(line);
        }
    }

    void runCode(const std::string& source) {
        vibeCompiler::Scanner scanner(source);

        std::vector<vibeCompiler::Token> tokens = scanner.scanTokens();

        for (const auto& token : tokens) {
            std::cout << token.toString() << std::endl;
        }
    }
} // namespace vibeCompiler