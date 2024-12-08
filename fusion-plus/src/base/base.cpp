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

#include <thread>
#include <unordered_map>

bool IsKeyReleased(int key)
{
	static std::unordered_map<int, bool> keyStates;

	bool currentState = (GetAsyncKeyState(key) & 0x8000) == 0;
	bool prevState = keyStates[key];
	keyStates[key] = currentState;

	return prevState && !currentState;
}

void Base::Init()
{
	MH_Initialize();

	Java::Init();
	if (Java::Version == MinecraftVersion::UNKNOWN)
	{
		MessageBoxA(NULL, "Unknown Minecraft version detected", "fusion+", MB_OK | MB_ICONERROR);
		
		Logger::Kill();
		MH_Uninitialize();
		Java::Kill();

		FreeLibraryAndExitThread(Main::HModule, 0);
		return;
	}

	SDK::Init();

	if (Java::Version == MinecraftVersion::LUNAR_1_8_9) Patcher::Init();

	Menu::Init();

	g_ModuleManager = std::make_unique<ModuleManager>();
	g_ModuleManager->Init();

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

	StrayCache::DeleteRefs();
	Java::Kill();
	Menu::Kill();
	Logger::Kill();

	MH_Uninitialize();
}