########################################################################################################################
# Main exec
########################################################################################################################
set(main_SOURCES main.cpp)

add_executable(main ${main_SOURCES})
target_link_libraries(main PRIVATE spdlog PRIVATE hello)

include_directories(${hello_SOURCE_DIR})

						   
add_custom_target(main_run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main.exe in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${main_SOURCES}
)

add_custom_target(run ALL
    DEPENDS main_run)