project(Test)
set(CMAKE_CXX_STANDARD 20)

add_executable(test-BaseTypesLib test-BaseTypesLib.cpp)
target_include_directories(test-BaseTypesLib PUBLIC ../src/BaseTypesLib)
add_test(NAME BaseTypesLib_Test COMMAND test-BaseTypesLib)
install(
  TARGETS test-BaseTypesLib
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(test-OR2L_Types test-OR2L_Types.cpp)
target_include_directories(test-OR2L_Types PUBLIC ../src/BaseTypesLib
                                                  ../src/OR2LaTeX/OR2L_Types)
target_link_libraries(test-OR2L_Types basetypeslib)
add_test(NAME OR2L_Types_test COMMAND test-OR2L_Types)
install(
  TARGETS test-OR2L_Types
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(test-ortools test-ortools.cpp)
target_include_directories(test-ortools PUBLIC ../src/BaseTypesLib
                                               ${ortools_INCLUDE_DIR})
target_link_libraries(test-ortools ${ortools_LIBRARY_DIR})
add_test(NAME ortools_test COMMAND test-ortools)
install(
  TARGETS test-ortools
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# add_executable(test-or2lbinding test-or2lbinding.cpp)
# target_include_directories(test-or2lbinding PUBLIC ../src/BaseTypesLib
# ../src/OR2LaTeX/OR2L_Types ${ortools_INCLUDE_DIR})
# target_link_libraries(test-or2lbinding BaseTypesLib OR2L_TYPES
# ${ortools_LIBRARY_DIR})
