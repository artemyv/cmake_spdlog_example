#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>

#include <hello_lib.h>

int main() {
    SPDLOG_INFO("{}.", hello_lib::getDescrption());
    SPDLOG_INFO("{}" , hello_lib::getVersion());
	
    return 0;
}
