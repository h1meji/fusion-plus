#include "radar.h"
#include <moduleManager/commonData.h>
#include <imgui/imgui.h>
#include "menu/menu.h"
#include <util/math/math.h>
#include "util/window/windowHelpers.h"
#include <configManager/configManager.h>
#include <imgui/imgui_internal.h>

void Radar::Update()
{
	if (!settings::Radar_Enabled)
	{
		renderData.clear();
		return;
	}
	if (!CommonData::SanityCheck())
	{
		renderData.clear();
		return;
	}

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	CWorld* world = SDK::Minecraft->theWorld;
	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty())
	{
		renderData.clear();
		return;
	}

	Vector3 pos = player->GetPos();
	playerYaw = player->GetRotationYaw();

	std::vector<Data> newData;

	for (CommonData::PlayerData entity : playerList)
	{
		bool isLocalPlayer = entity.pos == pos;

		Vector3 diff = pos - entity.pos;
		float dist = sqrt(pow(diff.x, 2.f) + pow(diff.y, 2.f) + pow(diff.z, 2.f)); // Sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
		// Regular distance check.
		if (dist > settings::Radar_Radius) {
			continue;
		}

		newData.push_back(Data{
			isLocalPlayer,
			entity.name,
			dist,
			Vector2(diff.x, diff.z)
		});
	}
	renderData = newData;
}

