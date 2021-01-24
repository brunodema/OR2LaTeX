cmake_minimum_required(VERSION 3.16)
project(OR2L)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(ortools MODULE)
message(STATUS "'ortools' library path set to: ${ortools_LIBRARIES}")
message(STATUS "'ortools' include directory set to: ${ortools_INCLUDES}")

add_subdirectory(src)
if((CMAKE_PROJECT_NAME STREQUAL OR2L OR OR2L_BUILD_TESTING) AND BUILD_TESTING)
  message(STATUS "building tests...")
  enable_testing()
  add_subdirectory(tests)
endif()
