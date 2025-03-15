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

private:
	std::string Name = "Right Auto Clicker";
	std::string Category = "Combat";
};

