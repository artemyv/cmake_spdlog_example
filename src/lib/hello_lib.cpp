#include "hello_lib.h"

#include <version.h>
#include <fmt/format.h>

std::string hello_lib::getDescription()
{
	return fmt::format("Hello from project: {}.", cmake_spdlog_example_DESCRIPTION);
}
 
std::string hello_lib::getVersion()
{
	return fmt::format("Version: {}", cmake_spdlog_example_VERSION);
}
