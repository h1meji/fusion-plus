#pragma once

#include "net/minecraft/client/Minecraft.h"

struct SDK
{
	static inline CMinecraft* minecraft;

	static void Init();
	static void Shutdown();
};

