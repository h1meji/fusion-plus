#pragma once

#include <string>

namespace FolderManager
{
	std::string GetFusionFolder();
	std::string GetConfigsFolder();

	bool EnsureDirectoryExists(const std::string& path);
	std::string GetProgramFilesFolder(const std::string& subFolder);

	std::string GetVersionStringDll();
}