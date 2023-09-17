#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>

#include <version.h>

int main() {
    SPDLOG_INFO("Hello from project: {}.", cmake_spdlog_example_DESCRIPTION);
    SPDLOG_INFO("Version: {}", cmake_spdlog_example_VERSION);
	
    return 0;
}
