#ifndef VIBECOMPILER_INTERPRETERDRIVER_INTERPRETERDRIVER_H
#define VIBECOMPILER_INTERPRETERDRIVER_INTERPRETERDRIVER_H
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
        void interpret(const std::string& source);
    };

} // namespace vibeCompiler

#endif