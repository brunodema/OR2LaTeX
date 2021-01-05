cmake_minimum_required(VERSION 3.16)
project(DEMALIB)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
  or-tools
  GIT_REPOSITORY https://github.com/google/or-tools.git
  GIT_TAG        master
)

# After the following call, the CMake targets defined by or-tools
# will be defined and available to the rest of the build
set(or-tools_BUILD_DEPS ON)
FetchContent_MakeAvailable(or-tools)

add_subdirectory(src)
add_subdirectory(tests)