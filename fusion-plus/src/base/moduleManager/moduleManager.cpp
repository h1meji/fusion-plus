#include "moduleManager.h"

#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/combat/wTap.h"
#include "modules/combat/leftAutoClicker.h"
#include "modules/combat/rightAutoClicker.h"
#include "modules/visual/esp.h"
#include "modules/visual/radar.h"
#include "modules/visual/blockEsp.h"
#include "modules/movement/bridgeAssist.h"
#include "modules/movement/velocity.h"
#include "modules/utility/arrayList.h"
#include "modules/inventory/chestStealer.h"
#include "modules/tnt-tag/tagBack.h"
#include "modules/tnt-tag/ITEsp.h"
#include "commonData.h"

#include <configManager/configManager.h>
#include <imgui/imgui.h>

void ModuleManager::Init()
{
	modules.push_back(std::make_unique<AimAssist>());
	modules.push_back(std::make_unique<Reach>());
	modules.push_back(std::make_unique<WTap>());
	modules.push_back(std::make_unique<LeftAutoClicker>());
	modules.push_back(std::make_unique<RightAutoClicker>());
	modules.push_back(std::make_unique<Esp>());
	modules.push_back(std::make_unique<Radar>());
	modules.push_back(std::make_unique<BlockEsp>());
	modules.push_back(std::make_unique<ArrayList>());
	modules.push_back(std::make_unique<BridgeAssist>());
	modules.push_back(std::make_unique<Velocity>());
	modules.push_back(std::make_unique<ChestStealer>());

	modules.push_back(std::make_unique<TagBack>());
	modules.push_back(std::make_unique<ITEsp>());
	Logger::Log("Modules initialized");

	// load friends
	ConfigManager::LoadFriends();
	Logger::Log("Friends loaded");

	// load the first config
	std::vector<std::string> configList = ConfigManager::GetConfigList();
	if (!configList.empty())
	{
		ConfigManager::LoadConfig(configList[0].c_str());
		Logger::Log("Config loaded: %s", configList[0].c_str());
	}
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

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);

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