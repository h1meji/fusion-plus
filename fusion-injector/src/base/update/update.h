#pragma once

#include <windows.h>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace Update
{
	struct UpdateInfo
	{
		std::string clientVersion;
		std::string clientDownloadUrl;
		std::string injectorVersion;
		std::string injectorDownloadUrl;
	};

	static std::string oldDllPath = "";

	UpdateInfo GetUpdateInfo(const std::string& url);
	bool UpdateDll(const std::string& fileName, const std::string& downloadUrl, const std::string& oldPath, const std::string& dllPath = "");
	bool UpdateInjector(const std::string& fileName, const std::string& downloadUrl, const std::string& injectorPath = "");

	bool CompareVersions(const int currentVersion[3], const int jsonVersion[3]);
	bool CompareVersions(const std::string& currentVersion, const std::string& jsonVersion);
}