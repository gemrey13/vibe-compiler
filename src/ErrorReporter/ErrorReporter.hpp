#pragma once

#include <string>
#include <vector>

namespace vibeCompiler {
    enum struct VibeStatus { OK, ERROR };

    class ErrorReporter {
      public:
        void clearErrors();
        VibeStatus getStatus() const;
        void printError() const;
        void setError(int line, const std::string& message);

      private:
        std::vector<std::string> errorMessages;
        VibeStatus status = VibeStatus::OK;
    };

} // namespace vibeCompiler::ErrorReporter
