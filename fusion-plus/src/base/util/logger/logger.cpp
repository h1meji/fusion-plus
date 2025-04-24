#include "logger.h"

#include <cstdarg>

#include "configManager/configManager.h"

FILE* out;
FILE* err;

void Logger::Init()
{
	AllocConsole();
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&err, "CONOUT$", "w", stderr);

	Logger::initialized = true;

	std::cout << "fusion+\n" << std::endl;
}

void Logger::Shutdown()
{
	if (Logger::initialized)
	{
		if (out != nullptr) fclose(out);
		if (err != nullptr) fclose(err);
		FreeConsole();

		Logger::initialized = false;
	}
}

std::string Logger::GetTimestamp()
{
	std::time_t now = std::time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &now);  // Thread-safe version for Windows

	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
	return std::string(buffer);
}

std::string Logger::LogLevelToString(LogLevel level)
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

void Logger::Log(LogLevel level, const char* format, ...)
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

	if (logFile.is_open()) {
		logFile << logMessage << std::endl;
		logFile.close();
	}
}

void Logger::Log(const char* format, ...)
{
	if (!Logger::initialized) return;

	std::va_list args;
	va_start(args, format);
	char messageBuffer[1024];
	std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
	va_end(args);

	Log(LogLevel::INFO, messageBuffer);
}

void Logger::LogPosition(Vector3 position)
{
	if (!Logger::initialized) return;

	Log(LogLevel::INFO, "X: %f, Y: %f, Z: %f", position.x, position.y, position.z);
}