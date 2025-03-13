#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

class Weapon : public ModuleBase
{
public:
	void Update() override {};
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return true; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Weapon";
	std::string Category = "Utility";
};