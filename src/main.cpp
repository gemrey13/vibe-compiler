#include "InterpreterDriver/InterpreterDriver.hpp"
#include <iostream>

int main(int argc, const char* argv[]) {
    vibeCompiler::InterpreterDriver driver;

    if (argc > 2) {
        std::cout << "Usage: ./cook [filename.gz] or just ./cook for interpreter" << std::endl;
        return 64;
    }

    if (argc == 2) {
        return driver.runScript(argv[1]);
    }

    driver.runPrompt();

    return 0;
}