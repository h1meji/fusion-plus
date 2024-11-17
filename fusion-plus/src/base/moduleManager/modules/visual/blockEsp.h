#pragma once
#include "util/math/geometry.h"

#include <vector>
#include <string>

#include "moduleManager/moduleBase.h"

class BlockEsp : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::BlockESP_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	struct Data {
		Vector3 position;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
	};

private:
	std::string Name = "Block ESP";
	std::string Category = "Visual";

	std::vector<Data> renderData;

	int range = 20;
};