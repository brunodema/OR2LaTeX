project(TestOR2L)
set(CMAKE_CXX_STANDARD 20)

include_directories(../src/BaseTypesLib)
include_directories(../src/OR2LaTeX/OR2L_Types)

add_executable(testBaseTypesLib testBaseTypesLib.cpp)
add_executable(testOR2L_Types testOR2L_Types.cpp)



