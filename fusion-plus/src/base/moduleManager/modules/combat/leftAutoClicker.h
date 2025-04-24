#pragma once

#include "moduleManager/moduleBase.h"

class LeftAutoClicker : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::LAC_Key; }

	bool IsEnabled() override { return settings::LAC_Enabled; }
	void SetEnabled(bool enabled) override { settings::LAC_Enabled = enabled; }
	void Toggle() override { settings::LAC_Enabled = !settings::LAC_Enabled; }

private:
	std::string m_name = "Left Auto Clicker";
	std::string m_category = "Combat";

	long m_lastClickTime = 0;
	int m_nextCps = 10;
	bool m_shouldDrop = false;
	bool m_shouldSpike = false;

	float m_normalCps = 0.0f;
	float m_lastKurtosisValue = 0.0f;
};

