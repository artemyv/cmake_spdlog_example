set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

cmake_minimum_required(VERSION 3.21)
project(cmake_spdlog_example)
set(CMAKE_CXX_STANDARD 17)

# Set the compiler options

# define the library first before anything that depends on it
add_subdirectory(src)

########################################################################################################################
# Dependencies
########################################################################################################################
configure_file(extern/CMakeLists.txt.spdlog extern/spdlog-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/extern/spdlog-download)
if (result)
    message(FATAL_ERROR "CMake step for spdlog failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/extern/spdlog-download)
if (result)
    message(FATAL_ERROR "Build step for spdlog failed: ${result}")
endif ()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/extern/spdlog-src
        ${CMAKE_CURRENT_BINARY_DIR}/extern/spdlog-build
        EXCLUDE_FROM_ALL)

