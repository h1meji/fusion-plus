#pragma once
#include "util/math/geometry.h"

#include <string>
#include <vector>

#include "moduleManager/moduleBase.h"

class Reach : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::Reach_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::Reach_Key; }

	void SetEnabled(bool enabled) override { settings::Reach_Enabled = enabled; }
	void Toggle() override { settings::Reach_Enabled = !settings::Reach_Enabled; }

private:
	std::string Name = "Reach";
	std::string Category = "Combat";
};

