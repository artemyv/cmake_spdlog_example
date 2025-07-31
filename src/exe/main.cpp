#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <source_location>
#include <string>

namespace Log
{
    template <spdlog::level::level_enum Level, class... Args>
    struct [[maybe_unused]] Logger
    {
        Logger() = delete;
        explicit Logger(
            fmt::format_string<Args...> fmt,
            Args&&... args,
            std::source_location loc = std::source_location::current())
        {
            spdlog::log(
                spdlog::source_loc{loc.file_name(), static_cast<int>(loc.line()), loc.function_name()},
                Level,
                fmt,
                std::forward<Args>(args)...);
        }
    };

    // Deduction guide for Logger
    template <spdlog::level::level_enum Level, class... Args>
    Logger(fmt::format_string<Args...>, Args&&..., std::source_location) -> Logger<Level, Args...>;
    template <spdlog::level::level_enum Level, class... Args>
    Logger(fmt::format_string<Args...>, Args&&...) -> Logger<Level, Args...>;

    template <class... Args>
    using trace    = Logger<spdlog::level::trace, Args...>;
    template <class... Args>
    using debug    = Logger<spdlog::level::debug, Args...>;
    template <class... Args>
    using info     = Logger<spdlog::level::info, Args...>;
    template <class... Args>
    using warn     = Logger<spdlog::level::warn, Args...>;
    template <class... Args>
    using err      = Logger<spdlog::level::err, Args...>;
    template <class... Args>
    using critical = Logger<spdlog::level::critical, Args...>;
}

int main()
{
    Log::info("Hello info from {}.", "main.cpp");
    Log::err("Hello err from {}.", "main.cpp");
    Log::warn("Hello warn from {}.", "main.cpp");
    Log::debug("Hello debug from {}.", "main.cpp");
    return 0;
}