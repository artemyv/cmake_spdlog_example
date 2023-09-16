#include <spdlog/spdlog.h>
#include <sstream>

#define SPDLOG_LOGGER_STREAM(log, lvl)                                                                   \
    log && log->should_log(lvl) &&                                                                       \
        LogStream(log, lvl, spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}) == \
            LogLine()

class LogLine
{
    std::ostringstream m_ss;
public:
    LogLine() {}
    template <typename T> LogLine& operator<<(T t) { m_ss << t; return *this; }


    //template <typename T, typename = std::enable_if_t<std::is_function_v<T>>> LogLine& operator<<(T val) { m_ss << t; return *this; }

    std::string str() const { return m_ss.str(); }
};

class LogStream {
    std::shared_ptr<spdlog::logger> m_log;
    spdlog::level::level_enum m_lvl;
    spdlog::source_loc m_loc;
public:
    LogStream(std::shared_ptr<spdlog::logger> log, spdlog::level::level_enum lvl, spdlog::source_loc loc) :m_log{ log }, m_lvl{ lvl }, m_loc{ loc }{}
    bool operator==(const LogLine& line) {
        m_log->log(m_loc, m_lvl, "{}", line.str()); 
        return true;
    }
};

//specific log implementation macros

#define LVL_ERROR spdlog::level::err
#define LOG(x) SPDLOG_LOGGER_STREAM(spdlog::default_logger(),x)