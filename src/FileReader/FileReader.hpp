#pragma once

#include <fstream>
#include <string>

namespace vibeCompiler {

    class FileReader {
      public:
        FileReader(const std::string& filename);
        ~FileReader();

        std::string readAll();

      private:
        std::string filename;
        std::ifstream fileStream;
    };

} // namespace vibeCompiler::FileReader
