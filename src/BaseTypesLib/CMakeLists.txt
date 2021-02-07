project(basetypeslib)

file(GLOB files *.cpp *.h)

add_library(basetypeslib STATIC ${files})
target_include_directories(basetypeslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(basetypeslib INTERFACE boost::boost)

install(
  TARGETS basetypeslib
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
