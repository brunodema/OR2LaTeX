project(or2l_types)
set(CMAKE_CXX_STANDARD 20)

file(GLOB files *.cpp *.h)

add_library(or2l_types STATIC ${files})
target_include_directories(or2l_types PUBLIC ${basetypeslib_SOURCE_DIR}
                                             ${ortools_INCLUDE_DIR})
target_link_libraries(or2l_types basetypeslib ${ortools_LIBRARY_DIR})

install(
  TARGETS or2l_types
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
