#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

#include "../../moduleBase.h"

class Reach : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	bool Enabled = false;
	std::string Name = "Reach";
	std::string Category = "Combat";

	float ReachDistance = 3.0f;
};

