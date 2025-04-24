#pragma once

#include "moduleManager/moduleBase.h"

class RightAutoClicker : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::RAC_Key; }

	bool IsEnabled() override { return settings::RAC_Enabled; }
	void SetEnabled(bool enabled) override { settings::RAC_Enabled = enabled; }
	void Toggle() override { settings::RAC_Enabled = !settings::RAC_Enabled; }

private:
	std::string m_name = "Right Auto Clicker";
	std::string m_category = "Combat";

	long m_lastClickTime = 0;
	int m_nextCps = 10;
};

