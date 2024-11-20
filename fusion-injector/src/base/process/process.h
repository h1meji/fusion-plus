#pragma once

#include <vector>
#include <Windows.h>
#include <string>

namespace ProcessManager
{
	struct WindowInfo
	{
		WindowInfo(DWORD processId, const std::string& processName, HWND hwnd)
			: processId(processId), processName(processName), hwnd(hwnd) {}
		DWORD processId;
		std::string processName;
		HWND hwnd;
	};

	bool GetMinecraftProcesses(std::vector<WindowInfo>& processes);
	bool InjectDLL(DWORD processId, const char* dllPath);
	std::string GetProcessName(DWORD processId);

	inline static std::vector<WindowInfo> _processes;
}