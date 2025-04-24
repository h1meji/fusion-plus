#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

class ArrayList : public ModuleBase
{
public:
	void Update() override {}

	void RenderOverlay() override {};
	void RenderHud() override;
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::AL_Key; }

	bool IsEnabled() override { return settings::AL_Enabled; }
	void SetEnabled(bool enabled) override { settings::AL_Enabled = enabled; }
	void Toggle() override { settings::AL_Enabled = !settings::AL_Enabled; }

private:
	std::string m_name = "Array List";
	std::string m_category = "Utility";
};