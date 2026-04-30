#pragma once

#include "ErrorReporter/ErrorReporter.hpp"

#include <string>
#include <vector>

namespace vibeCompiler {

    class InterpreterDriver {
      public:
        InterpreterDriver();
        int runScript(const std::string& filename);
        void runPrompt();
        void runCode(const std::string& source);

      private:
        ErrorReporter errorReporter;
    };

} // namespace vibeCompiler