#include "base.h"

#include <thread>

#include "request/request.h"
#include "folder/folder.h"
#include "update/update.h"
#include <iostream>

Base::Base()
{
	window.Init(); // initialize the window
	FolderManager::GetFusionFolder(); // ensure the fusion folder exists
}

void Base::Run()
{
	while (window.Update()) // update the window
	{
		// sleep for 1ms to reduce CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void Base::Cleanup()
{
	window.Cleanup(); // cleanup the window
}

bool BaseUtils::IsDllUpdated()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.clientVersion.empty())
		return false;

	std::string currentVersion = FolderManager::GetVersionStringDll();
	if (currentVersion.empty())
		return false;

	return Update::CompareVersions(FolderManager::GetVersionStringDll(), info.clientVersion);
}

bool BaseUtils::IsInjectorUpdated()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.injectorVersion.empty())
		return false;

	return Update::CompareVersions(INJECTOR_VERSION, info.injectorVersion);
}

bool BaseUtils::UpdateDll(std::string oldPath)
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.clientVersion.empty() || info.clientDownloadUrl.empty())
		return false;

	return Update::UpdateDll("fusion-plus_v" + info.clientVersion + ".dll", info.clientDownloadUrl, oldPath);
}

bool BaseUtils::UpdateInjector()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.injectorVersion.empty() || info.injectorDownloadUrl.empty())
		return false;

	return Update::UpdateInjector("fusion-plus_v" + info.injectorVersion + ".exe", info.injectorDownloadUrl);
}