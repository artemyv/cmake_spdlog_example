#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>
#include "logger.h"

int main() {
    
    LOG_ERROR("do as printf,%s", "format");
    LOG_INFO("do as printf,%d", 125);
    return 0;
}
