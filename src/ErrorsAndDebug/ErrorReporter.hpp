#ifndef VIBECOMPILER_ERRORSANDDEBUG_ERRORREPORTER_H
#define VIBECOMPILER_ERRORSANDDEBUG_ERRORREPORTER_H
#pragma once

#include <string>
#include <vector>

namespace vibeCompiler::ErrorsAndDebug {

    enum class VibeStatus { OK, ERROR };

    class ErrorReporter {
      public:
        void clearErrors();
        VibeStatus getStatus() const;
        void printToStdErr();
        void setError(int line, const std::string& message);

      private:
        std::vector<std::string> errorMessages;
        VibeStatus status = VibeStatus::OK;
    };

} // namespace vibeCompiler::ErrorsAndDebug

#endif