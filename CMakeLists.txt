cmake_minimum_required(VERSION 3.16)
project(OR2L)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)



include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
set(BUILD_DEPS ON) # this is a 'ortools' option definition
FetchContent_Declare(
  ortools
  URL  https://github.com/google/or-tools/releases/download/v8.1/or-tools_ubuntu-20.04_v8.1.8487.tar.gz
)
# After the following call, the CMake targets defined by or-tools
# will be defined and available to the rest of the build
FetchContent_MakeAvailable(ortools)

# this is sort of an ugly version of a 'find_package'
find_library(ortools_LIBRARY_DIR NAMES libortools.so HINTS ${ortools_SOURCE_DIR}/lib)
set(ortools_INCLUDE_DIR ${ortools_SOURCE_DIR}/include)
message(STATUS "'ortools' library directory set to: ${ortools_LIBRARY_DIR}")
message(STATUS "'ortools' include directory set to: ${ortools_INCLUDE_DIR}")

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_subdirectory(src)
if((CMAKE_PROJECT_NAME STREQUAL OR2L OR OR2L_BUILD_TESTING) AND BUILD_TESTING)
    message(STATUS "building tests...")
    add_subdirectory(tests)
endif()