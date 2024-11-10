#pragma once

#include "../../moduleBase.h"

class RightAutoClicker : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	bool Enabled = false;
	std::string Name = "Right Auto Clicker";
	std::string Category = "Clicker";

	float rightMaxCps = 20;
	float rightMinCps = 15;
	bool blocksOnly = true;
};

