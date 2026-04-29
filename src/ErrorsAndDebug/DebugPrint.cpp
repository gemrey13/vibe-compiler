#include "ErrorsAndDebug/DebugPrint.hpp"

#include <iostream>
#include <string>

namespace vibeCompiler::ErrorsAndDebug {

    void debugPrint(const std::string& str) {
        std::cout << str << std::endl;
    }
 
} // namespace vibeCompiler::ErrorsAndDebug