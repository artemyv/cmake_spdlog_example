#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/printf.h>
template <class loggerPtr, class... Args>
void loglineprintf(loggerPtr                 logger,
    spdlog::level::level_enum level,
    spdlog::source_loc        loc,
    const char* fmt,
    const Args&... args) noexcept
{
    if (logger && logger->should_log(level))
    {
        logger->log(loc, level, "{}", fmt::sprintf(fmt, args...));
    }
}

#define SPDLOG_LOGGER_PRINTF(logger, level, ...) \
    loglineprintf(logger, level, spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, __VA_ARGS__)

//specific log implementation macros

#define LOG_ERROR(...) SPDLOG_LOGGER_PRINTF(spdlog::default_logger(),spdlog::level::err,__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_PRINTF(spdlog::default_logger(),spdlog::level::info,__VA_ARGS__)