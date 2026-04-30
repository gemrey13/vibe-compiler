#pragma once

#include <string>
#include <vector>

namespace vibeCompiler {

    /**
     * @enum VibeStatus
     * @brief Represents the global state of the compiler execution.
     */
    enum struct VibeStatus { OK, ERROR };

    /**
     * @class ErrorReporter
     * @brief The central hub for tracking and broadcasting syntax and runtime failures.
     *
     * Why: Compilers need a way to stop execution when they hit invalid code
     * without crashing the entire program. This class gathers all "L's" in one
     * place so they can be printed in a batch.
     */
    class ErrorReporter {
      public:
        /**
         * @brief Resets the reporter to its initial "OK" state and clears messages.
         */
        void clearErrors();

        /**
         * @brief Checks the current status of the compiler.
         * @return VibeStatus::ERROR if any errors were reported, otherwise OK.
         */
        VibeStatus getStatus() const;

        /**
         * @brief Flushes all collected error messages to the standard output.
         */
        void printError() const;

        /**
         * @brief Registers a new error and flips the status to ERROR.
         *
         * @param line The line number where the issue was detected.
         * @param message A descriptive string explaining why the code failed the vibe check.
         */
        void setError(int line, const std::string& message);

      private:
        std::vector<std::string> errorMessages; // Stores the log of failures.
        VibeStatus status = VibeStatus::OK;     // The internal flag for execution health.
    };

} // namespace vibeCompiler
