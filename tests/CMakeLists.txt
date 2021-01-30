project(Test)

set(EXECUTABLES_TO_BE_INSTALLED test-BaseTypesLib test-OR2L_Types test-ortools test-or2lbinding)

# test-BaseTypesLib
add_executable(test-BaseTypesLib test-BaseTypesLib.cpp)
# target_include_directories(test-BaseTypesLib PUBLIC
# ${basetypeslib_SOURCE_DIR})
target_link_libraries(test-BaseTypesLib basetypeslib)
add_test(NAME basetypeslib COMMAND test-BaseTypesLib)

# test-OR2L_Types
add_executable(test-OR2L_Types test-OR2L_Types.cpp)
# target_include_directories(test-OR2L_Types PUBLIC ${basetypeslib_SOURCE_DIR}
# ${or2l_types_SOURCE_DIR})
target_link_libraries(test-OR2L_Types or2l_types)
add_test(NAME or2l_types COMMAND test-OR2L_Types)

# test-ortools
add_executable(test-ortools test-ortools.cpp)
# target_include_directories(test-ortools PUBLIC ${basetypeslib_SOURCE_DIR}
# ${ortools_INCLUDES})
target_link_libraries(test-ortools basetypeslib ortools::ortools)
add_test(NAME ortools COMMAND test-ortools)

# test-or2lbinding
add_executable(test-or2lbinding test-or2lbinding.cpp)
# target_include_directories(test-or2lbinding PUBLIC ${basetypeslib_SOURCE_DIR}
# ${or2l_types_SOURCE_DIR}
# ${ortools_INCLUDES})
target_link_libraries(test-or2lbinding or2l_types)
add_test(NAME or2lbinding COMMAND test-or2lbinding)

# ----
# test-gurobi
if(USE_GUROBI)
add_executable(test-gurobi test-gurobi.cpp)
target_link_libraries(test-gurobi basetypeslib gurobi::gurobi)
add_test(NAME gurobi COMMAND test-gurobi)
list(APPEND EXECUTABLES_TO_BE_INSTALLED test-gurobi)
endif()

install(
  TARGETS ${EXECUTABLES_TO_BE_INSTALLED}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})