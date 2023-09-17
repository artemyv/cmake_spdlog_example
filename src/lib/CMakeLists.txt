########################################################################################################################
# hello_lib lib
########################################################################################################################
set(hello_lib_SOURCES hello_lib.cpp hello_lib.h ${PROJECT_BINARY_DIR}/src/version.h)

add_library(hello ${hello_lib_SOURCES})
target_link_libraries(hello PRIVATE fmt::fmt)

if (cmake_spdlog_example_USE_WSTRING)
  target_compile_definitions(hello PRIVATE "cmake_spdlog_example_USE_WSTRING")
endif()

message( "project bin dir ${PROJECT_BINARY_DIR}")

target_include_directories(hello PUBLIC
                           "${PROJECT_BINARY_DIR}/src"
                           )
						   