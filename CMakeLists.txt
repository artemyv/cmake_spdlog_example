cmake_minimum_required(VERSION 3.21)

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

include(cmake/PreventInSourceBuilds.cmake)

# Set the project name and language
project(
  cmake_spdlog_example
  VERSION 1.0.2
  DESCRIPTION "Playground for cmake and spdlog"
  HOMEPAGE_URL "%%myurl%%"
  LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#dependencies
include(Dependencies.cmake)
cmake_spdlog_example_setup_dependencies()

# Set the compiler options
option(cmake_spdlog_example_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
add_library(cmake_spdlog_example_warnings INTERFACE)
add_library(cmake_spdlog_example::cmake_spdlog_example_warnings ALIAS cmake_spdlog_example_warnings)

option(cmake_spdlog_example_USE_WSTRING "Use wide strings" ON)

include(cmake/CompilerWarnings.cmake)
  cmake_spdlog_example_set_project_warnings(
    cmake_spdlog_example_warnings
    ${cmake_spdlog_example_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

# define the library first before anything that depends on it
add_subdirectory(src)
