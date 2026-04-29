#include <iostream>

int main(int argc, const char* argv[]) {

    if (argc > 2) {
        std::cout << "Usage: ./cook <filename.gz> or just ./cook for interpreter" << std::endl;
        std::exit(64);
    }

    if (argc == 2) {
        // return runScript(argv[1]);
    }

    // runPrompt();

    return 0;
}