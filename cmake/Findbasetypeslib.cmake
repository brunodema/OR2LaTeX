# OR2LaTeX
# Standard 'FindPackage.cmake' procedure:
# (1) Fetch it online via 'fetchContent'

# Define global vairables for the dependency (URLs, paths, names, etc)
# Package name:
set(_PACKAGE_NAME "basetypeslib")
# Set target URLs for manual fetch:

include(FindPackageHandleStandardArgs)
set(${_PACKAGE_NAME}_FOUND 0)

# (3) Fetch it online via 'fetchContent'
message(
  STATUS
    "Searching for '${_PACKAGE_NAME}' package by retrieving it from a repository..."
)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  ${_PACKAGE_NAME}
  GIT_REPOSITORY https://github.com/brunodema/BaseTypesLib.git
  GIT_TAG master)
FetchContent_MakeAvailable(${_PACKAGE_NAME})

add_library(${_PACKAGE_NAME}::${_PACKAGE_NAME} ALIAS ${_PACKAGE_NAME})

find_package_handle_standard_args(${_PACKAGE_NAME} DEFAULT_MSG)
