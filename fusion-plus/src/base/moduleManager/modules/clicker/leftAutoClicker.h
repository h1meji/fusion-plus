#pragma once

#include "../../moduleBase.h"

class LeftAutoClicker : public ModuleBase
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
	std::string Name = "Left Auto Clicker";
	std::string Category = "Clicker";

	float leftMaxCps = 14;
	float leftMinCps = 8;
	bool ignoreBlocks = true;
};

