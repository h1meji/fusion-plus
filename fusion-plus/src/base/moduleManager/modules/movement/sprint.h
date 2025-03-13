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

    bool IsEnabled() override { return settings::S_Enabled; }
    std::string GetName() override { return Name; }
    std::string GetCategory() override { return Category; }

private:
    std::string Name = "Sprint";
    std::string Category = "Movement";
};