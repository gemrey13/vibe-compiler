#pragma once

#include <fstream>
#include <string>

namespace vibeCompiler {

    /**
     * @class FileReader
     * @brief Responsible for loading raw source code from the file system.
     *
     * Why: Before we can scan tokens or evaluate logic, we need to pull the
     * "vibes" (source code) into a format the compiler can actually read.
     * This class abstracts the file-handling logic to keep the rest of the
     * compiler clean and focused on interpretation.
     */
    class FileReader {
      public:
        /**
         * @brief Initializes the reader and attempts to open the target file.
         * @param filename The path to the .yow file we want to cook.
         */
        FileReader(const std::string& filename);

        /**
         * @brief Standard destructor ensuring the file stream is safely closed.
         */
        ~FileReader();

        /**
         * @brief Reads the entire contents of the file into a single string.
         *
         * This method consumes the whole file from start to EOF. If the file
         * can't be read or is ghosting us (missing), it returns an empty string.
         *
         * @return std::string The raw source code ready for the Scanner.
         */
        std::string readAll();

      private:
        std::string filename;        // The path to our source script.
        std::ifstream fileStream;    // The actual input stream for disk access.
    };

} // namespace vibeCompiler
