########################################################################################################################
# Main exec
########################################################################################################################
set(main_SOURCES main.cpp)

add_executable(main ${main_SOURCES})
target_link_libraries(main PRIVATE spdlog)

target_include_directories(main PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
						   
add_custom_target(main_run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main.exe in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${main_SOURCES}
)

add_custom_target(run ALL
    DEPENDS main_run)