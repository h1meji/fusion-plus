#pragma once

#include <string>
#include <vector>

#include "util/math/geometry.h"
#include "moduleManager/moduleBase.h"

class Radar : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override;
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::Radar_Key; }

	bool IsEnabled() override { return settings::Radar_Enabled; }
	void SetEnabled(bool enabled) override { settings::Radar_Enabled = enabled; }
	void Toggle() override { settings::Radar_Enabled = !settings::Radar_Enabled; }
	
private:
	std::string m_name = "Radar";
	std::string m_category = "Visual";

	struct Data
	{
		bool isLocalPlayer;
		std::string name;
		float dist;
		Vector2 relativePosition;
	};

	std::vector<Data> m_renderData;
	float m_playerYaw = -1.f;
};