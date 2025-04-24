#pragma once

#include <string>
#include <random>

#include "moduleManager/moduleBase.h"
#include "util/math/geometry.h"

class Velocity : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::Velocity_Key; }

	bool IsEnabled() override { return settings::Velocity_Enabled; }
	void SetEnabled(bool enabled) override { settings::Velocity_Enabled = enabled; }
	void Toggle() override { settings::Velocity_Enabled = !settings::Velocity_Enabled; }

private:
	std::string m_name = "Velocity";
	std::string m_category = "Movement";
};