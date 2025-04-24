#pragma once

#include <vector>
#include <string>

#include "util/math/geometry.h"
#include "moduleManager/moduleBase.h"

class Esp : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override;
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::ESP_Key; }

	bool IsEnabled() override { return settings::ESP_Enabled; }
	void SetEnabled(bool enabled) override { settings::ESP_Enabled = enabled; }
	void Toggle() override { settings::ESP_Enabled = !settings::ESP_Enabled; }

private:
	std::string m_name = "ESP";
	std::string m_category = "Visual";

	struct Data
	{
		std::vector<Vector3> boxVerticies;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
		float health;
		float maxHealth;
		std::vector<Vector3> boundingBoxVerticies;;
	};

	std::vector<Data> m_renderData;
};