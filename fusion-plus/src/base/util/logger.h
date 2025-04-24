#pragma once

#include <cstdarg>

#include <iostream>
#include <string>

#include "util/math/geometry.h"
#include "configManager/configManager.h"

struct Logger
{
	enum class LogLevel { LOG_DEBUG, INFO, WARNING, LOG_ERROR };

	static void Init()
	{
		AllocConsole();
		freopen_s(&m_out, "CONOUT$", "w", stdout);
		freopen_s(&m_err, "CONOUT$", "w", stderr);

		Logger::initialized = true;

		std::cout << "fusion+\n" << std::endl;
	}

	static void Shutdown()
	{
		if (Logger::initialized)
		{
			if (m_out != nullptr) fclose(m_out);
			if (m_err != nullptr) fclose(m_err);
			FreeConsole();

			Logger::initialized = false;
		}
	}

	static std::string GetTimestamp()
	{
		std::time_t now = std::time(nullptr);
		struct tm timeInfo;
		localtime_s(&timeInfo, &now);  // Thread-safe version for Windows

		char buffer[80];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
		return std::string(buffer);
	}

	static std::string LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::LOG_DEBUG: return "d";
		case LogLevel::INFO: return "i";
		case LogLevel::WARNING: return "*";
		case LogLevel::LOG_ERROR: return "!";
		default: return "?";
		}
	}

	static void Log(LogLevel level, const char* format, ...)
	{
		if (!Logger::initialized) return;

		std::va_list args;
		va_start(args, format);
		char messageBuffer[1024];
		std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
		va_end(args);

		std::string logFilePath = configmanager::GetFusionPath() + "\\log.txt";
		std::ofstream logFile;
		logFile.open(logFilePath, std::ios::app);

		std::string logMessage = "[" + GetTimestamp() + "] [" + LogLevelToString(level) + "] " + messageBuffer;

		std::cout << logMessage << std::endl;

		if (logFile.is_open())
		{
			logFile << logMessage << std::endl;
			logFile.close();
		}
	}

	static void LogPosition(Vector3 position)
	{
		if (!Logger::initialized) return;

		Log(LogLevel::INFO, "X: %f, Y: %f, Z: %f", position.x, position.y, position.z);
	}

	static inline bool initialized = false;

private:
	static inline FILE* m_out;
	static inline FILE* m_err;
};

#define LOG_DEBUG(message, ...) Logger::Log(Logger::LogLevel::LOG_DEBUG, message, ##__VA_ARGS__)
#define LOG_INFO(message, ...) Logger::Log(Logger::LogLevel::INFO, message, ##__VA_ARGS__)
#define LOG_WARNING(message, ...) Logger::Log(Logger::LogLevel::WARNING, message, ##__VA_ARGS__)
#define LOG_ERROR(message, ...) Logger::Log(Logger::LogLevel::LOG_ERROR, message, ##__VA_ARGS__)
#define LOG_POS(pos) Logger::LogPosition(pos)