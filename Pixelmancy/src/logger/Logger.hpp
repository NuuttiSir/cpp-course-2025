#pragma once

#define BUILD_LOG_LEVEL_TRACE 0
#define BUILD_LOG_LEVEL_DEBUG 1
#define BUILD_LOG_LEVEL_INFO 2
#define BUILD_LOG_LEVEL_WARN 3
#define BUILD_LOG_LEVEL_ERROR_LOG 4
#define BUILD_LOG_LEVEL_CRITICAL 5

#define BUILD_LOG_LEVEL BUILD_LOG_LEVEL_DEBUG

namespace pixelmancy {
namespace logger {

#ifdef _WIN32
constexpr const char* RESET_COLOR = "";
constexpr const char* TRACE_COLOR = "";
constexpr const char* DEBUG_COLOR = "";
constexpr const char* INFO_COLOR = "";
constexpr const char* WARN_COLOR = "";
constexpr const char* ERROR_COLOR = "";
constexpr const char* CRITICAL_COLOR = "";
constexpr const char* FILE_COLOR = "";
constexpr const char* LINE_COLOR = "";
#else
constexpr const char* RESET_COLOR = "\033[0m";
constexpr const char* TRACE_COLOR = "\033[37m";    // White
constexpr const char* DEBUG_COLOR = "\033[36m";    // Cyan
constexpr const char* INFO_COLOR = "\033[32m";     // Green
constexpr const char* WARN_COLOR = "\033[33m";     // Yellow
constexpr const char* ERROR_COLOR = "\033[31m";    // Red
constexpr const char* CRITICAL_COLOR = "\033[41m"; // Red background
constexpr const char* FILE_COLOR = "\033[35m";     // Magenta
constexpr const char* LINE_COLOR = "\033[34m";     // Blue
#endif

enum class LogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR_LOG,
    CRITICAL
};

struct endl_t
{
};

struct flush_t
{
};

struct file_t
{
    std::string fileName;
    std::string lineNumber;

    file_t(const std::string& file, const std::string& line) : fileName(file), lineNumber(line)
    {
    }
};

constexpr endl_t endl;
constexpr flush_t flush;
constexpr flush_t file;

class iLogger
{
public:
    virtual ~iLogger() = default;

    virtual LogLevel filter() const = 0;
    virtual void setLogLevel(LogLevel level) = 0;

    virtual iLogger& operator<<(LogLevel level) = 0;
    virtual iLogger& operator<<(std::string const& msg) = 0;
    virtual iLogger& operator<<(endl_t) = 0;
    virtual iLogger& operator<<(flush_t) = 0;
    virtual iLogger& operator<<(file_t) = 0;
    virtual iLogger& operator<<(int value) = 0;
    virtual iLogger& operator<<(float value) = 0;
    virtual iLogger& operator<<(double value) = 0;
    virtual iLogger& operator<<(unsigned value) = 0;
    virtual iLogger& operator<<(std::size_t value) = 0;

    iLogger& operator<<(const char* msg)
    {
        return operator<<(std::string(msg));
    }
};

} // namespace logger
} // namespace pixelmancy
