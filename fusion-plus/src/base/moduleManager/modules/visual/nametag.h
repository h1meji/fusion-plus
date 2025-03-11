#pragma once

#include "moduleManager/moduleBase.h"
#include <util/math/geometry.h>

class Nametag : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::NT_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	struct Data {
		std::vector<Vector3> boxVerticies;
		std::vector<Vector3> boundingBoxVerticies;
		std::string name;
		std::string distText;
		std::string healthText;
		std::string invisbleText;
		float dist;
		float opacityFadeFactor;
	};

private:
	std::string Name = "Nametags";
	std::string Category = "Visual";

	std::vector<Data> nametagData;
};