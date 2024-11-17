#include "radar.h"
#include <moduleManager/commonData.h>
#include <imgui/imgui.h>
#include "menu/menu.h"
#include <util/math/math.h>

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
		float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2)); // Sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
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

void Radar::RenderUpdate()
{
	if (!settings::Radar_Enabled) return;

	ImVec2 screenSize = ImGui::GetWindowSize();
	float widthRatio = screenSize.x / 1920;
	float heightRatio = screenSize.y / 1080;
	ImVec2 zerozero = ImVec2(settings::Radar_Position[0] * widthRatio + settings::Radar_Size / 2, settings::Radar_Position[1] * heightRatio + settings::Radar_Size / 2);
	if (settings::Radar_Square)
	{
		// Draw square
		ImGui::GetWindowDrawList()->AddRectFilled(
			ImVec2(settings::Radar_Position[0], settings::Radar_Position[1]),
			ImVec2(settings::Radar_Position[0] + settings::Radar_Size, settings::Radar_Position[1] + settings::Radar_Size),
			ImColor(settings::Radar_BackgroundColor[0], settings::Radar_BackgroundColor[1], settings::Radar_BackgroundColor[2], settings::Radar_BackgroundColor[3])
		);
	}
	else
	{
		// Draw circle
		ImGui::GetWindowDrawList()->AddCircleFilled(
			ImVec2(settings::Radar_Position[0] + (settings::Radar_Size / 2), settings::Radar_Position[1] + (settings::Radar_Size / 2)),
			settings::Radar_Size / 2,
			ImColor(settings::Radar_BackgroundColor[0], settings::Radar_BackgroundColor[1], settings::Radar_BackgroundColor[2], settings::Radar_BackgroundColor[3])
		);
	}

	auto rotatePoint = [](float x, float y, float angle) -> ImVec2 {
		float rad = angle * (PI / 180);
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
			//// Draw triangle
			//ImGui::GetWindowDrawList()->AddTriangleFilled(
			//	ImVec2(zerozero.x, zerozero.y - 5),
			//	ImVec2(zerozero.x - 5, zerozero.y + 5),
			//	ImVec2(zerozero.x + 5, zerozero.y + 5),
			//	ImColor(255, .5 * 255, 0, 255)
			//);
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
			//// Draw square
			//ImGui::GetWindowDrawList()->AddRectFilled(
			//	ImVec2(zerozero.x + data.relativePosition.x / settings::Radar_Radius * (settings::Radar_Size / 2) - 2.5, zerozero.y + data.relativePosition.y / settings::Radar_Radius * (settings::Radar_Size / 2) - 2.5),
			//	ImVec2(zerozero.x + data.relativePosition.x / settings::Radar_Radius * (settings::Radar_Size / 2) + 2.5, zerozero.y + data.relativePosition.y / settings::Radar_Radius * (settings::Radar_Size / 2) + 2.5),
			//	ImColor(255, 0, 0, 255)
			//);
			//if (settings::Radar_ShowNames)
			//{
			//	ImVec2 textSize = ImGui::CalcTextSize(data.name.c_str());
			//	ImGui::GetWindowDrawList()->AddText(
			//		ImVec2(zerozero.x + data.relativePosition.x / settings::Radar_Radius * (settings::Radar_Size / 2) - textSize.x / 2, (zerozero.y + 10) + data.relativePosition.y / settings::Radar_Radius * (settings::Radar_Size / 2) - textSize.y / 2),
			//		ImColor(255, 255, 255, 255),
			//		data.name.c_str()
			//	);
			//}
			// Draw other players as squares
			ImGui::GetWindowDrawList()->AddRectFilled(
				ImVec2(radarPos.x - 2.5, radarPos.y - 2.5),
				ImVec2(radarPos.x + 2.5, radarPos.y + 2.5),
				ImColor(settings::Radar_PlayerColor[0], settings::Radar_PlayerColor[1], settings::Radar_PlayerColor[2], settings::Radar_PlayerColor[3])
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

void Radar::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("radar", ImVec2(425, renderSettings ? 181 : 35))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(28374, "Toggle Radar", &settings::Radar_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();

			Menu::DoSliderStuff(3948573, "Radius", &settings::Radar_Radius, 0.0f, 300.0f);

			Menu::DoToggleButtonStuff(345643, "Rotate with Player", &settings::Radar_RotateWithPlayer);

			Menu::DoToggleButtonStuff(34732744, "Show Names", &settings::Radar_ShowNames);

			ImGui::SeparatorText("UI Settings");

			Menu::DoSliderStuff(47346, "Size", &settings::Radar_Size, 100.0f, 1000.0f);

			Menu::DoToggleButtonStuff(37365, "Square", &settings::Radar_Square);

			Menu::DoSliderStuff(845353, "Position X", &settings::Radar_Position[0], 0.0f, 1920.0f);

			Menu::DoSliderStuff(8356745, "Position Y", &settings::Radar_Position[1], 0.0f, 1080.0f);

			Menu::DoColorPickerStuff(3434685, "Local Player Color", settings::Radar_LocalPlayerColor);

			Menu::DoColorPickerStuff(37685, "Player Color", settings::Radar_PlayerColor);

			Menu::DoColorPickerStuff(3454745, "Background Color", settings::Radar_BackgroundColor);

			ImGui::Spacing();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}