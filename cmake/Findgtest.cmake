# OR2LaTeX
# Standard 'FindPackage.cmake' procedure:
# (1) Fetch it online via 'fetchContent'

# Define global vairables for the dependency (URLs, paths, names, etc)
# Package name:
set(_PACKAGE_NAME "gtest")
# Repository URL:
set(_REPO_URL "https://github.com/google/googletest.git")
# Target branch
set(_TARGET_BRANCH release-1.10.0)

include(FindPackageHandleStandardArgs)
set(${_PACKAGE_NAME}_FOUND 0)

  message(
    STATUS
      "Searching for '${_PACKAGE_NAME}' package by retrieving it from a repository...")

      # instructions taken from here: https://stackoverflow.com/questions/58677831/cmake-adding-gtest-to-build

    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  gtest
  GIT_REPOSITORY "${_REPO_URL}"
  GIT_TAG        "${_TARGET_BRANCH}"
)
FetchContent_MakeAvailable(gtest)

find_package_handle_standard_args(${_PACKAGE_NAME} DEFAULT_MSG)
