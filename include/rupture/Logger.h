
#pragma once

namespace Rupture {
    enum class LogLevel {
        DEBUG  = 0,
        INFO   = 1,
        WARN   = 2,
        ERROR  = 3
    };

    class Logger {
    private:
        static LogLevel currentLevel;
    public:
        
        static void Log(LogLevel level, const char * msg, const char * file, int line);
        static void SetLevel(LogLevel level);
    };
}


#ifdef RUPTURE_DEBUG
    #define LOG_DEBUG(msg) Rupture::Logger::Log(Rupture::LogLevel::DEBUG, msg, __FILE__, __LINE__)
    #define LOG_INFO(msg)  Rupture::Logger::Log(Rupture::LogLevel::INFO, msg, __FILE__, __LINE__)
    #define LOG_WARN(msg)  Rupture::Logger::Log(Rupture::LogLevel::WARN, msg, __FILE__, __LINE__)
    #define LOG_ERROR(msg) Rupture::Logger::Log(Rupture::LogLevel::ERROR, msg, __FILE__, __LINE__)
#else
    #define LOG_DEBUG(msg)
    #define LOG_INFO(msg)
    #define LOG_WARN(msg)
    #define LOG_ERROR(msg)
#endif