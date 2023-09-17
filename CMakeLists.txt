cmake_minimum_required(VERSION 3.21)

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

include(cmake/PreventInSourceBuilds.cmake)

# Set the project name and language
project(
  cmake_spdlog_example
  VERSION 1.0.1
  DESCRIPTION "Playground for cmake and spdlog"
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX)

configure_file(src/version.h.in version.h)



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#dependencies
include(Dependencies.cmake)
myproject_setup_dependencies()

# Set the compiler options
option(myproject_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
add_library(myproject_warnings INTERFACE)
add_library(myproject::myproject_warnings ALIAS myproject_warnings)

include(cmake/CompilerWarnings.cmake)
  myproject_set_project_warnings(
    myproject_warnings
    ${myproject_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

# define the library first before anything that depends on it
add_subdirectory(src)

