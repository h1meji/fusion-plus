#pragma once

#include <iostream>
#include <string>

#include "util/math/geometry.h"

struct Logger
{
	enum class LogLevel { LOG_DEBUG, INFO, WARNING, LOG_ERROR };

	static void Init();
	static void Shutdown();

	static std::string GetTimestamp();
	static std::string LogLevelToString(LogLevel level);
	static void Log(LogLevel level, const char* format, ...);

	static void Log(const char* format, ...);
	static void LogPosition(Vector3 message);

	static inline bool initialized = false;;
};

#define LOG_DEBUG(message, ...) Logger::Log(Logger::LogLevel::LOG_DEBUG, message, ##__VA_ARGS__)
#define LOG_INFO(message, ...) Logger::Log(Logger::LogLevel::INFO, message, ##__VA_ARGS__)
#define LOG_WARNING(message, ...) Logger::Log(Logger::LogLevel::WARNING, message, ##__VA_ARGS__)
#define LOG_ERROR(message, ...) Logger::Log(Logger::LogLevel::LOG_ERROR, message, ##__VA_ARGS__)
#define LOG_POS(pos) Logger::LogPosition(Logger::LogLevel::INFO, pos)