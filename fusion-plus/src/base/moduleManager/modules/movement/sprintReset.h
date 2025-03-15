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

	bool IsEnabled() override { return settings::SR_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::SR_Key; }

	void SetEnabled(bool enabled) override { settings::SR_Enabled = enabled; }
	void Toggle() override { settings::SR_Enabled = !settings::SR_Enabled; }

private:
	std::string Name = "Sprint Reset";
	std::string Category = "Movement";

	bool sprintResetInAction = false;
	bool can_sprint_reset = true;

	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::chrono::time_point<std::chrono::steady_clock> pauseTime;
};