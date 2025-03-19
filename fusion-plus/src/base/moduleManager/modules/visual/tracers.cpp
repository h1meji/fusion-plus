#include "tracers.h"
#include <imgui/imgui.h>
#include <menu/menu.h>
#include "moduleManager/commonData.h"
#include <util/math/worldToScreen.h>
#include <util/math/math.h>

#define M_PI 3.14159265358979323846

void Tracers::Update()
{
	if (!settings::Tracers_Enabled) return;
	if (!CommonData::SanityCheck()) return;

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	CWorld* world = SDK::Minecraft->theWorld;
	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	Vector3 renderPos = CommonData::renderPos;
	Vector3 pos = player->GetPos();
	std::string name = player->GetName();

	if (CommonData::thirdPersonView != 0) {
		Vector3 cameraPos = CWorldToScreen::GetCameraPosition(CommonData::modelView);
		Vector2 angles = player->GetAngles();
		float eyeHeight = player->IsSneaking() ? 1.54f : 1.62f;

		Vector3 relativeEyePosToPlayer = { 0, eyeHeight, 0 };
		cameraPos = cameraPos - relativeEyePosToPlayer;

		float distance = sqrt(cameraPos.x * cameraPos.x + cameraPos.y * cameraPos.y + cameraPos.z * cameraPos.z) * 2;

		if (CommonData::thirdPersonView == 2) {
			distance = -distance;
		}

		// This whole calculation came from gaspers source from their reach module, which you can find in this cheat as well
		float cos = std::cos(Math::degToRadiants(angles.x + 90.0f));
		float sin = std::sin(Math::degToRadiants(angles.x + 90.0f));
		float cosPitch = std::cos(Math::degToRadiants(angles.y));
		float sinPitch = std::sin(Math::degToRadiants(angles.y));

		float x = renderPos.x - (cos * distance * cosPitch);
		float y = renderPos.y + (distance * sinPitch);
		float z = renderPos.z - (sin * distance * cosPitch);

		// The raycast that is commented out below does not work that well for some reason, acts weirdly when colliding with chests, and other things.
		// Also might be poor in performance.
		//Vector3 ray = world->rayTraceBlocks(renderPos, Vector3{ x, y, z }, false, false, false);
		//renderPos = ray.x == 0 ? Vector3{ x,y,z } : ray;

		renderPos = Vector3{ x,y,z };
	}

	float renderPartialTicks = CommonData::renderPartialTicks;

	std::vector<Vector3> newData;
	for (CommonData::PlayerData entity : playerList)
	{
		if (entity.name == name) continue;

		Vector3 entityPos = entity.pos;
		Vector3 entityLastPos = entity.lastPos;

		Vector3 diff = pos - entityPos;
		float dist = sqrt(pow(diff.x, 2.f) + pow(diff.y, 2.f) + pow(diff.z, 2.f));
		// Regular distance check.
		if (dist > 300) {
			continue;
		}

		Vector3 feet{ renderPos - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; feet.y -= entity.height + 0.1f; // At the feet
		Vector3 body{ feet.x, feet.y + (entity.height / 2), feet.z }; // At the body
		Vector3 head{ feet.x, feet.y + entity.height, feet.z }; // At the head

		switch (settings::Tracers_Position)
		{
		case 0:
			newData.push_back(feet);
			break;
		case 1:
			newData.push_back(body);
			break;
		case 2:
			newData.push_back(head);
			break;
		default:
			newData.push_back(body);
			break;
		}
	}
	tracerData = newData;
}

void Tracers::RenderOverlay()
{
	if (!settings::Tracers_Enabled || !CommonData::dataUpdated) return;
	if (tracerData.empty()) return;

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	if (!player) return;

	Vector2 playerAngles = player->GetAngles();
	if (playerAngles.x == NAN || playerAngles.y == NAN) return;

	for (Vector3 pos : tracerData)
	{
		ImVec2 screenSize = ImGui::GetWindowSize();
		Vector2 screenPos;
		bool onScreen = CWorldToScreen::WorldToScreen(pos, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, screenPos);
		if (onScreen)
		{
			if (screenPos.x == NAN) return;

			ImColor color = ImColor(settings::Tracers_Color[0], settings::Tracers_Color[1], settings::Tracers_Color[2], settings::Tracers_Color[3]);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(screenPos.x, screenPos.y), color, settings::Tracers_Thickness);
		}
		else
		{
			Vector2 angles = Math::getAngles(CommonData::renderPos, pos);
			Logger::Log("Angles: %f %f", angles.x, angles.y);
			Vector2 anglesDiff = angles - playerAngles;
			Logger::Log("Angles Diff: %f %f", anglesDiff.x, anglesDiff.y);

			float x = anglesDiff.x;
			float y = anglesDiff.y;

			float angle = atan2(y, x) * 180 / M_PI;
			Logger::Log("Angle: %f", angle);

			float x2 = cos(angle * M_PI / 180) * 100;
			float y2 = sin(angle * M_PI / 180) * 100;

			ImColor color = ImColor(settings::Tracers_Color[0], settings::Tracers_Color[1], settings::Tracers_Color[2], settings::Tracers_Color[3]);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(screenSize.x / 2 + x2, screenSize.y / 2 + y2), color, settings::Tracers_Thickness);
		}
	}
}

void Tracers::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("tracers_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(180, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::Tracers_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			if (ImGui::BeginChild("tracers_settings", ImVec2(425, 215), false))
			{
				Menu::KeybindButton(181, "Keybind", ImVec2(297, 0), settings::Tracers_Key);
				Menu::ComboBox(182, "Type", ImVec2(270, 0), &settings::Tracers_Type, settings::Tracers_TypeList, 2);
				Menu::ComboBox(183, "Position", ImVec2(270, 0), &settings::Tracers_Position, settings::Tracers_PositionList, 3);
				Menu::Slider(184, "Thickness", ImVec2(225, 0), &settings::Tracers_Thickness, 1.f, 5.f);
				Menu::ToggleButton(185, "Off Screen Only", ImVec2(368, 0), &settings::Tracers_OffScreenOnly);
				Menu::ColorPicker(186, "Color", ImVec2(374, 0), settings::Tracers_Color);
			}
			ImGui::EndChild();
			ImGui::Spacing();
		}
	}
	ImGui::EndChild();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	ImGui::EndGroup();
}
