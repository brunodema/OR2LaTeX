project(OR2L_TYPES)
set(CMAKE_CXX_STANDARD 20)

include_directories(../../BaseTypesLib)

file(GLOB files
*.cpp
*.h
)

add_library(OR2L_TYPES STATIC ${files})

install(TARGETS OR2L_TYPES
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
)