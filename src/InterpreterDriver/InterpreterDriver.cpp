#include "InterpreterDriver.hpp"
#include "ErrorsAndDebug/ErrorReporter.hpp"
#include "FileReader/FileReader.hpp"

#include <iostream>

namespace vibeCompiler {

    int InterpreterDriver::runScript(const std::string& filename) {
        FileReader fileReader(filename, reporter);

        std::string code = fileReader.readAll();

        if (code.empty() && reporter.getStatus() == ErrorsAndDebug::VibeStatus::ERROR) {
            return 65; // Exit code for "Input data error"
        }

        return runCode(code);
    }
} // namespace vibeCompiler