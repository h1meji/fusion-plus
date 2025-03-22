#include "moduleManager.h"

#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/combat/leftAutoClicker.h"
#include "modules/combat/rightAutoClicker.h"
#include "modules/visual/esp.h"
#include "modules/visual/radar.h"
#include "modules/visual/nametag.h"
#include "modules/visual/blockEsp.h"
#include "modules/movement/bridgeAssist.h"
#include "modules/movement/velocity.h"
#include "modules/movement/sprintReset.h"
#include "modules/movement/sprint.h"
#include "modules/inventory/chestStealer.h"
#include "modules/inventory/inventorySorter.h"
#include "modules/utility/arrayList.h"
#include "modules/utility/clientBrandChanger.h"
#include "modules/utility/weapon.h"
//#include "modules/tnt-tag/tagBack.h"
//#include "modules/tnt-tag/ITEsp.h"
#include "commonData.h"

#include <configManager/configManager.h>
#include <imgui/imgui.h>

#include "util/minecraft/inventory.h"
#include <menu/menu.h>
#include <util/keys.h>


void ModuleManager::Init()
{
	modules.push_back(std::make_unique<AimAssist>());
	modules.push_back(std::make_unique<Reach>());
	modules.push_back(std::make_unique<LeftAutoClicker>());
	modules.push_back(std::make_unique<RightAutoClicker>());
	modules.push_back(std::make_unique<Esp>());
	modules.push_back(std::make_unique<Radar>());
	modules.push_back(std::make_unique<Nametag>());
	modules.push_back(std::make_unique<BlockEsp>());
	modules.push_back(std::make_unique<BridgeAssist>());
	modules.push_back(std::make_unique<Velocity>());
	modules.push_back(std::make_unique<SprintReset>());
	modules.push_back(std::make_unique<Sprint>());
	modules.push_back(std::make_unique<ChestStealer>());
	modules.push_back(std::make_unique<InventorySorter>());
	modules.push_back(std::make_unique<ArrayList>());
	modules.push_back(std::make_unique<ClientBrandChanger>());
	modules.push_back(std::make_unique<Weapon>());

	//modules.push_back(std::make_unique<TagBack>());
	//modules.push_back(std::make_unique<ITEsp>());
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

	// init inventory system
	InventorySystem::Init();

	// hook
	try {
		if (StrayCache::clientBrandRetriever_getClientModName != nullptr && ClientBrandChanger::getClientModName_callback != nullptr) {
			bool hookResult = JavaHook::hook(StrayCache::clientBrandRetriever_getClientModName, ClientBrandChanger::getClientModName_callback);
			Logger::Log(hookResult ? "Hooked ClientBrandRetriever.getClientModName" : "Failed to hook ClientBrandRetriever.getClientModName");
		} else {
			Logger::Log("Skipping ClientBrandRetriever hook - Invalid function pointers");
		}
	} catch (const std::exception& e) {
		Logger::Log("Error during hook initialization: %s", e.what());
	}
}

void ModuleManager::UpdateModules()
{
	CommonData::UpdateData();

	for (auto& module : modules)
	{
		// Keybinds
		if (module->GetKey() != 0 && Keys::IsKeyPressed(module->GetKey()))
		{
			module->Toggle();
		}

		if (module->IsEnabled())
			module->Update();
	}
}

void ModuleManager::RenderOverlay()
{
	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->RenderOverlay();
	}
}

void ModuleManager::RenderHud()
{
	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->RenderHud();
	}

	// Render Keybinds Window
	if (settings::Hud_ShowKeybinds)
	{
		ImGuiWindowFlags windowFlags;
		if (!Menu::OpenHudEditor)
		{
			windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs;
		}
		else
		{
			windowFlags = 0;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

		std::call_once(*Menu::setupKeybindsFlag, [&]() {
			ImGui::SetNextWindowPos(ImVec2(settings::Hud_KeybindsPosition[0], settings::Hud_KeybindsPosition[1]));
			});

		if (ImGui::Begin("Keybinds", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | windowFlags))
		{
			settings::Hud_KeybindsPosition[0] = ImGui::GetWindowPos().x;
			settings::Hud_KeybindsPosition[1] = ImGui::GetWindowPos().y;

			ImGui::PushFont(Menu::FontBold);
			ImGui::Text("Keybinds");
			ImGui::PopFont();

			for (auto& module : modules)
			{
				int key = module->GetKey();
				if (key != 0)
				{
					ImGui::Text("%s: %s", module->GetName().c_str(), Keys::GetKeyName(key));
				}
			}
		}
		ImGui::End();

		ImGui::PopStyleVar();
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