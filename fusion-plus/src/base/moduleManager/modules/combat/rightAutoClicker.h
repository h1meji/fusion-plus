#pragma once

#include "moduleManager/moduleBase.h"

class RightAutoClicker : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::RAC_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::RAC_Key; }

	void SetEnabled(bool enabled) override { settings::RAC_Enabled = enabled; }
	void Toggle() override { settings::RAC_Enabled = !settings::RAC_Enabled; }

private:
	std::string Name = "Right Auto Clicker";
	std::string Category = "Combat";
};

