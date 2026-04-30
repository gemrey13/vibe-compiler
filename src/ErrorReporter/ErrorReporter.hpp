#ifndef VIBECOMPILER_ERRORREPORTER_ERRORREPORTER_H
#define VIBECOMPILER_ERRORREPORTER_ERRORREPORTER_H
#pragma once

#include <string>
#include <vector>

namespace vibeCompiler::ErrorReporter {
    enum struct VibeStatus { OK, ERROR };

    class ErrorReporter {
      public:
        void clearErrors();
        VibeStatus getStatus();
        void printError();
        void setError(int line, const std::string& message);

      private:
        std::vector<std::string> errorMessages;
        VibeStatus status = VibeStatus::OK;
    };

} // namespace vibeCompiler::ErrorReporter

#endif
