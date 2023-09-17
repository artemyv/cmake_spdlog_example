#include "hello_lib.h"

#include <version.h>
#include <fmt/xchar.h>

hello_lib::retstr hello_lib::getDescription()
{
	return fmt::format(_TXT("Hello from project: {}."), cmake_spdlog_example_DESCRIPTION);
}
hello_lib::retstr hello_lib::getVersion()
{
	return fmt::format(_TXT("Version: {}."), cmake_spdlog_example_VERSION);
}
