#pragma once

#include <string>
#include <vector>

#include <util/math/geometry.h>
#include "moduleManager/moduleBase.h"

class Radar : public ModuleBase
{
public:
	void Update() override;
	void RenderOverlay() override {};
	void RenderHud() override;

	void RenderMenu() override;

	bool IsEnabled() override { return settings::Radar_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::Radar_Key; }

	void SetEnabled(bool enabled) override { settings::Radar_Enabled = enabled; }
	void Toggle() override { settings::Radar_Enabled = !settings::Radar_Enabled; }

	struct Data {
		bool isLocalPlayer;
		std::string name;
		float dist;
		Vector2 relativePosition;
	};
	
private:
	std::string Name = "Radar";
	std::string Category = "Visual";

	std::vector<Data> renderData;
	float playerYaw = -1.f;
};