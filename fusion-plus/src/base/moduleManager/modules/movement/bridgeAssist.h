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

	bool IsEnabled() override { return settings::BA_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return 0; }

private:
	void Sneak();
	void UnSneak();

	Vector3 m_from;
	const Vector3 m_direction = Vector3(0, -1e6, 0);

	bool m_is_edge = false;
	bool m_prev = false;

	bool m_has_pressed_shift = false;

	bool m_is_bridging = false;

private:
	std::string Name = "Bridge Assist";
	std::string Category = "Movement";
};
