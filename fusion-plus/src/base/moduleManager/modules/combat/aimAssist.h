#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

#include "../../moduleBase.h"

class AimAssist : public ModuleBase
{
public:
	Vector3 renderData;

	void Update() override;

	void RenderUpdate() override;
	void RenderMenu() override;

	bool IsEnabled() override { return Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

private:
	bool Enabled = false;
	std::string Name = "Aim Assist";
	std::string Category = "Combat";

	bool visibilityCheck = true;
	bool aimAssistFeedback = true;
	bool fovCircle = true;

	Vector3 data;
	bool pitchInfluenced = false;
	bool aimKey = true;

	bool adaptive = true;
	float adaptiveOffset = 3;

	float fov = 35.0f;
	float smooth = 15.f;
	float aimDistance = 4.f;
	float randomYaw = 2;
	float randomPitch = .075f;

	int targetPriority = 2;
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
};

