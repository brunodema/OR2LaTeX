project(TestOR2L)
set(CMAKE_CXX_STANDARD 20)

add_executable(test-BaseTypesLib test-BaseTypesLib.cpp)
target_include_directories(test-BaseTypesLib PUBLIC ../src/BaseTypesLib)

add_executable(test-OR2L_Types test-OR2L_Types.cpp)
target_include_directories(test-OR2L_Types PUBLIC ../src/BaseTypesLib)
target_include_directories(test-OR2L_Types PUBLIC ../src/OR2LaTeX/OR2L_Types)
target_link_libraries(test-OR2L_Types BaseTypesLib)

add_executable(test-ortools test-ortools.cpp)
target_include_directories(test-ortools PUBLIC ../src/BaseTypesLib)
target_include_directories(test-ortools PUBLIC ${ortools_SOURCE_DIR})
target_link_libraries(test-ortools ortools::ortools)

add_executable(test-or2lbinding test-or2lbinding.cpp)
target_include_directories(test-or2lbinding PUBLIC ../src/BaseTypesLib)
target_include_directories(test-or2lbinding PUBLIC ../src/OR2LaTeX/OR2L_Types)
target_include_directories(test-or2lbinding PUBLIC ${ortools_SOURCE_DIR})
target_link_libraries(test-or2lbinding BaseTypesLib)
target_link_libraries(test-or2lbinding OR2L_TYPES)
target_link_libraries(test-or2lbinding ortools::ortools)




