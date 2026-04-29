cmake_minimum_required(VERSION 3.29.5)

# 1. Project Setup
project(VibeCompiler 
    VERSION 1.0.0 
    DESCRIPTION "A modern C++23 compiler for the Vibe language"
    LANGUAGES CXX
)

# 2. Modern C++23 Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 3. Compiler Warnings (The "Strict" Vibe)
# This treats warnings as errors to keep your code clean
if(MSVC)
    add_compile_options(/W4 /WX /wd4100) # Level 4, Errors, Ignore unused param warning
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wshadow -Wconversion)
endif()

# 4. Source Discovery
# This finds all .cpp files in src and its subfolders automatically
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.hpp"
)

# 5. Build Executable
add_executable(cook ${SOURCES})

# 6. Include Directories
# Use PRIVATE to keep the 'src' path internal to this target
target_include_directories(cook PRIVATE src)

# 7. Output Directory (Optional)
# Puts your 'cook' executable in a 'bin' folder inside build
set_target_properties(cook PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 8. Print Status
message(STATUS "VibeCompiler: C++23 build configured for ${CMAKE_SYSTEM_NAME}")