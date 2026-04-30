#include "InterpreterDriver/InterpreterDriver.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    vibeCompiler::InterpreterDriver driver;

    /*
    argc: This is the "argument count."
        argc = 1: You just ran ./cook (no file).
        argc = 2: You ran ./cook script.yow (one file).
        argc > 2: You tried to run ./cook script.yow extra_file.txt.
    */
    if (argc > 2) {
        std::cout << "Too many files! 💀" << std::endl;
        std::cout << "Usage: ./cook [filename.yow] or just ./cook to start cookin'" << std::endl;
        return 64;
    }

    if (argc == 2) {
        return driver.runScript(argv[1]);
    }

    driver.runPrompt();

    return 0;
}