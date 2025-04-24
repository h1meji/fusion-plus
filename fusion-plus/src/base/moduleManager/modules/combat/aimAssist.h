#pragma once

#include <string>
#include <vector>

#include "moduleManager/moduleBase.h"
#include "util/math/geometry.h"

class AimAssist : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override;
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::AA_Key; }

	bool IsEnabled() override { return settings::AA_Enabled; }
	void SetEnabled(bool enabled) override { settings::AA_Enabled = enabled; }
	void Toggle() override { settings::AA_Enabled = !settings::AA_Enabled; }

private:
	std::string m_name = "Aim Assist";
	std::string m_category = "Combat";

	Vector3 m_data = Vector3();
	bool m_pitchInfluenced = false;
};

