#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>

#include "../../moduleBase.h"

class Esp : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override;

	void RenderMenu() override;

	bool IsEnabled() override { return Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	struct Data {
		std::vector<Vector3> boxVerticies;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
		float health;
		float maxHealth;
	};

private:
	bool Enabled = true;
	std::string Name = "ESP";
	std::string Category = "Visual";

	std::vector<Data> renderData;

	bool Box = true;
	float BoxColor[4]{ 0, 0, 0, 1 };

	bool FilledBox = true;
	float FilledBoxColor[3]{ 0, 0, 0 };
	float SecondFilledBoxColor[3]{ 0, 0, 0 };
	float FilledBoxOpacity = 0.15f;

	bool Outline = true;
	float OutlineColor[4]{ 0, 0, 0, 0.25 };

	bool Text = true;
	float TextSize = 18;
	float TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	bool TextOutline = true;
	float TextOutlineColor[4]{ 0, 0, 0, 1.0f };
	float TextUnrenderDistance = 14.0f;

	float FadeDistance = 3.0f;

	bool HealthBar = true;
};