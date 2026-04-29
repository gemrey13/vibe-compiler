#ifndef VIBECOMPILER_FILEREADER_FILEREADER_H
#define VIBECOMPILER_FILEREADER_FILEREADER_H
#pragma once

#include <fstream>
#include <string>

namespace vibeCompiler {

    class FileReader {
      public:
        explicit FileReader(const std::string& filename);
        ~FileReader();

        std::string readAll();

      private:
        std::string filename;
        std::ifstream fileStream;
    };

} // namespace vibeCompiler

#endif