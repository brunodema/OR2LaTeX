# OR2LaTeX Standard 'FindPackage.cmake' procedure:
# (1) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
# (2) Fetch it online via 'fetchContent'

# Define global variables for the dependency (URLs, paths, names, etc) Search
# Package name:
set(_PACKAGE_NAME "boost")
# Paths:
set(_SEARCH_PATHS "$ENV{PROGRAMFILES}/boost/" "C:/boost/" "usr/local")
# Include path suffixes:
set(_INCLUDE_PATH_SUFFIXES "boost")
# Library path suffixes:
set(_FILE_NAMES "align.hpp")
# Set target URLs for manual fetch:
#2set(boost_WINDOWS_URL
#    "https://github.com/google/or-tools/releases/download/v8.1/or-tools_VisualStudio2019-64bit_v8.1.8487.zip"
#)
set(boost_Windows_URL
    "https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz")
set(boost_Linux_URL
    "https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.gz")

# Standard strategy definitions for the package:

include(FindPackageHandleStandardArgs)
set(boost_FOUND 0)

# Standard strategy definitions for the package:
option(boost_FIND_BY_PACKAGE
       "Sets if the package can manually search for the dependency or not." ON)
option(
  boost_FIND_BY_FETCH
  "Sets if the package can be retrieved from an external repository or not." ON)

if(boost_FIND_BY_PACKAGE)
  # (1) Search manually for the dependency (set 'INCLUDES'/'LIBRARIES' variables)
  message(
    STATUS "Searching for '${_PACKAGE_NAME}' package using manual approach...")
  list(APPEND boost_SEARCH_PATHS ${_SEARCH_PATHS})

  find_path(
    boost_INCLUDE_DIR
    NAMES ${_FILE_NAMES}
    PATH_SUFFIXES ${_INCLUDE_PATH_SUFFIXES}
    HINTS ${boost_SEARCH_PATHS})

  set(boost_INCLUDE_DIR ${boost_INCLUDE_DIR}/..
  )# goes back a folder to target the actual desired directory

  if(boost_INCLUDE_DIR)
    message(
      STATUS "'${_PACKAGE_NAME}' found via manual search. Setting variables...")

    add_library(boost INTERFACE)
    target_include_directories(boost INTERFACE ${boost_INCLUDE_DIR})
    target_compile_definitions(boost INTERFACE BOOST)
    add_library(boost::boost ALIAS boost)
  else()
    message(
      STATUS "'${_PACKAGE_NAME}' package NOT found using manual approach.")
  endif()
endif()
if(boost_FIND_BY_FETCH AND boost_FOUND EQUAL 0)
  message(
    STATUS
      "Searching for '${_PACKAGE_NAME}' package by retrieving it from a repository..."
  )
  message(
    STATUS
      "The detected OS is: ${CMAKE_SYSTEM_NAME}. The associated URL will be: ${boost_${CMAKE_SYSTEM_NAME}_URL}."
  )

  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)
  FetchContent_Declare(boost URL ${boost_${CMAKE_SYSTEM_NAME}_URL})
  FetchContent_MakeAvailable(boost)

  # this is sort of an ugly version of a 'find_package'

  set(boost_INCLUDE_DIR ${boost_SOURCE_DIR})

  #add_library(boost INTERFACE)
  target_include_directories(boost INTERFACE ${boost_INCLUDE_DIR})

  add_library(boost::boost ALIAS boost)
endif()

# Sets the missing variables ('INCLUDES', 'LIBRARIES')
set(boost_INCLUDES ${boost_INCLUDE_DIR})
message(STATUS "'${_PACKAGE_NAME}' include directory set to: ${boost_INCLUDES}")
find_package_handle_standard_args(boost DEFAULT_MSG boost_INCLUDE_DIR)
