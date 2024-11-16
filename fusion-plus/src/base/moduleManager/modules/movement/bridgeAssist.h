#pragma once

#include <string>

#include "moduleManager/moduleBase.h"

#include "util/math/geometry.h"

class BridgeAssist : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return settings::BA_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	void Sneak();
	void UnSneak();

	// parameters for the raytrace 
	Vector3 m_from;
	const Vector3 m_direction = Vector3(0, -1e6, 0);

	// true if player is on the egde of a block
	// m_prev will store the previous value of m_isEdge, this will help when player has entered or left an edge
	bool m_is_edge = false;
	bool m_prev = false;

	// used for block_esp::only_initiate_when_sneaking
	bool m_has_pressed_shift = false;

private:
	std::string Name = "Bridge Assist";
	std::string Category = "Movement";
};
