project(basetypeslib)

file(GLOB files *.cpp *.h)

add_library(basetypeslib STATIC ${files})
set_target_properties(
  basetypeslib PROPERTIES LINKER_LANGUAGE CXX) # needs this if there is no .cpp
                                               # in the source directory

install(
  TARGETS basetypeslib
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
