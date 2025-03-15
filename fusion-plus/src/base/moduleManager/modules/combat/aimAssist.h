#pragma once
#include "util/math/geometry.h"

#include <string>
#include <vector>

#include "moduleManager/moduleBase.h"

class AimAssist : public ModuleBase
{
public:
	Vector3 renderData;

	void Update() override;

	void RenderOverlay() override;
	void RenderHud() override {};
	void RenderMenu() override;

	bool IsEnabled() override { return settings::AA_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::AA_Key; }

	void SetEnabled(bool enabled) override { settings::AA_Enabled = enabled; }
	void Toggle() override { settings::AA_Enabled = !settings::AA_Enabled; }

private:
	std::string Name = "Aim Assist";
	std::string Category = "Combat";

	Vector3 data;
	bool pitchInfluenced = false;
};

