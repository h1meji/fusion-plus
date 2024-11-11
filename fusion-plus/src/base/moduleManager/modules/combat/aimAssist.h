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

	void RenderUpdate() override;
	void RenderMenu() override;

	bool IsEnabled() override { return settings::AA_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Aim Assist";
	std::string Category = "Combat";

	Vector3 data;
	bool pitchInfluenced = false;
};

