#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

#include "util/math/geometry.h"

#include <random>
inline int rand_int(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

class Velocity : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::Velocity_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::Velocity_Key; }

	void SetEnabled(bool enabled) override { settings::Velocity_Enabled = enabled; }
	void Toggle() override { settings::Velocity_Enabled = !settings::Velocity_Enabled; }

private:
	std::string Name = "Velocity";
	std::string Category = "Movement";
};