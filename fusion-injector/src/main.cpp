#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>

#include "base/request/request.h"
#include "../ext/nlohmann/json.hpp"

using json = nlohmann::json;

bool IsUpToDate(const int currentVersion[3], const int jsonVersion[3]) {
    for (int i = 0; i < 3; ++i) {
        if (currentVersion[i] > jsonVersion[i]) {
            return true; // Current version is higher
        }
        else if (currentVersion[i] < jsonVersion[i]) {
            return false; // JSON version is higher
        }
        // If equal, continue to the next part of the version
    }
    return true; // Versions are identical
}

bool EnsureDirectoryExists(const std::string& path) {
    if (!std::filesystem::exists(path)) {  // Using C++17 filesystem
        if (!CreateDirectoryA(path.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    }
    return true;
}

std::string GetProgramFilesPathWithFolder(const std::string& subFolder = "Fusion+") {
    char path[MAX_PATH];

    // Get the Program Files folder
    if (SHGetFolderPathA(NULL, CSIDL_PROGRAM_FILES, NULL, 0, path) == S_OK) {
        std::string fullPath = std::string(path) + "\\" + subFolder;

        // Ensure the folder exists if a subfolder was specified
        if (!subFolder.empty() && !EnsureDirectoryExists(fullPath)) {
            std::cerr << "Could not create folder: " << fullPath << std::endl;
            return "";
        }

        return fullPath;
    }
    else {
        std::cerr << "Failed to get Program Files folder." << std::endl;
        return "";
    }
}

int main()
{
	std::string programFilesPath = GetProgramFilesPathWithFolder();
	if (programFilesPath.empty()) {
		return 1;
	}

    std::wstring url = L"https://pastebin.com/raw/ZvJ2wmif";
    std::string response = Request::Get(url);

	json j = json::parse(response);

    if (!response.empty()) {
        std::cout << "Response:\n" << response << "\n";
		std::cout << "> Version: " << j["version"].get<std::string>() << "\n";
		std::cout << "> URL: " << j["url"].get<std::string>() << "\n";
    }
    else {
        std::cout << "Failed to fetch data.\n";
        return 1;
    }

    // Check if the version in the JSON is newer than the version extracted from fusion-plus_v#.#.#.dll
    std::string currentDll;
    for (const auto& entry : std::filesystem::directory_iterator(programFilesPath))
    {
        if (entry.path().extension() == ".dll")
		{
			currentDll = entry.path().filename().string();
			break;
		}
    }

	if (currentDll.empty()) {
		std::cerr << "No DLL files found in the directory: " << programFilesPath << std::endl;
	}
    else
    {
        std::string currentVersion = currentDll.substr(currentDll.find_last_of("_") + 1);
		currentVersion = currentVersion.substr(0, currentVersion.find_last_of("."));
        std::string jsonVersion = j["version"].get<std::string>();

		std::cout << "Current version: " << currentVersion << "\n";
		std::cout << "JSON version: " << jsonVersion << "\n";

		// Extract the version numbers from the strings and compare them
		int currentVersionNumber[3] = { 0, 0, 0 };
		int jsonVersionNumber[3] = { 0, 0, 0 };

		sscanf_s(currentVersion.c_str(), "v%d.%d.%d", &currentVersionNumber[0], &currentVersionNumber[1], &currentVersionNumber[2]);
		sscanf_s(jsonVersion.c_str(), "v%d.%d.%d", &jsonVersionNumber[0], &jsonVersionNumber[1], &jsonVersionNumber[2]);

		std::cout << "Current version: " << currentVersionNumber[0] << "." << currentVersionNumber[1] << "." << currentVersionNumber[2] << "\n";
		std::cout << "JSON version: " << jsonVersionNumber[0] << "." << jsonVersionNumber[1] << "." << jsonVersionNumber[2] << "\n";

		if (IsUpToDate(currentVersionNumber, jsonVersionNumber)) {
			std::cout << "The current version is up to date.\n";
			return 0;
		}
        else {
            std::cout << "A new version is available.\n";

			// Delete the old DLL file
			std::wstring oldFilePath = std::wstring(programFilesPath.begin(), programFilesPath.end()) + L"\\fusion-plus_" + std::wstring(currentVersion.begin(), currentVersion.end()) + L".dll";
            if (DeleteFile(oldFilePath.c_str())) {
                std::wcout << L"Deleted old file: " << oldFilePath << L"\n";
			}
            else {
                std::wcout << L"Failed to delete old file: " << oldFilePath << L"\n";
            }
        }
    }

    std::string jsonUrl = j["url"].get<std::string>();
	std::string jsonVersion = j["version"].get<std::string>();

	url = std::wstring(jsonUrl.begin(), jsonUrl.end());
    std::wstring filePath = std::wstring(programFilesPath.begin(), programFilesPath.end()) + L"\\fusion-plus_" + std::wstring(jsonVersion.begin(), jsonVersion.end()) + L".dll";

    if (Request::DownloadToFile(url, filePath)) {
        std::wcout << L"File downloaded successfully to " << filePath << L"\n";
    }
    else {
        std::wcout << L"Failed to download the file.\n";
    }

    return 0;
}