cmake_minimum_required(VERSION 3.16)
project(OR2L)

option(BUILD_TESTING
       "Determines if the standard tests of the library will be built or not."
       ON)
option(
  USE_GUROBI
  "Determines if the 'Gurobi' libraries will be used during compilation/linking."
  OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(basetypeslib MODULE REQUIRED)
find_package(gtest MODULE REQUIRED)
#find_package(boost MODULE REQUIRED)
find_package(ortools MODULE REQUIRED)
if(USE_GUROBI)
  find_package(gurobi MODULE REQUIRED)
endif()

add_subdirectory(src)
if((CMAKE_PROJECT_NAME STREQUAL OR2L OR OR2L_BUILD_TESTING) AND BUILD_TESTING)
  message(STATUS "building tests...")
  enable_testing()
  add_subdirectory(tests)
endif()
