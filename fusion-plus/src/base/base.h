#pragma once

#include <string>

#include <Windows.h>

struct Base
{
	static void Init();
	static void Shutdown();

	static void renderLoop();

	static inline bool m_running;

	static inline const char* m_version = "v0.5";
};

