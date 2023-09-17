########################################################################################################################
# hello_lib lib
########################################################################################################################
set(hello_lib_SOURCES hello_lib.cpp hello_lib.h)

add_library(hello ${hello_lib_SOURCES})
target_link_libraries(hello PRIVATE fmtlib)

target_include_directories(hello PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
						   