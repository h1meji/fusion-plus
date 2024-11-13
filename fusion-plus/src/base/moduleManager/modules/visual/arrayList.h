#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

class ArrayList : public ModuleBase
{
public:
	void Update() override {}
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::AL_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Array List";
	std::string Category = "Visual";
};