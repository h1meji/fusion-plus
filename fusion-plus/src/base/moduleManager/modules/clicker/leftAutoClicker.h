#pragma once

#include "moduleManager/moduleBase.h"

class LeftAutoClicker : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return settings::LAC_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Left Auto Clicker";
	std::string Category = "Clicker";
};

