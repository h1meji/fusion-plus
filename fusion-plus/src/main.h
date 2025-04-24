#pragma once

#include <Windows.h>

class Main
{
public:
	static void Init();
	static void Shutdown();

	static inline HMODULE hModule;
};

