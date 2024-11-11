#pragma once
#include "util/math/geometry.h"

#include <string>
#include <vector>

#include "moduleManager/moduleBase.h"

class Reach : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return settings::Reach_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Reach";
	std::string Category = "Combat";
};

