#pragma once

#include <string>

#include "moduleManager/moduleBase.h"
#include "util/math/geometry.h"

class BridgeAssist : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::BA_Key; }

	bool IsEnabled() override { return settings::BA_Enabled; }
	void SetEnabled(bool enabled) override { settings::BA_Enabled = enabled; }
	void Toggle() override { settings::BA_Enabled = !settings::BA_Enabled; }

private:
	std::string m_name = "Bridge Assist";
	std::string m_category = "Movement";

	void Sneak();
	void UnSneak();

	Vector3 m_from = Vector3();
	const Vector3 m_direction = Vector3(0, -1e6, 0);

	bool m_isEdge = false;
	bool m_prev = false;

	bool m_hasPressedShift = false;

	bool m_isBridging = false;
};
