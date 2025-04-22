#pragma once

#include <memory>
#include "ostream_logger.hpp"

namespace pixelmancy::logger {
class Log
{
public:
    static void Init();
    static void Init(LogLevel level);

    static std::shared_ptr<ostream_logger>& GetLogger()
    {
        return s_logger;
    }

    ~Log() = default;

private:
    static std::shared_ptr<ostream_logger> s_logger;
};

} // namespace pixelmancy::logger

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_TRACE
#    define P_LOG_TRACE() \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::TRACE << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_TRACE() std::ostringstream()
#endif

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_DEBUG
#    define P_LOG_DEBUG() \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::DEBUG << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_DEBUG() std::ostringstream()
#endif

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_INFO
#    define P_LOG_INFO() \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::INFO << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_INFO() std::ostringstream()
#endif

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_WARN
#    define P_LOG_WARN() \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::WARN << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_WARN() std::ostringstream()
#endif

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_ERROR_LOG
#    define P_LOG_ERROR()                                                                      \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::ERROR_LOG \
                                                  << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_ERROR() std::ostringstream()
#endif

#if BUILD_LOG_LEVEL <= BUILD_LOG_LEVEL_CRITICAL
#    define P_LOG_CRITICAL()                                                                  \
        (*::pixelmancy::logger::Log::GetLogger()) << ::pixelmancy::logger::LogLevel::CRITICAL \
                                                  << ::pixelmancy::logger::file_t(__FILE__, std::to_string(__LINE__))
#else
#    define P_LOG_CRITICAL() std::ostringstream()
#endif
