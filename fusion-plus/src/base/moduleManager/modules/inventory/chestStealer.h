#pragma once

#include <string>
#include <vector>
#include <chrono>

#include <imgui/imgui.h>

#include "moduleManager/moduleBase.h"

class ChestStealer : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::CS_Key; }
	
	bool IsEnabled() override { return settings::CS_Enabled; }
	void SetEnabled(bool enabled) override { settings::CS_Enabled = enabled; }
	void Toggle() override { settings::CS_Enabled = !settings::CS_Enabled; }

private:
	std::string m_name = "Chest Stealer";
	std::string m_category = "Inventory";

	bool m_isStealing = false;
	std::chrono::time_point<std::chrono::steady_clock> m_lastStealTime;
	std::chrono::time_point<std::chrono::steady_clock> m_activated;
	std::vector<int> m_chestSlots;
	int m_chestSlotIndex = 0;

	void ResetSteal();
	void RenderItems(ImVec2 pos);
};