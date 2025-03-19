#pragma once

#include <string>
#include <vector>

#include <util/math/geometry.h>
#include "moduleManager/moduleBase.h"

class Tracers : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override;
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::Tracers_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::Tracers_Key; }

	void SetEnabled(bool enabled) override { settings::Tracers_Enabled = enabled; }
	void Toggle() override { settings::Tracers_Enabled = !settings::Tracers_Enabled; }

private:
	std::string Name = "Tracers";
	std::string Category = "Visual";

	std::vector<Vector3> tracerData;
};