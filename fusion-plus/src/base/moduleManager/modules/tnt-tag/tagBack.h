#pragma once
#include "moduleManager/moduleBase.h"
#include "util/math/geometry.h"

class TagBack : public ModuleBase
{
public:
	Vector3 renderData;

	void Update() override;
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::TB_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	std::string Name = "Tag Back";
	std::string Category = "TnT Tag";

	Vector3 data;
	bool pitchInfluenced = false;

	long lastClickTime = 0;
	int nextCps = 10;
};

