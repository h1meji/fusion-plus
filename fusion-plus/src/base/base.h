#pragma once
#include <Windows.h>
#include <string>

struct Base
{
	static void Init();
	static void Kill();

	static void RenderLoop();

	static inline bool Running;

	static inline std::string CrashReportPath;
	static void WriteCrashReport(EXCEPTION_POINTERS* pException);

	static inline const char* version = "v0.5";
};

