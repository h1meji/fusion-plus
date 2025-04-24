#pragma once

#include <string>

#include "util/math/geometry.h"
#include "moduleManager/moduleBase.h"

class Reach : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::Reach_Key; }

	bool IsEnabled() override { return settings::Reach_Enabled; }
	void SetEnabled(bool enabled) override { settings::Reach_Enabled = enabled; }
	void Toggle() override { settings::Reach_Enabled = !settings::Reach_Enabled; }

private:
	std::string m_name = "Reach";
	std::string m_category = "Combat";
};

