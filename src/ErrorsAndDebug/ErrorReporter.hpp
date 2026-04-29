#ifndef VIBECOMPILER_ERRORSANDDEBUG_ERRORREPORTER_H
#define VIBECOMPILER_ERRORSANDDEBUG_ERRORREPORTER_H
#pragma once

#include <string>
#include <vector>

namespace vibeCompiler::ErrorsAndDebug {

    enum class LoxStatus { OK, ERROR };

    class ErrorReporter {
      public:
        void clearErrors();
        LoxStatus getStatus();
        void printToStdErr();
        void setError(int line, const std::string& message);

      private:
        std::vector<std::string> errorMessages;
        LoxStatus status = LoxStatus::OK;
    };

} // namespace vibeCompiler::ErrorsAndDebug

#endif