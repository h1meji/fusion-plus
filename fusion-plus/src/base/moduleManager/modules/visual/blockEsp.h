#pragma once
#include "util/math/geometry.h"

#include <vector>
#include <string>

#include "moduleManager/moduleBase.h"

class BlockEsp : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override;
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::BlockESP_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return 0; }

	void SetEnabled(bool enabled) override { settings::BlockESP_Enabled = enabled; }
	void Toggle() override { settings::BlockESP_Enabled = !settings::BlockESP_Enabled; }

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