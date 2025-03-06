#include "main.h"

#include <fstream>
#include <exception>

static LONG WINAPI GlobalExceptionHandler(EXCEPTION_POINTERS* pException)
{
	Base::WriteCrashReport(pException);
	return EXCEPTION_EXECUTE_HANDLER;
}

void Main::Init()
{
	Base::Init();
}

void Main::Kill()
{
	Base::Kill();
	FreeLibraryAndExitThread(Main::HModule, 0);
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Main::HModule = hModule;
		DisableThreadLibraryCalls(hModule);
		SetUnhandledExceptionFilter(GlobalExceptionHandler);
		HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main::Init), hModule, 0, nullptr);

		if (hThread) CloseHandle(hThread);
	}

	return TRUE;
}