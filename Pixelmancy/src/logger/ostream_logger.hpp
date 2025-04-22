#pragma once

#include <filesystem>
#include <ostream>
#include <string>

#include "Logger.hpp"

namespace pixelmancy {
namespace logger {

/**
 * This is created by refereing https://www.youtube.com/watch?v=8c2nfQrPb6g&t=795s
 * @brief A logger that writes to an ostream.
 */
template <typename CharT, typename Traites = std::char_traits<CharT>>
class basic_ostream_logger : public iLogger
{
public:
    basic_ostream_logger(std::basic_ostream<CharT, Traites>& stream) : m_stream(stream)
    {
    }

    LogLevel filter() const override
    {
        return m_filterLogLevel;
    }

    void setLogLevel(LogLevel level) override
    {
        m_messageLogLevel = level;
    }

    iLogger& operator<<(LogLevel level) override
    {
        setLogLevel(level);
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            switch (m_messageLogLevel)
            {
            case LogLevel::TRACE:
                m_stream << TRACE_COLOR << "[TRACE]" << RESET_COLOR;
                break;

            case LogLevel::DEBUG:
                m_stream << DEBUG_COLOR << "[DEBUG]" << RESET_COLOR;
                break;

            case LogLevel::INFO:
                m_stream << INFO_COLOR << "[INFO]" << RESET_COLOR;
                break;

            case LogLevel::WARN:
                m_stream << WARN_COLOR << "[WARN]" << RESET_COLOR;
                break;

            case LogLevel::ERROR_LOG:
                m_stream << ERROR_COLOR << "[ERROR]" << RESET_COLOR;
                break;

            case LogLevel::CRITICAL:
                m_stream << CRITICAL_COLOR << "[CRITICAL]" << RESET_COLOR;
                break;
            }
        }
        return *this;
    }

    iLogger& operator<<(std::string const& msg) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << msg;
        }
        return *this;
    }

    iLogger& operator<<(endl_t) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << "\n";
        }
        return *this;
    }

    iLogger& operator<<(file_t fileData) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            std::filesystem::path filePath(fileData.fileName);
            m_stream << "[" << LINE_COLOR << filePath.filename().string() << RESET_COLOR << ":" << LINE_COLOR << fileData.lineNumber << RESET_COLOR << "] - ";
        }
        return *this;
    }

    iLogger& operator<<(flush_t) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << std::flush;
        }
        return *this;
    }

    iLogger& operator<<(int i) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << i;
        }
        return *this;
    }

    iLogger& operator<<(float i) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << i;
        }
        return *this;
    }

    iLogger& operator<<(double i) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << i;
        }
        return *this;
    }

    iLogger& operator<<(unsigned i) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << static_cast<int>(i);
        }
        return *this;
    }

    iLogger& operator<<(std::size_t i) override
    {
        if (m_messageLogLevel >= m_filterLogLevel)
        {
            m_stream << i;
        }
        return *this;
    }

private:
    std::basic_ostream<CharT, Traites>& m_stream;
    LogLevel m_filterLogLevel = static_cast<LogLevel>(BUILD_LOG_LEVEL);
    LogLevel m_messageLogLevel = LogLevel::INFO;
};

using ostream_logger = basic_ostream_logger<char>;

} // namespace logger
} // namespace pixelmancy
