include(FindPackageHandleStandardArgs)

message(STATUS "searching for 'ortools' package'...")

list(APPEND ortools_SEARCH_PATHS "$ENV{PROGRAMFILES}"
     "$ENV{PROGRAMFILES\(X86\)}")

find_path(
  ortools_INCLUDE_DIR ortools/linear_solver/glop_utils.h
  PATH_SUFFIXES ortools/include include
  HINTS ${ortools_DIR})

find_library(
  ortools_LIBRARY
  NAMES ortools.lib libortools.so
  PATH_SUFFIXES ortools/lib lib lib64
  PATHS ${ortools_SEARCH_PATHS})

find_package_handle_standard_args(ortools DEFAULT_MSG ortools_INCLUDE_DIR
                                  ortools_LIBRARY)

if(ortools_FOUND)
  message(STATUS "'ortools' found via 'find_package'.")
  set(ortools_INCLUDES ${ortools_INCLUDE_DIR})
  set(ortools_LIBRARIES ${ortools_LIBRARY})
else()
  set(Windows_ORTOOLS_URL
      "https://github.com/google/or-tools/releases/download/v8.1/or-tools_VisualStudio2019-64bit_v8.1.8487.zip"
  )
  set(MSYS_ORTOOLS_URL
      "https://github.com/google/or-tools/releases/download/v8.1/or-tools_VisualStudio2019-64bit_v8.1.8487.zip"
  )
  set(Linux_ORTOOLS_URL
      "https://github.com/google/or-tools/releases/download/v8.1/or-tools_ubuntu-20.04_v8.1.8487.tar.gz"
  )
  message(
    STATUS
      "'ortools' not found via 'find_package'. Retrieving it from the main repository..."
  )
  message(
    STATUS
      "The detected OS is: ${CMAKE_SYSTEM_NAME}. The associated URL will be: ${${CMAKE_SYSTEM_NAME}_ORTOOLS_URL}."
  )

  include(FetchContent)
  set(FETCHCONTENT_QUIET FALSE)
  set(BUILD_DEPS ON) # this is a 'ortools' option definition
  FetchContent_Declare(ortools URL ${${CMAKE_SYSTEM_NAME}_ORTOOLS_URL})
  # After the following call, the CMake targets defined by or-tools will be
  # defined and available to the rest of the build
  FetchContent_MakeAvailable(ortools)

  # this is sort of an ugly version of a 'find_package'
  find_library(
    ortools_LIBRARY_DIR
    NAMES libortools.so ortools.lib
    HINTS ${ortools_SOURCE_DIR}/lib)
  set(ortools_LIBRARIES ${ortools_LIBRARY_DIR})
  set(ortools_INCLUDE_DIR ${ortools_SOURCE_DIR}/include)
  set(ortools_INCLUDES ${ortools_SOURCE_DIR}/include)
endif()
