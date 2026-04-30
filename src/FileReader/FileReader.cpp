#include "FileReader/FileReader.hpp"

#include <iostream>
#include <iterator>

namespace vibeCompiler {

    FileReader::FileReader(const std::string& p_filename) : filename(p_filename) {
        fileStream.open(filename);
        if (!fileStream.is_open()) {
            std::cout << "Could not open source file: " << filename << std::endl;
        }
    }

    std::string FileReader::readAll() {
        if (!fileStream.is_open())
            return "";

        fileStream.clear();
        fileStream.seekg(0, std::ios::end); // Move "cursor" to the very end
        std::streamsize size =
            fileStream.tellg(); // Ask: "What position are you at?" for this instance in the last.

        if (size <= 0)
            return "";

        std::string buffer;
        buffer.resize(static_cast<size_t>(size));

        fileStream.seekg(0, std::ios::beg);   // Move "cursor" back to the start
        fileStream.read(buffer.data(), size); // Copy everything into our bucket

        return buffer;
    }

    /*
     * A ~ (tilde) before a function name means it is a Destructor. This runs automatically when the
     * FileReader object is destroyed. It tells the operating system: "I'm done with this file, you
     * can let other programs use it now."
     */
    FileReader::~FileReader() {
        fileStream.close();
    }

} // namespace vibeCompiler::FileReader
