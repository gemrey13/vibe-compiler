#include "ErrorReporter/ErrorReporter.hpp"

#include <iostream>

namespace vibeCompiler {

    void ErrorReporter::clearErrors() {
        errorMessages.clear();
        status = VibeStatus::OK;
    }

    VibeStatus ErrorReporter::getStatus() const {
        return status;
    }

    void ErrorReporter::printError() const {
        for (const auto& message : errorMessages) {
            std::cerr << message << std::endl;
        }
    }

    void ErrorReporter::setError(int line, const std::string& message) {
        errorMessages.emplace_back("[Line " + std::to_string(line) + "] Aura check failed: " + message);
        status = VibeStatus::ERROR;
    }

} // namespace vibeCompiler::ErrorReporter