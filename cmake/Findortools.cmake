# OR2LaTeX
# Standard 'FindPackage.cmake' procedure:
# (1) Search for 'Config' file (user must provide search paths)
# (2) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
# (3) Fecth it online via 'fetchContent'

# Define global vairables for the dependency (URLs, paths, names, etc)
# Search paths:
set(_SEARCH_PATHS "$ENV{PROGRAMFILES}" "usr/local")
message(${_SEARCH_PATHS})
# Include path suffixes:
set(_INCLUDE_PATH_SUFFIXES "ortools/include" "include")
# Library path suffixes:
set(_LIBRARY_PATH_SUFFIXES "ortools/lib" "lib" "lib64")
# Target file for 'FIND_PATH':
set(_FILE_NAMES "ortools/linear_solver/glop_utils.h")
# Target file for 'FIND_LIBRARY':
set(_LIBRARY_NAMES "ortools.lib" "libortools.so")
# Set target URLs for manual fetch:
set(Windows_ORTOOLS_URL
    "https://github.com/google/or-tools/releases/download/v8.1/or-tools_VisualStudio2019-64bit_v8.1.8487.zip"
)
set(MSYS_ORTOOLS_URL
    "https://github.com/google/or-tools/releases/download/v8.1/or-tools_VisualStudio2019-64bit_v8.1.8487.zip"
)
set(Linux_ORTOOLS_URL
    "https://github.com/google/or-tools/releases/download/v8.1/or-tools_ubuntu-20.04_v8.1.8487.tar.gz"
)

# Standard strategy definitions for the package:
option(
  ortools_FIND_BY_CONFIG
  "Sets if the package can search for '<package-name>Config.cmake' files or not."
  ON)
option(ortools_FIND_BY_PACKAGE
       "Sets if the package can manually search for the dependency or not." ON)
option(
  ortools_FIND_BY_FETCH
  "Sets if the package can be retrieved from an external repository or not." ON)

include(FindPackageHandleStandardArgs)
set(ortools_FOUND 0)

# (1) Search for 'Config' file (user must provide search paths)
if(ortools_FIND_BY_CONFIG)
  message(STATUS "Searching for 'ortools' package using 'CONFIG' approach...")
  find_package(ortools CONFIG)
  if(ortools_FOUND)
    get_target_property(ortools_INCLUDE_DIR ortools::ortools
                        INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(ortools_LIBRARY_DIR ortools::ortools
                        INTERFACE_LINK_LIBRARIES)
    set(ortools_INCLUDES ${ortools_INCLUDE_DIR})
    set(ortools_LIBRARIES ${ortools_LIBRARY_DIR})
    message(
      STATUS
        "'ortools' package found using 'CONFIG' approach. Exiting 'Findortools.cmake'..."
    )
  else()
    message(STATUS "'ortools' package NOT found using 'CONFIG' approach.")
  endif()
endif()

# (2) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
if(ortools_FIND_BY_PACKAGE AND ortools_FOUND EQUAL 0)
  message(STATUS "Searching for 'ortools' package using manual approach...")
  list(APPEND ortools_SEARCH_PATHS ${_SEARCH_PATHS})

  find_path(
    ortools_INCLUDE_DIR ${_FILE_NAMES}
    PATH_SUFFIXES ${_INCLUDE_PATH_SUFFIXES}
    HINTS ${ortools_SEARCH_PATHS})

  find_library(
    ortools_LIBRARY_DIR
    NAMES ${_LIBRARY_NAMES}
    PATH_SUFFIXES ${_LIBRARY_PATH_SUFFIXES}
    PATHS ${ortools_SEARCH_PATHS})

  if(ortools_INCLUDE_DIR AND ortools_LIBRARY_DIR)
    message(STATUS "'ortools' found via manual search. Setting variables...")
    set(ortools_INCLUDES ${ortools_INCLUDE_DIR})
    set(ortools_LIBRARIES ${ortools_LIBRARY_DIR})

    add_library(ortools STATIC IMPORTED GLOBAL)
    target_include_directories(ortools INTERFACE ${ortools_INCLUDE_DIR})
    set_target_properties(ortools PROPERTIES IMPORTED_LOCATION
                                             ${ortools_LIBRARY_DIR})
    add_library(ortools::ortools ALIAS ortools)
  else()
    message(STATUS "'ortools' package NOT found using manual approach.")
  endif()
endif()

# (3) Fetch it online via 'fetchContent'
if(ortools_FIND_BY_FETCH AND ortools_FOUND EQUAL 0)
  message(
    STATUS
      "Searching for 'ortools' package by retrieving it from a repository...")
  message(
    STATUS
      "IMPORTANT: currently, the online repositories contain only 'Release' versions of the library. Be aware of this before proceeding."
  )
  message(
    STATUS
      "The detected OS is: ${CMAKE_SYSTEM_NAME}. The associated URL will be: ${${CMAKE_SYSTEM_NAME}_ORTOOLS_URL}."
  )

  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)
  FetchContent_Declare(ortools URL ${${CMAKE_SYSTEM_NAME}_ORTOOLS_URL})
  FetchContent_MakeAvailable(ortools)

  # this is sort of an ugly version of a 'find_package'
  find_library(
    ortools_LIBRARY_DIR REQUIRED
    NAMES ${_LIBRARY_NAMES}
    PATHS ${ortools_SOURCE_DIR}/lib
    NO_DEFAULT_PATH)

  set(ortools_LIBRARIES ${ortools_LIBRARY_DIR})
  set(ortools_INCLUDE_DIR ${ortools_SOURCE_DIR}/include)
  set(ortools_INCLUDES ${ortools_SOURCE_DIR}/include)

  add_library(ortools STATIC IMPORTED GLOBAL)
  target_include_directories(ortools INTERFACE ${ortools_INCLUDE_DIR})
  set_target_properties(ortools PROPERTIES IMPORTED_LOCATION
                                           ${ortools_LIBRARY_DIR})

  add_library(ortools::ortools ALIAS ortools)
endif()

message(STATUS "'ortools' library path set to: ${ortools_LIBRARIES}")
message(STATUS "'ortools' include directory set to: ${ortools_INCLUDES}")
find_package_handle_standard_args(ortools DEFAULT_MSG ortools_INCLUDE_DIR
                                  ortools_LIBRARY_DIR)
