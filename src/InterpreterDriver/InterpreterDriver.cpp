#include "InterpreterDriver.hpp"
#include "FileReader/FileReader.hpp"

#include <iostream>

namespace vibeCompiler {

    int InterpreterDriver::runScript(const std::string& filename) {
        vibeCompiler::FileReader::FileReader fileReader(filename);

        std::string code = fileReader.readAll();
        if (code.empty()) {
            return 65;
        }

        // return runCode(code);
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
            // runCode(line)
        }
    }

    void runCode(const std::string& source) {
        // Scanner scanner = new Scanner(source);
        // List<Token> tokens =scanner.scanTokens();


        // loop for (token in tokens) {
        //     print token
        // }
    }
} // namespace vibeCompiler