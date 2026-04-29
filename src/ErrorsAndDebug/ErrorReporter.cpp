#include "ErrorsAndDebug/ErrorReporter.hpp"

#include <iostream>

namespace vibeCompiler::ErrorsAndDebug {

    void ErrorReporter::clearErrors() {
        errorMessages.clear();
        status = VibeStatus::OK;
    }

    VibeStatus ErrorReporter::getStatus() const {
        return status;
    }

    void ErrorReporter::setError(int line, const std::string& message) {
        status = VibeStatus::ERROR;
        // Using std::format style (Senior preference)
        errorMessages.push_back("[Line " + std::to_string(line) + "] Error: " + message);
    }

    void ErrorReporter::printToStdErr() {
        for (const auto& msg : errorMessages) {
            // Using C++23 std::println for cleaner output
            std::cerr << msg << std::endl;
        }
    }

} // namespace vibeCompiler::ErrorsAndDebug