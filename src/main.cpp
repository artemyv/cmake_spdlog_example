#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>

int main() {
    SPDLOG_INFO("Hello from spdlog!");

    return 0;
}
