#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>
#include  <source_location>
#include <string>
#define SKSE_MAKE_SOURCE_LOGGER(a_func, a_type)                                       \
                                                                                      \
	template <class... Args>                                                          \
	struct [[maybe_unused]] a_func                                                    \
	{                                                                                 \
		a_func() = delete;                                                            \
                                                                                      \
		explicit a_func(                                                              \
			fmt::format_string<Args...> a_fmt,                                        \
			Args&&... a_args,                                                         \
			std::source_location a_loc = std::source_location::current()) \
		{                                                                             \
			spdlog::log(                                                              \
				spdlog::source_loc{                                                   \
					a_loc.file_name(),                                                \
					static_cast<int>(a_loc.line()),                                   \
					a_loc.function_name() },                                          \
				spdlog::level::a_type,                                                \
				a_fmt,                                                                \
				std::forward<Args>(a_args)...);                                       \
		}                                                                             \
	};                                                                                \
                                                                                      \
	template <class... Args>                                                          \
	a_func(fmt::format_string<Args...>, Args&&...) -> a_func<Args...>;

namespace Log
{
	SKSE_MAKE_SOURCE_LOGGER(trace, trace);
	SKSE_MAKE_SOURCE_LOGGER(debug, debug);
	SKSE_MAKE_SOURCE_LOGGER(info, info);
	SKSE_MAKE_SOURCE_LOGGER(warn, warn);
	SKSE_MAKE_SOURCE_LOGGER(err, err);
	SKSE_MAKE_SOURCE_LOGGER(critical, critical);
}

int main()
{
    Log::info("Hello info from {}.", "main.cpp");
    Log::err("Hello err from {}.", "main.cpp");
    Log::warn("Hello warn from {}.", "main.cpp");
    Log::debug("Hello debug from {}.", "main.cpp");
    return 0;
}