#include "Logger.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <map>

std::string getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm tm_now;

    localtime_s(&tm_now, &now);

    std::stringstream time_stream;
    time_stream << std::put_time(&tm_now, "%H:%M:%S");

    return time_stream.str();
}

Logger::Logger() {}

Logger& Logger::getLogger()
{
    static Logger logger;
    return logger;
}

void Logger::log(const std::string& message, LogLevel severity)
{
    static const std::map <LogLevel, std::string> severities = {
            {LogLevel::INFO, "INFO"},
            {LogLevel::WARNING, "WARNING"},
            {LogLevel::ERROR, "ERROR"},
            {LogLevel::CRITICAL, "CRITICAL"}
    };

    std::cerr << '[' << getCurrentTime() << "] [" << severities.at(severity) << "] " << message << std::endl;
}

void Logger::info(const std::string& message)
{
    this->log(message, LogLevel::INFO);
}

void Logger::warning(const std::string& message)
{
    this->log(message, LogLevel::WARNING);
}

void Logger::error(const std::string& message)
{
    this->log(message, LogLevel::ERROR);
}

void Logger::critical(const std::string& message)
{
    this->log(message, LogLevel::CRITICAL);
}
