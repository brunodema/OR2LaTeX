project(TestOR2L)
set(CMAKE_CXX_STANDARD 20)

include_directories(../src/BaseTypesLib)
include_directories(../src/OR2LaTeX/OR2L_Types)

add_executable(test-BaseTypesLib test-BaseTypesLib.cpp)
add_executable(test-OR2L_Types test-OR2L_Types.cpp)


add_executable(test-ortools test-ortools.cpp)
target_include_directories(test-ortools PUBLIC ${ortools_SOURCE_DIR})
target_link_libraries(test-ortools ortools::ortools)




