#pragma once

#include <string>

namespace FolderManager
{
	std::string GetFusionFolder();
	std::string GetConfigsFolder();

	bool EnsureDirectoryExists(const std::string& path);
	std::string GetDocumentsPath(const std::string& subFolder);

	std::string GetDllPath();

	std::string GetVersionStringDll();

	std::string GetCurrentDir();
}