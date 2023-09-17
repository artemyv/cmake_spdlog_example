#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>

#include <hello_lib.h>

int main() {
#ifdef cmake_spdlog_example_USE_WSTRING
    SPDLOG_INFO(L"W {}.", hello_lib::getDescrptionW());
    SPDLOG_INFO(L"W {}" , hello_lib::getVersionW());
#else 
    SPDLOG_INFO("U {}.", hello_lib::getDescrption());
    SPDLOG_INFO("U {}" , hello_lib::getVersion());
#endif	
    return 0;
}
