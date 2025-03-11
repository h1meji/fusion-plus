#pragma once
#include <iostream>
#include <string>
#include "util/math/geometry.h"

struct Logger
{
	static void Init();
	static void Kill();

	static void Log(const char* format, ...);
	static void LogPosition(Vector3 message);
	static void Err(const char* format, ...);

	static void LogWait(int seconds, const char* format, ...);
	static void ErrWait(int seconds, const char* format, ...);

	static inline bool Initialized = false;;
};

#define LOG(message, ...) Logger::Log(message, ##__VA_ARGS__)
#define LOG_POS(position) Logger::LogPosition(position)
#define ERR(message, ...) Logger::Err(message, ##__VA_ARGS__)
#define LOG_WAIT(seconds, message, ...) Logger::LogWait(seconds, message, ##__VA_ARGS__)
#define ERR_WAIT(seconds, message, ...) Logger::ErrWait(seconds, message, ##__VA_ARGS__)