#include <Windows.h>
#include <thread>

#include "logger.h"
#include <cstdarg>

FILE* out;
FILE* err;

void Logger::Init()
{
	AllocConsole();
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&err, "CONOUT$", "w", stderr);

	Logger::Initialized = true;

	std::cout << "Welcome to fusion+\n" << std::endl;
}

void Logger::Kill()
{
	if (Logger::Initialized)
	{
		fclose(out);
		fclose(err);
		FreeConsole();
	}
}

void Logger::Log(const char* format, ...)
{
	//if (!Logger::Initialized) Logger::Init();

	std::va_list args;
	va_start(args, format);
	char messageBuffer[1024];
	std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
	va_end(args);

	std::cout << "[ LOG ] :: " << messageBuffer << std::endl;
}

void Logger::LogPosition(Vector3 position)
{
	if (!Logger::Initialized) Logger::Init();

	std::cout << "[ LOG POS ] :: X -> " << position.x << " Y -> " << position.y << " Z ->" << position.z << std::endl;
}

void Logger::Err(const char* format, ...)
{
	if (!Logger::Initialized) Logger::Init();

	std::va_list args;
	va_start(args, format);
	char messageBuffer[1024];
	std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
	va_end(args);

	std::cout << "[ ERR ] :: " << messageBuffer << std::endl;
}

void Logger::LogWait(int seconds, const char* format, ...)
{
	if (!Logger::Initialized) Logger::Init();

	std::va_list args;
	va_start(args, format);
	char messageBuffer[1024];
	std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
	va_end(args);

	std::cout << "[ LOG ] :: " << messageBuffer << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Logger::ErrWait(int seconds, const char* format, ...)
{
	if (!Logger::Initialized) Logger::Init();

	std::va_list args;
	va_start(args, format);
	char messageBuffer[1024];
	std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
	va_end(args);

	std::cout << "[ ERR ] :: " << messageBuffer << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
