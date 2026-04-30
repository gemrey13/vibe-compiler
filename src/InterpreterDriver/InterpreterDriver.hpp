#pragma once

#include <string>
#include <vector>

namespace vibeCompiler {

    class InterpreterDriver {
      public:
        InterpreterDriver();
        int runScript(const std::string& filename);
        void runPrompt();

      private:
        void runCode(const std::string& source);
    };

} // namespace vibeCompiler