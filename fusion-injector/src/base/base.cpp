#include "base.h"

#include "request/request.h"
#include "folder/folder.h"
#include "update/update.h"

Base::Base()
{
	window.Init(); // initialize the window
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

bool Base::UpdateDll()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.clientVersion.empty() || info.clientDownloadUrl.empty())
		return false;

	if (!Update::CompareVersions(FolderManager::GetVersionStringDll(), FolderManager::GetVersionStringDll()))
		return true;

	return Update::UpdateDll("fusion-plus_v" + info.clientVersion + ".dll", info.clientDownloadUrl);
}

bool Base::UpdateInjector()
{
	Update::UpdateInfo info = Update::GetUpdateInfo("https://pastebin.com/raw/ZvJ2wmif");

	if (info.injectorVersion.empty() || info.injectorDownloadUrl.empty())
		return false;

	if (!Update::CompareVersions(INJECTOR_VERSION, info.injectorVersion))
		return true;

	return Update::UpdateInjector("fusion-plus_v" + info.injectorVersion + ".exe", info.injectorDownloadUrl);
}