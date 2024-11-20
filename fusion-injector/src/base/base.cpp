#include "base.h"

#include "request/request.h"
#include "folder/folder.h"
#include "update/update.h"

Base::Base()
{
	window.Init(); // initialize the window
	FolderManager::GetFusionFolder(); // ensure the fusion folder exists
}

void Base::Run()
{
	while (window.Update()) // update the window
	{
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

bool BaseUtils::UpdateDll()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.clientVersion.empty() || info.clientDownloadUrl.empty())
		return false;

	return Update::UpdateDll("fusion-plus_v" + info.clientVersion + ".dll", info.clientDownloadUrl);
}

bool BaseUtils::UpdateInjector()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.injectorVersion.empty() || info.injectorDownloadUrl.empty())
		return false;

	return Update::UpdateInjector("fusion-plus_v" + info.injectorVersion + ".exe", info.injectorDownloadUrl);
}