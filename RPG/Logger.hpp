#pragma once

#include <string>

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class Logger
{
private:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:
	static Logger& getLogger();
	void log(const std::string& message, LogLevel severity);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);
	void critical(const std::string& message);
};
