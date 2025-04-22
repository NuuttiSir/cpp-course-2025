#include "Log.hpp"

#include <iostream>

namespace pixelmancy {
namespace logger {
std::shared_ptr<ostream_logger> Log::s_logger;

void Log::Init()
{
    s_logger = std::make_shared<ostream_logger>(std::cout);
    std::ios_base::sync_with_stdio(false);
    s_logger->setLogLevel(LogLevel::TRACE);
}

void Log::Init(LogLevel level)
{
    s_logger = std::make_shared<ostream_logger>(std::cout);
    std::ios_base::sync_with_stdio(false);
    s_logger->setLogLevel(level);
}
} // namespace logger
} // namespace pixelmancy