void Radar::RenderHud()
{
	if (!settings::Radar_Enabled) return;

	std::call_once(*Menu::setupRadarFlag, []() {
		ImGui::SetNextWindowPos(ImVec2(settings::Radar_Position[0], settings::Radar_Position[1]));
		ImGui::SetNextWindowSize(ImVec2(settings::Radar_Size, settings::Radar_Size));
		});


	// Set window background and rounding
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(settings::Radar_BackgroundColor[0], settings::Radar_BackgroundColor[1], settings::Radar_BackgroundColor[2], settings::Radar_BackgroundColor[3]));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, settings::Radar_SquareRoundness);

	ImGuiWindowFlags windowFlags;
	if (!Menu::OpenHudEditor)
	{
		windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoResize;
	}
	else
	{
		windowFlags = 0;
	}

	static AspectRatioData aspectData(1.f, 1.f);
	WindowHelpers::SetFixedAspectRatio(&aspectData);

	ImGui::Begin("RaderHudWindow", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | windowFlags);
	{
		settings::Radar_Position[0] = ImGui::GetWindowPos().x;
		settings::Radar_Position[1] = ImGui::GetWindowPos().y;
		settings::Radar_Size = ImGui::GetWindowSize().x;

		ImVec2 zerozero = ImVec2(settings::Radar_Position[0] + settings::Radar_Size / 2, settings::Radar_Position[1] + settings::Radar_Size / 2);

		auto rotatePoint = [](float x, float y, float angle) -> ImVec2 {
			float rad = angle * (float)((float)PI / 180.f);
			float cosA = cos(rad);
			float sinA = sin(rad);
			return ImVec2(
				x * cosA - y * sinA,
				x * sinA + y * cosA
			);
			};

		ImVec2 localPlayerPos[3] = {};
		for (Data data : renderData)
		{
			float relX = data.relativePosition.x / settings::Radar_Radius * (settings::Radar_Size / 2);
			float relY = data.relativePosition.y / settings::Radar_Radius * (settings::Radar_Size / 2);

			ImVec2 radarPos(relX, relY);

			if (settings::Radar_RotateWithPlayer) {
				radarPos = rotatePoint(radarPos.x, radarPos.y, -playerYaw);
			}

			radarPos.x += zerozero.x;
			radarPos.y += zerozero.y;

			// if local player, draw a triangle instead of a square.
			if (data.isLocalPlayer) {
				// Draw player triangle
				ImVec2 p1 = ImVec2(0, -5);
				ImVec2 p2 = ImVec2(-5, 5);
				ImVec2 p3 = ImVec2(5, 5);

				// Rotate triangle points
				if (!settings::Radar_RotateWithPlayer) {
					p1 = rotatePoint(p1.x, p1.y, playerYaw);
					p2 = rotatePoint(p2.x, p2.y, playerYaw);
					p3 = rotatePoint(p3.x, p3.y, playerYaw);
				}

				// Translate triangle to radar position
				p1.x += radarPos.x; p1.y += radarPos.y;
				p2.x += radarPos.x; p2.y += radarPos.y;
				p3.x += radarPos.x; p3.y += radarPos.y;

				localPlayerPos[0] = p1;
				localPlayerPos[1] = p2;
				localPlayerPos[2] = p3;
			}
			else {
				ImColor playerColor = ImColor(settings::Radar_PlayerColor[0], settings::Radar_PlayerColor[1], settings::Radar_PlayerColor[2], settings::Radar_PlayerColor[3]);
				ImColor friendColor = ImColor(settings::Radar_FriendColor[0], settings::Radar_FriendColor[1], settings::Radar_FriendColor[2], settings::Radar_FriendColor[3]);

				// Draw other players as squares
				ImGui::GetWindowDrawList()->AddRectFilled(
					ImVec2(radarPos.x - 2.5f, radarPos.y - 2.5f),
					ImVec2(radarPos.x + 2.5f, radarPos.y + 2.5f),
					ConfigManager::IsFriend(data.name) ? friendColor : playerColor
				);

				// Show names if enabled
				if (settings::Radar_ShowNames) {
					ImVec2 textSize = ImGui::CalcTextSize(data.name.c_str());
					ImGui::GetWindowDrawList()->AddText(
						ImVec2(radarPos.x - textSize.x / 2, radarPos.y + 5),
						ImColor(255, 255, 255, 255),
						data.name.c_str()
					);
				}
			}
		}

		ImGui::GetWindowDrawList()->AddTriangleFilled(localPlayerPos[0], localPlayerPos[1], localPlayerPos[2], ImColor(settings::Radar_LocalPlayerColor[0], settings::Radar_LocalPlayerColor[1], settings::Radar_LocalPlayerColor[2], settings::Radar_LocalPlayerColor[3]));
	}
	ImGui::End();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Radar::RenderMenu()
{
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("radar_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(52, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::Radar_Enabled);
	//	ImGui::EndGroup();
	//	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	//	{
	//		renderSettings = !renderSettings;
	//	}

	//	ImGui::PopStyleColor();
	//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

	//	if (renderSettings)
	//	{
	//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//		ImGui::Separator();
	//		if (ImGui::BeginChild("radar_settings", ImVec2(425, 215), false))
	//		{
	//			Menu::KeybindButton(180, "Keybind", ImVec2(297, 0), settings::Radar_Key);
	//			Menu::Slider(53, "Radius", ImVec2(225, 0), &settings::Radar_Radius, 0.0f, 300.0f);
	//			Menu::ToggleButton(54, "Rotate with Player", ImVec2(368, 0), &settings::Radar_RotateWithPlayer);
	//			Menu::ToggleButton(55, "Show Names", ImVec2(368, 0), &settings::Radar_ShowNames);

	//			ImGui::SeparatorText("UI Settings");

	//			Menu::Slider(56, "Size", ImVec2(225, 0), &settings::Radar_Size, 100.0f, 1000.0f);
	//			Menu::Slider(57, "Square Roundness", ImVec2(225, 0), &settings::Radar_SquareRoundness, 0.0f, 100.0f);
	//			Menu::Slider(58, "Position X", ImVec2(225, 0), &settings::Radar_Position[0], 0.0f, 1920.0f);
	//			Menu::Slider(59, "Position Y", ImVec2(225, 0), &settings::Radar_Position[1], 0.0f, 1080.0f);
	//			Menu::ColorPicker(60, "Local Player Color", ImVec2(374, 0), settings::Radar_LocalPlayerColor);
	//			Menu::ColorPicker(61, "Player Color", ImVec2(374, 0), settings::Radar_PlayerColor);
	//			Menu::ColorPicker(62, "Friend Color", ImVec2(374, 0), settings::Radar_FriendColor);
	//			Menu::ColorPicker(63, "Background Color", ImVec2(374, 0), settings::Radar_BackgroundColor);
	//		}
	//		ImGui::EndChild();
	//		ImGui::Spacing();
	//	}
	//}
	//ImGui::EndChild();

	//ImGui::PopStyleVar();
	//ImGui::PopStyleColor();

	//ImGui::EndGroup();
}