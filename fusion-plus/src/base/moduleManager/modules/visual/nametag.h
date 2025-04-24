#pragma once

#include "moduleManager/moduleBase.h"
#include "util/math/geometry.h"

class Nametag : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override;
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::NT_Key; }

	bool IsEnabled() override { return settings::NT_Enabled; }
	void SetEnabled(bool enabled) override { settings::NT_Enabled = enabled; }
	void Toggle() override { settings::NT_Enabled = !settings::NT_Enabled; }

private:
	std::string m_name = "Nametags";
	std::string m_category = "Visual";

	struct Data
	{
		std::vector<Vector3> boxVerticies;
		std::vector<Vector3> boundingBoxVerticies;
		std::string name;
		std::string distText;
		std::string healthText;
		std::string invisbleText;
		float dist;
		float opacityFadeFactor;
	};

	std::vector<Data> m_nametagData;
};