#pragma once

#include "moduleManager/moduleBase.h"

class WTap : public ModuleBase
{
public:
	void Update() override;

	void RenderUpdate() override {};
	void RenderMenu() override;

	bool IsEnabled() override { return settings::WTap_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "W-Tap";
	std::string Category = "Combat";

	int lastHurtResistantTime = 0;
	bool wTapInAction = false;
	int timeSinceLetGoW = 0;
	bool can_wtap = true;
};