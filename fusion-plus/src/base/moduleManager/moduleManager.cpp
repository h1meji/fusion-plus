#include "moduleManager.h"

#include "modules/visual/esp.h"
#include "modules/visual/arrayList.h"
#include "modules/visual/radar.h"
#include "modules/visual/blockEsp.h"
#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/combat/wTap.h"
#include "modules/clicker/leftAutoClicker.h"
#include "modules/clicker/rightAutoClicker.h"
#include "modules/movement/bridgeAssist.h"
#include "modules/tnt-tag/tagBack.h"
#include "commonData.h"

#include <configManager/configManager.h>

void ModuleManager::Init()
{
	modules.push_back(std::make_unique<Esp>());
	modules.push_back(std::make_unique<ArrayList>());
	modules.push_back(std::make_unique<Radar>());
	modules.push_back(std::make_unique<BlockEsp>());
	modules.push_back(std::make_unique<AimAssist>());
	modules.push_back(std::make_unique<Reach>());
	modules.push_back(std::make_unique<WTap>());
	modules.push_back(std::make_unique<LeftAutoClicker>());
	modules.push_back(std::make_unique<RightAutoClicker>());
	modules.push_back(std::make_unique<BridgeAssist>());
	modules.push_back(std::make_unique<TagBack>());

	// load friends
	ConfigManager::LoadFriends();

	// load the first config
	std::vector<std::string> configList = ConfigManager::GetConfigList();
	if (!configList.empty())
		ConfigManager::LoadConfig(configList[0].c_str());
}

void ModuleManager::UpdateModules()
{
	CommonData::UpdateData();

	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->Update();
	}
}

void ModuleManager::RenderUpdate()
{
	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->RenderUpdate();
	}
}

void ModuleManager::RenderMenu(int index)
{
	if (index < 0)
		return;

	std::vector<std::string> categories = GetCategories();
	for (auto& module : modules)
	{
		if (module->GetCategory() == categories[index])
			module->RenderMenu();
	}
}

std::vector<std::string> ModuleManager::GetCategories()
{
	std::vector<std::string> categories;

	for (auto& module : modules)
	{
		if (std::find(categories.begin(), categories.end(), module->GetCategory()) == categories.end())
			categories.push_back(module->GetCategory());
	}

	return categories;
}