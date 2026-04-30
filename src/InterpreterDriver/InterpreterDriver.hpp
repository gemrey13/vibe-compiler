#pragma once

#include "ErrorReporter/ErrorReporter.hpp"

#include <string>
#include <vector>


/**
 * @brief The vibeCompiler namespace contains all core components of the 
 * custom programming language "vibe."
 */
namespace vibeCompiler {

    class ErrorReporter;

    class InterpreterDriver {
      public:
        InterpreterDriver();
        int runScript(const std::string& filename);

        /**
         * @brief Launches the interactive vibe-compiler session.
         *
         * The REPL cycle:
         * 
         * 1. 📖 READ     : Intercepts raw input from the standard stream.
         * 
         * 2. 🧠 EVALUATE : Passes the lexemes to the interpreter for execution.
         * 
         * 3. 🔊 PRINT    : Dispatches the output (or the "mid" error) to the user.
         * 
         * 4. 🔄 LOOP     : Resets the state for the next line of code.
         */
        void runPrompt();
        void runCode(const std::string& source);

      private:
        vibeCompiler::ErrorReporter errorReporter;
    };

} // namespace vibeCompiler