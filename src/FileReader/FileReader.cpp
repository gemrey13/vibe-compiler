#include "FileReader.hpp"
#include "ErrorsAndDebug/ErrorReporter.hpp"

#include <iterator>
// #include "LoxError.h"

namespace vibeCompiler {

    FileReader::FileReader(const std::string& filename, ErrorsAndDebug::ErrorReporter& reporter)
        : filename(filename) {
        fileStream.open(filename);
        if (!fileStream.is_open()) {
            reporter.setError(0, "Could not open source file: '" + filename + "'");
        }
    }

    std::string FileReader::readAll() {
        if (!fileStream.is_open())
            return "";

        fileStream.seekg(0, std::ios::end);
        size_t size = fileStream.tellg();

        std::string buffer(size, ' ');

        // Seek back to start and read
        fileStream.seekg(0, std::ios::beg);
        fileStream.read(&buffer[0], size);

        return buffer;
    }

    FileReader::~FileReader() {
        fileStream.close();
    }

} // namespace vibeCompiler
