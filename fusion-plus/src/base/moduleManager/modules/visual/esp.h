#pragma once
#include "util/math/geometry.h"

#include <vector>
#include <string>

#include "moduleManager/moduleBase.h"

class Esp : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::ESP_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	struct Data {
		std::vector<Vector3> boxVerticies;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
		float health;
		float maxHealth;
		std::vector<Vector3> boundingBoxVerticies;;
	};

private:
	std::string Name = "ESP";
	std::string Category = "Visual";

	std::vector<Data> renderData;
};