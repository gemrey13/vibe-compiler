#include "ErrorReporter/ErrorReporter.hpp"

#include <iostream>

namespace vibeCompiler::ErrorReporter {

    void ErrorReporter::clearErrors() {
        errorMessages.clear();
        status = VibeStatus::OK;
    }

    VibeStatus ErrorReporter::getStatus() {
        return status;
    }

    void ErrorReporter::printError() {
        for (auto& message : errorMessages) {
            std::cerr << message << std::endl;
        }
    }

    void ErrorReporter::setError(int line, const std::string& message) {
        errorMessages.emplace_back("[Line " + std::to_string(line) + "] Error: " + message);
        status = VibeStatus::ERROR;
    }

} // namespace vibeCompiler::ErrorReporter