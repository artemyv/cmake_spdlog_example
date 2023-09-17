#include <string>

namespace hello_lib
{
#ifdef cmake_spdlog_example_USE_WSTRING
using TextChar = wchar_t;
#else
using TextChar = char;
#endif

using retstr = std::basic_string<TextChar>;
retstr getDescription();
retstr getVersion();

}