#include "process.h"

#include <Psapi.h>
#include <string>
#include <TlHelp32.h>
#include <algorithm>

#include <iostream>

bool IsMinecraftProcess(DWORD processId) {
    auto hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    // Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if (!Module32First(hModuleSnap, &me32))
    {
        CloseHandle(hModuleSnap);
        return false;
    }

    // Check the module list of the process for jvm.dll or javaw.exe 
    do
    {
        if (wcscmp(me32.szModule, L"jvm.dll") == 0 || wcscmp(me32.szModule, L"javaw.exe") == 0)
            return true;
    } while (Module32Next(hModuleSnap, &me32));

    // We haven't found jvm.dll or javaw.exe in the process module list 
    CloseHandle(hModuleSnap);
    return false;
}

bool ProcessManager::GetMinecraftProcesses(std::vector<WindowInfo>& processes)
{
	ProcessManager::_processes.clear();
	processes.clear();

	// Enumerate all windows and check if they belong to a Minecraft process
	EnumWindows([](HWND hwnd, LPARAM lparam) -> BOOL {
		DWORD PID = 0;
		GetWindowThreadProcessId(hwnd, &PID);

		const static DWORD TITLE_SIZE = 1024;
		CHAR windowTitle[TITLE_SIZE];
		GetWindowTextA(hwnd, windowTitle, TITLE_SIZE);
		const int win_name_length = GetWindowTextLength(hwnd);

		if (IsWindowVisible(hwnd) && win_name_length != 0) {
			// convert window title to std::string
			auto title = std::string(windowTitle);

			if (IsMinecraftProcess(PID))
			{
				ProcessManager::_processes.emplace_back(PID, title, hwnd);
			}

			return TRUE;
		}

		return TRUE;
		}, NULL);

	// sort processes by process name
	std::sort(ProcessManager::_processes.begin(), ProcessManager::_processes.end(), [](const WindowInfo& a, const WindowInfo& b) {
		return a.processName < b.processName;
		});

	processes = ProcessManager::_processes;
    return true;
}

bool ProcessManager::InjectDLL(DWORD processId, const char* dllPath)
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (hProcess == NULL) {
		return false; // ! could not open process
    }

    // Allocate memory for the DLL path in the target process
    LPVOID allocatedMemory = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (allocatedMemory == NULL) {
        CloseHandle(hProcess);
		return false; // ! could not allocate memory in target process
    }

    // Write the DLL path to the allocated memory
    if (!WriteProcessMemory(hProcess, allocatedMemory, dllPath, strlen(dllPath) + 1, NULL)) {
        VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
        CloseHandle(hProcess);
		return false; // ! could not write memory in target process
    }

    // Get the address of LoadLibraryA
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    if (loadLibraryAddr == NULL) {
        VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
        CloseHandle(hProcess);
		return false; // ! could not get address of LoadLibraryA
    }

    // Create a remote thread to inject the DLL
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, allocatedMemory, 0, NULL);
    if (hThread == NULL) {
        VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
        CloseHandle(hProcess);
		return false; // ! could not create remote thread
    }

    // Wait for the remote thread to finish and clean up
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    VirtualFreeEx(hProcess, allocatedMemory, 0, MEM_RELEASE);
    CloseHandle(hProcess);

    return true;
}
