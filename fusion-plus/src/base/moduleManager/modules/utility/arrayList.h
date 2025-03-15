#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

class ArrayList : public ModuleBase
{
public:
	void Update() override {}
	void RenderOverlay() override {};
	void RenderHud() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::AL_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return 0; }

	void SetEnabled(bool enabled) override { settings::AL_Enabled = enabled; }
	void Toggle() override { settings::AL_Enabled = !settings::AL_Enabled; }

private:
	std::string Name = "Array List";
	std::string Category = "Utility";
};