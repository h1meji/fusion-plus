#pragma once

#include <chrono>

#include "moduleManager/moduleBase.h"

class SprintReset : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::SR_Key; }

	bool IsEnabled() override { return settings::SR_Enabled; }
	void SetEnabled(bool enabled) override { settings::SR_Enabled = enabled; }
	void Toggle() override { settings::SR_Enabled = !settings::SR_Enabled; }

private:
	std::string m_name = "Sprint Reset";
	std::string m_category = "Movement";

	bool m_sprintResetInAction = false;
	bool m_canSprintReset = true;

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	std::chrono::time_point<std::chrono::steady_clock> m_pauseTime;
};