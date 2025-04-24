#pragma once

#include <chrono>

#include "moduleManager/moduleBase.h"

class Sprint : public ModuleBase
{
public:
    void Update() override;

    void RenderOverlay() override {};
    void RenderHud() override {};
    void RenderMenu() override;

    std::string GetName() override { return m_name; }
    std::string GetCategory() override { return m_category; }
    int GetKey() override { return settings::S_Key; }

    bool IsEnabled() override { return settings::S_Enabled; }
	void SetEnabled(bool enabled) override { settings::S_Enabled = enabled; }
	void Toggle() override { settings::S_Enabled = !settings::S_Enabled; }

private:
    std::string m_name = "Sprint";
    std::string m_category = "Movement";

    bool m_isHoldingCtrl = false;
};