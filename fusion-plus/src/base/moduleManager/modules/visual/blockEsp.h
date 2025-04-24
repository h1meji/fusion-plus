#pragma once

#include <vector>
#include <string>

#include "util/math/geometry.h"
#include "moduleManager/moduleBase.h"

class BlockEsp : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override;
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::BlockESP_Key; }

	bool IsEnabled() override { return settings::BlockESP_Enabled; }
	void SetEnabled(bool enabled) override { settings::BlockESP_Enabled = enabled; }
	void Toggle() override { settings::BlockESP_Enabled = !settings::BlockESP_Enabled; }

private:
	std::string m_name = "Block ESP";
	std::string m_category = "Visual";

	struct Data
	{
		Vector3 position;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
	};

	std::vector<Data> m_renderData;

	int m_range = 20;
};