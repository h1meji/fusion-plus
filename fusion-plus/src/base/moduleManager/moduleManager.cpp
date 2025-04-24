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

#include "commonData.h"
#include "configManager/configManager.h"
#include "util/minecraft/inventory.h"
#include "util/keys.h"
#include "menu/menu.h"


void ModuleManager::Init()
{
	m_modules.push_back(std::make_unique<AimAssist>());
	m_modules.push_back(std::make_unique<Reach>());
	m_modules.push_back(std::make_unique<LeftAutoClicker>());
	m_modules.push_back(std::make_unique<RightAutoClicker>());
	m_modules.push_back(std::make_unique<Esp>());
	m_modules.push_back(std::make_unique<Radar>());
	m_modules.push_back(std::make_unique<Nametag>());
	m_modules.push_back(std::make_unique<BridgeAssist>());
	m_modules.push_back(std::make_unique<Velocity>());
	m_modules.push_back(std::make_unique<SprintReset>());
	m_modules.push_back(std::make_unique<Sprint>());
	m_modules.push_back(std::make_unique<ChestStealer>());
	m_modules.push_back(std::make_unique<ArrayList>());
	m_modules.push_back(std::make_unique<ClientBrandChanger>());
	m_modules.push_back(std::make_unique<Weapon>());
	LOG_INFO("Modules initialized");

	// load friends
	configmanager::LoadFriends();
	LOG_INFO("Friends loaded");

	// load the first config
	std::vector<std::string> configList = configmanager::GetConfigList();
	if (!configList.empty())
	{
		configmanager::LoadConfig(0);
		LOG_INFO("Config loaded: %s", configList[0].c_str());
	}

	// init inventory system
	InventorySystem::Init();

	// hook
	try
	{
		if (StrayCache::clientBrandRetriever_getClientModName != nullptr && ClientBrandChanger::GetClientModName_callback != nullptr)
		{
			bool hookResult = JavaHook::Hook(StrayCache::clientBrandRetriever_getClientModName, ClientBrandChanger::GetClientModName_callback);
			LOG_INFO(hookResult ? "Hooked ClientBrandRetriever.getClientModName" : "Failed to hook ClientBrandRetriever.getClientModName");
		} 
		else
		{
			LOG_INFO("Skipping ClientBrandRetriever hook - Invalid function pointers");
		}
	}
	catch (const std::exception& e)
	{
		LOG_INFO("Error during hook initialization: %s", e.what());
	}
}

void ModuleManager::UpdateModules()
{
	CommonData::UpdateData();

	for (auto& module : m_modules)
	{
		// Keybinds
		if (module->GetKey() != 0 && Keys::IsKeyPressedOnce(module->GetKey()) && !Menu::open)
		{
			module->Toggle();
		}

		if (module->IsEnabled())
		{
			module->Update();
		}
	}
}

void ModuleManager::RenderOverlay()
{
	for (auto& module : m_modules)
	{
		if (module->IsEnabled())
		{
			module->RenderOverlay();
		}
	}
}

void ModuleManager::RenderHud()
{
	for (auto& module : m_modules)
	{
		if (module->IsEnabled())
		{
			module->RenderHud();
		}
	}

	// Render Keybinds Window
	if (settings::Hud_ShowKeybinds)
	{
		ImGuiWindowFlags windowFlags;
		if (!Menu::openHudEditor)
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

			Menu::BoldText("Keybinds", FontSize::SIZE_18);
			Menu::HorizontalSeparator("KeybindsSeparator");

			for (auto& module : m_modules)
			{
				int key = module->GetKey();
				if (key != 0)
				{
					Menu::Text((module->GetName() + " : " + Keys::GetKeyName(key)).c_str(), FontSize::SIZE_16);
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
	for (auto& module : m_modules)
	{
		if (module->GetCategory() == categories[index])
		{
			module->RenderMenu();
		}
	}
}

std::vector<std::string> ModuleManager::GetCategories()
{
	std::vector<std::string> categories;

	for (auto& module : m_modules)
	{
		if (std::find(categories.begin(), categories.end(), module->GetCategory()) == categories.end())
		{
			categories.push_back(module->GetCategory());
		}
	}

	return categories;
}

int ModuleManager::GetFirstModuleIndexByCategory(const std::string& category)
{
	for (int i = 0; i < m_modules.size(); i++)
	{
		if (m_modules[i]->GetCategory() == category)
		{
			return i;
		}
	}

	return -1;
}
