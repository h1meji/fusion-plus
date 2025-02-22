#include "base.h"

#include "../main.h"
#include "java/java.h"
#include "util/logger.h"
#include "menu/menu.h"
#include "moduleManager/moduleManager.h"
#include "sdk/sdk.h"
#include "util/window/borderless.h"
#include "patcher/patcher.h"

#include "minhook/minhook.h"

#include "util/minecraft.h"

#include <thread>
#include <unordered_map>
#include <sdk/net/minecraft/client/ClientBrandRetriever.h>
#include <java/hotspot/hotspot.h>
#include <java/javahook.h>

static bool IsKeyReleased(int key)
{
	static std::unordered_map<int, bool> keyStates;

	bool currentState = (GetAsyncKeyState(key) & 0x8000) == 0;
	bool prevState = keyStates[key];
	keyStates[key] = currentState;

	return prevState && !currentState;
}

void Base::Init()
{
#ifdef _DEBUG
	Logger::Init();
#endif

	MH_Initialize();

	Java::Init();
	switch (Java::Version)
	{
	case MinecraftVersion::LUNAR_1_8_9:
		Logger::Log("Lunar Client 1.8.9 detected");
		break;
	case MinecraftVersion::LUNAR_1_7_10:
		Logger::Log("Lunar Client 1.7.10 detected");
		break;
	case MinecraftVersion::VANILLA_1_8_9:
		Logger::Log("Vanilla 1.8.9 detected");
		break;
	case MinecraftVersion::VANILLA_1_7_10:
		Logger::Log("Vanilla 1.7.10 detected");
		break;
	case MinecraftVersion::UNKNOWN:
		Logger::Log("Unknown Minecraft version detected");
		MessageBoxA(NULL, "Unknown Minecraft version detected", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Kill();
		MH_Uninitialize();
		Java::Kill();
		FreeLibraryAndExitThread(Main::HModule, 0);
		break;
	default:
		Logger::Log("Unknown Minecraft version detected");
		MessageBoxA(NULL, "Unknown Minecraft version detected", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Kill();
		MH_Uninitialize();
		Java::Kill();
		FreeLibraryAndExitThread(Main::HModule, 0);
		break;
	}

	SDK::Init();

	if (Java::Version == MinecraftVersion::LUNAR_1_8_9) Patcher::Init();

	if (!HotSpot::init())
	{
		Logger::Log("Failed to initialize HotSpot");
		MessageBoxA(NULL, "Failed to initialize HotSpot", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Kill();
		MH_Uninitialize();
		Java::Kill();
		FreeLibraryAndExitThread(Main::HModule, 0);
		return;
	}

	Menu::Init();

	g_ModuleManager = std::make_unique<ModuleManager>();
	g_ModuleManager->Init();

	MinecraftItems::Init();

	Base::Running = true;

	while (Base::Running)
	{
		g_ModuleManager->UpdateModules();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	Main::Kill();
}	

void Base::Kill()
{
	Patcher::Kill();
	if (Borderless::Enabled)
		Borderless::Restore(Menu::HandleWindow);

	JavaHook::clean();
	StrayCache::DeleteRefs();
	Java::Kill();
	Menu::Kill();
	Logger::Kill();

	MH_Uninitialize();
}