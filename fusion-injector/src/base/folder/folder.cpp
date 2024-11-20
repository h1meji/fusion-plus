#include "folder.h"

#include <windows.h>
#include <filesystem>
#include <shlobj.h>

bool FolderManager::EnsureDirectoryExists(const std::string& path)
{
    if (!std::filesystem::exists(path)) {
        if (!CreateDirectoryA(path.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            return false; // ! directory creation failed
        }
    }
    return true;
}

std::string FolderManager::GetProgramFilesFolder(const std::string& subFolder)
{
    char path[MAX_PATH];

    if (SHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES, NULL, 0, path) == S_OK) {
        std::string fullPath = std::string(path) + "\\" + subFolder;

        if (!subFolder.empty() && !FolderManager::EnsureDirectoryExists(fullPath)) {
			return ""; // ! directory creation failed
        }

        return fullPath;
    }
    else {
		return ""; // ! failed to get "Program Files" folder
    }
}

std::string FolderManager::GetDllPath()
{
	return GetFusionFolder() + "\\fusion-plus_v" + GetVersionStringDll() + ".dll";
}

std::string FolderManager::GetVersionStringDll()
{
    std::string currentDll;
    for (const auto& entry : std::filesystem::directory_iterator(GetFusionFolder()))
    {
        if (entry.path().extension() == ".dll" && entry.path().filename().string().starts_with("fusion-plus"))
        {
            currentDll = entry.path().filename().string();
            break;
        }
    }

	if (currentDll.empty())
	{
		return ""; // ! no dll found
	}

    std::string currentVersion = currentDll.substr(currentDll.find_last_of("v") + 1);
    currentVersion = currentVersion.substr(0, currentVersion.find_last_of("."));
    return currentVersion;
}

std::string FolderManager::GetFusionFolder()
{
	return FolderManager::GetProgramFilesFolder("Fusion+");
}