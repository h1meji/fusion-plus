#include "update.h"

#include "request/request.h"
#include "folder/folder.h"

Update::UpdateInfo Update::GetUpdateInfo(const std::string& url)
{
	std::wstring convertedUrl = std::wstring(url.begin(), url.end());
	std::string response = Request::Get(convertedUrl);
	json j = json::parse(response);

	if (j.empty())
		return UpdateInfo();

	UpdateInfo info;

	info.clientVersion = j["client"]["version"];
	info.clientDownloadUrl = j["client"]["url"];
	info.injectorVersion = j["injector"]["version"];
	info.injectorDownloadUrl = j["injector"]["url"];

	return info;
}

bool Update::UpdateDll(const std::string& fileName, const std::string& downloadUrl, const std::string& dllPath)
{
	std::wstring convertedUrl = std::wstring(downloadUrl.begin(), downloadUrl.end());
	std::wstring convertedPath = std::wstring(dllPath.begin(), dllPath.end());
	std::wstring convertedFileName = std::wstring(fileName.begin(), fileName.end());

	if (convertedPath.empty())
	{
		std::string path = FolderManager::GetFusionFolder();
		convertedPath = std::wstring(path.begin(), path.end());
	}

	std::wstring fullPath = convertedPath + L"\\" + convertedFileName;

	return Request::DownloadToFile(convertedUrl, fullPath);
}

bool Update::UpdateInjector(const std::string& fileName, const std::string& downloadUrl, const std::string& injectorPath)
{
	std::wstring convertedUrl = std::wstring(downloadUrl.begin(), downloadUrl.end());
	
	std::wstring convertedPath;
	if (injectorPath.empty())
	{
		wchar_t buffer[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, buffer);
		std::wstring currentDirectory(buffer);
		convertedPath = currentDirectory;
	}
	else
	{
		convertedPath = std::wstring(injectorPath.begin(), injectorPath.end());
	}

	return Request::DownloadToFile(convertedUrl, convertedPath);
}

bool Update::CompareVersions(const int currentVersion[3], const int jsonVersion[3])
{
	for (int i = 0; i < 3; ++i) {
		if (currentVersion[i] > jsonVersion[i]) {
			return true; // current version is higher, no update needed
		}
		else if (currentVersion[i] < jsonVersion[i]) {
			return false; // json version is higher, update needed
		}
	}
	return true; // versions are identical, no update needed
}

bool Update::CompareVersions(const std::string& currentVersion, const std::string& jsonVersion)
{
	int current[3] = { 0, 0, 0 };
	int json[3] = { 0, 0, 0 };

	std::string currentVersionCopy = currentVersion;
	std::string jsonVersionCopy = jsonVersion;

	for (int i = 0; i < 3; ++i) {
		size_t pos = currentVersionCopy.find('.');
		current[i] = std::stoi(currentVersionCopy.substr(0, pos));
		currentVersionCopy.erase(0, pos + 1);

		pos = jsonVersionCopy.find('.');
		json[i] = std::stoi(jsonVersionCopy.substr(0, pos));
		jsonVersionCopy.erase(0, pos + 1);
	}

	return CompareVersions(current, json);
}
