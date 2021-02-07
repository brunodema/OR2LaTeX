# OR2LaTeX Standard 'FindPackage.cmake' procedure: (1) Search manually for the
# dependency (set 'INCLUDES'/'LIBRARIES' variables)

# Define global variables for the dependency (URLs, paths, names, etc) Search
# paths:
set(_SEARCH_PATHS "$ENV{PROGRAMFILES}/boost/" "C:/boost/" "usr/local")
# Include path suffixes:
set(_INCLUDE_PATH_SUFFIXES "boost")
# Library path suffixes:
set(_FILE_NAMES "align.hpp")

# Standard strategy definitions for the package:

include(FindPackageHandleStandardArgs)
set(boost_FOUND 0)

# (1) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
message(STATUS "Searching for 'boost' package using manual approach...")
list(APPEND boost_SEARCH_PATHS ${_SEARCH_PATHS})

find_path(
  boost_INCLUDE_DIR
  NAMES ${_FILE_NAMES}
  PATH_SUFFIXES ${_INCLUDE_PATH_SUFFIXES}
  HINTS ${boost_SEARCH_PATHS})

set(boost_INCLUDE_DIR ${boost_INCLUDE_DIR}/..)

if(boost_INCLUDE_DIR)
  message(STATUS "'boost' found via manual search. Setting variables...")
  set(boost_INCLUDES ${boost_INCLUDE_DIR})

  add_library(boost INTERFACE)
  target_include_directories(boost INTERFACE ${boost_INCLUDE_DIR})
  target_compile_definitions(boost INTERFACE BOOST)
  add_library(boost::boost ALIAS boost)
else()
  message(STATUS "'boost' package NOT found using manual approach.")
endif()

message(STATUS "'boost' include directory set to: ${boost_INCLUDES}")
find_package_handle_standard_args(boost DEFAULT_MSG boost_INCLUDE_DIR)
