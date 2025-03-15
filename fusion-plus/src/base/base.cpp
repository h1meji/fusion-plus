#include "base.h"

#include "../main.h"
#include "java/java.h"
#include "util/logger/logger.h"
#include "menu/menu.h"
#include "moduleManager/moduleManager.h"
#include "sdk/sdk.h"
#include "util/window/borderless.h"
#include "patcher/patcher.h"

#include "minhook/minhook.h"

#include "util/minecraft/minecraft.h"
#include "configManager/configManager.h"

#include <thread>
#include <unordered_map>
#include <sdk/net/minecraft/client/ClientBrandRetriever.h>
#include <java/hotspot/hotspot.h>
#include <java/javahook.h>

void Base::Init()
{
	Base::CrashReportPath = ConfigManager::GetFusionPath();
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
	case MinecraftVersion::FORGE_1_8_9:
		Logger::Log("Forge 1.8.9 detected");
		break;
	case MinecraftVersion::FORGE_1_7_10:
		Logger::Log("Forge 1.7.10 detected");
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

static std::string GetExceptionDescription(DWORD exceptionCode)
{
	switch (exceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION: return "Access Violation (Invalid Memory Access)";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "Array Bounds Exceeded";
	case EXCEPTION_BREAKPOINT: return "Breakpoint Encountered";
	case EXCEPTION_DATATYPE_MISALIGNMENT: return "Data Type Misalignment";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "Floating-Point Divide by Zero";
	case EXCEPTION_FLT_OVERFLOW: return "Floating-Point Overflow";
	case EXCEPTION_ILLEGAL_INSTRUCTION: return "Illegal Instruction";
	case EXCEPTION_INT_DIVIDE_BY_ZERO: return "Integer Divide by Zero";
	case EXCEPTION_PRIV_INSTRUCTION: return "Privileged Instruction";
	case EXCEPTION_STACK_OVERFLOW: return "Stack Overflow";
	case EXCEPTION_COLLIDED_UNWIND: return "Collided Unwind";
	case EXCEPTION_CONTINUE_EXECUTION: return "Continue Execution";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "Non-Continuable Exception";
	case EXCEPTION_INVALID_DISPOSITION: return "Invalid Disposition";
	case EXCEPTION_GUARD_PAGE: return "Guard Page Violation";
	case EXCEPTION_INVALID_HANDLE: return "Invalid Handle";
	case EXCEPTION_IN_PAGE_ERROR: return "In Page Error";
	case EXCEPTION_SINGLE_STEP: return "Single Step";
	default: return "Unknown Exception";
	}
}

static void LogStackTrace(std::ofstream& log)
{
	const int maxFrames = 10;
	void* stack[maxFrames];
	unsigned short frames = CaptureStackBackTrace(0, maxFrames, stack, nullptr);

	log << "Stack Trace\n";
	for (unsigned short i = 0; i < frames; ++i)
	{
		log << "[" << i << "] " << stack[i] << "\n";
	}
}

void Base::WriteCrashReport(EXCEPTION_POINTERS* pException)
{
	std::ofstream log((Base::CrashReportPath + "crash_report.txt").c_str(), std::ios::app);
	if (!log.is_open())
	{
		MessageBoxA(NULL, "Failed to write crash report", "fusion+", MB_OK | MB_ICONERROR);
		return;
	}

	std::string javaVer = "";
	switch (Java::Version)
	{
	case MinecraftVersion::LUNAR_1_8_9:
		javaVer = "Lunar Client 1.8.9";
		break;
	case MinecraftVersion::LUNAR_1_7_10:
		javaVer = "Lunar Client 1.7.10";
		break;
	case MinecraftVersion::VANILLA_1_8_9:
		javaVer = "Vanilla 1.8.9";
		break;
	case MinecraftVersion::VANILLA_1_7_10:
		javaVer = "Vanilla 1.7.10";
		break;
	case MinecraftVersion::FORGE_1_8_9:
		javaVer = "Forge 1.8.9";
		break;
	case MinecraftVersion::FORGE_1_7_10:
		javaVer = "Forge 1.7.10";
		break;
	case MinecraftVersion::UNKNOWN:
		javaVer = "Unknown Minecraft";
		break;
	default:
		javaVer = "Invalid Minecraft";
		break;
	}

	std::string modules = "";
	for (auto& module : g_ModuleManager->GetModules())
	{
		if (module->IsEnabled())
			modules += "- " + module->GetName() + "\n";
	}

	json j;
	std::string settings = "";
	if (ConfigManager::SettingsToJson(j))
	{
		settings = j.dump();
	}

	time_t now = time(0);
	struct tm tstruct;
	char buf[80]{};
	localtime_s(&tstruct, &now);
	std::string crashTime = std::string(buf, strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct));

	DWORD exceptionCode = pException->ExceptionRecord->ExceptionCode;
	PVOID exceptionAddress = pException->ExceptionRecord->ExceptionAddress;

	log << "=== Crash Report ===\n";
	log << "Time:" << std::string(buf, strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct)) << "\n";
	log << "Exception Code: 0x" << std::hex << exceptionCode << " (" << GetExceptionDescription(pException->ExceptionRecord->ExceptionCode) << ")\n";
	log << "Exception Address: 0x" << std::hex << exceptionAddress << "\n";
	log << "\n";
	LogStackTrace(log);
	log << "\n";
	log << "Minecraft Version: " << javaVer << "\n";
	log << "Client Brand: " << SDK::Minecraft->OriginalClientBrand << "\n";
	log << "\n";
	log << "Enabled Modules: \n" << modules << "\n";
	log << "Settings: \n" << settings << "\n";
	log << "====================\n\n";
	log.close();

	// Open crash report path in explorer
	ShellExecuteA(NULL, "open", Base::CrashReportPath.c_str(), NULL, NULL, SW_SHOWNORMAL);

	// Open msgbox with success and crash report path
	MessageBoxA(NULL, ("Crash report written to " + Base::CrashReportPath + "crash_report.txt").c_str(), "fusion+", MB_OK | MB_ICONERROR);

}