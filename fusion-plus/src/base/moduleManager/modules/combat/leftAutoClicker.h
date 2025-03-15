#pragma once

#include "moduleManager/moduleBase.h"

class LeftAutoClicker : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::LAC_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return 0; }

	void SetEnabled(bool enabled) override { settings::LAC_Enabled = enabled; }
	void Toggle() override { settings::LAC_Enabled = !settings::LAC_Enabled; }

private:
	std::string Name = "Left Auto Clicker";
	std::string Category = "Combat";
};

