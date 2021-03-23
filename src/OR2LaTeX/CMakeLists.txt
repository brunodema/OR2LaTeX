project(or2l_types)

file(GLOB_RECURSE files *.cpp *.h)

set(_target_include_directories ${CMAKE_CURRENT_SOURCE_DIR}
                                ${ortools_INCLUDE_DIR})
set(_target_link_libraries basetypeslib::basetypeslib ortools::ortools)

if(USE_GUROBI)
  list(APPEND _target_link_libraries gurobi::gurobi)
endif()

add_library(or2l_types STATIC ${files})
target_include_directories(or2l_types PUBLIC ${_target_include_directories})
target_link_libraries(or2l_types PUBLIC ${_target_link_libraries})

install(
  TARGETS or2l_types
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
