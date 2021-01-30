# OR2LaTeX
# Standard 'FindPackage.cmake' procedure:
# (1) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)

# Define global vairables for the dependency (URLs, paths, names, etc)
# Search paths:
set(_SEARCH_PATHS "$ENV{PROGRAMFILES}/gurobi911/win64" "usr/local")
# Include path suffixes:
set(_INCLUDE_PATH_SUFFIXES "include")
# Library path suffixes:
set(_LIBRARY_PATH_SUFFIXES "lib")
# Target file for 'FIND_PATH':
set(_FILE_NAMES "gurobi_c++.h")
# Target file for 'FIND_LIBRARY':
set(_LIBRARY_NAMES "gurobi91.lib")
# Library file for 'Debug' mode (MTd)
set(_LIBRARY_DEBUG_NAMES "gurobi_c++mdd2019.lib")
# Library file for 'Release' mode (MT)
set(_LIBRARY_RELEASE_NAMES "gurobi_c++md2019.lib")

# Standard strategy definitions for the package:

include(FindPackageHandleStandardArgs)
set(gurobi_FOUND 0)

# (1) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
  message(STATUS "Searching for 'Gurobi' package using manual approach...")
  list(APPEND gurobi_SEARCH_PATHS ${_SEARCH_PATHS})

  find_path(
    gurobi_INCLUDE_DIR
    NAMES ${_FILE_NAMES}
    PATH_SUFFIXES ${_INCLUDE_PATH_SUFFIXES}
    HINTS ${gurobi_SEARCH_PATHS})

  find_path(
    gurobi_LIBRARY_DIR
    NAMES ${_LIBRARY_NAMES}
    PATH_SUFFIXES ${_LIBRARY_PATH_SUFFIXES}
    PATHS ${gurobi_SEARCH_PATHS})

  find_library(
    gurobi_DEBUG_LIBRARY
    NAMES ${_LIBRARY_DEBUG_NAMES}
    PATH_SUFFIXES ${_LIBRARY_PATH_SUFFIXES}
    PATHS ${gurobi_SEARCH_PATHS})

  find_library(
    gurobi_RELEASE_LIBRARY
    NAMES ${_LIBRARY_RELEASE_NAMES}
    PATH_SUFFIXES ${_LIBRARY_PATH_SUFFIXES}
    PATHS ${gurobi_SEARCH_PATHS})

  find_library(
    gurobi_LIBRARY
    NAMES ${_LIBRARY_NAMES}
    PATH_SUFFIXES ${_LIBRARY_PATH_SUFFIXES}
    PATHS ${gurobi_SEARCH_PATHS})

  if(gurobi_INCLUDE_DIR AND gurobi_LIBRARY_DIR)
    message(STATUS "'gurobi' found via manual search. Setting variables...")
    set(gurobi_INCLUDES ${gurobi_INCLUDE_DIR})
    set(gurobi_LIBRARIES ${gurobi_LIBRARY_DIR})

    add_library(gurobi INTERFACE IMPORTED GLOBAL)
    target_link_libraries(gurobi INTERFACE ${gurobi_LIBRARY} $<$<CONFIG:Debug>:${gurobi_DEBUG_LIBRARY}> $<$<CONFIG:Release>:${gurobi_RELEASE_LIBRARY}>)
    target_include_directories(gurobi INTERFACE ${gurobi_INCLUDE_DIR})
    target_compile_definitions(gurobi INTERFACE GUROBI)
    add_library(gurobi::gurobi ALIAS gurobi)
  else()
    message(STATUS "'gurobi' package NOT found using manual approach.")
  endif()

message(STATUS "'gurobi' library path set to: ${gurobi_LIBRARIES}")
message(STATUS "'gurobi' include directory set to: ${gurobi_INCLUDES}")
find_package_handle_standard_args(gurobi DEFAULT_MSG gurobi_INCLUDE_DIR
                                  gurobi_LIBRARY_DIR)
