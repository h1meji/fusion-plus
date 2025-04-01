#include "blockEsp.h"
#include <moduleManager/commonData.h>
#include <imgui/imgui.h>
#include <menu/menu.h>
#include <util/math/worldToScreen.h>

void BlockEsp::Update()
{
	if (!settings::BlockESP_Enabled) return;
	if (!CommonData::SanityCheck()) return;

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	CWorld* world = SDK::Minecraft->theWorld;

	/*CBlockPos pos = CBlockPos(0, 64, 0);
	CBlock block = world->GetBlockState(pos).GetBlock();

	std::cout << block.GetBlockId() << std::endl;*/

	Vector3 lastTickPos = player->GetLastTickPos();
	Vector3 playerPosition = lastTickPos + (player->GetPos() - lastTickPos) * CommonData::renderPartialTicks;

	int xLimit = (int)playerPosition.x + range * 2;
	int yLimit = (int)playerPosition.y + range * 2;
	int zLimit = (int)playerPosition.z + range * 2;

	std::vector<Data> newRenderData;
	for (int x = (int)playerPosition.x - range; x < xLimit; x++)
	{
		for (int y = (int)playerPosition.y - range; y < yLimit; y++)
		{
			for (int z = (int)playerPosition.z - range; z < zLimit; z++)
			{
				CBlock block = world->GetBlock(x, y, z);

				if (block.GetBlockId() == 0 || block.GetBlockId() != settings::BlockESP_TargetID) continue;

				Vector3 blockPos = Vector3((float)x, (float)y, (float)z);

				std::cout << block.GetBlockId() << " found at " << blockPos.x << " " << blockPos.y << " " << blockPos.z << std::endl;

				float dist = playerPosition.Distance(blockPos);
				char distC[32];
				std::snprintf(distC, sizeof(distC), "%.1f", dist);
				std::string distS(distC);

				Data data;
				data.position = blockPos;
				data.name = "";//block.GetBlockName();
				data.dist = dist;
				data.distText = distS + "m";
				data.opacityFadeFactor = 0.0f;

				newRenderData.push_back(data);
			}
		}
	}
	renderData = newRenderData;
}

void BlockEsp::RenderOverlay()
{
	if (!settings::BlockESP_Enabled || !CommonData::dataUpdated) return;

	for (Data data : renderData)
	{
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 p;
		if (!CWorldToScreen::WorldToScreen(data.position, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, p))
		{
			continue;
		}
	}
}

void BlockEsp::RenderMenu()
{
	//return;
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("besp_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(28374, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::BlockESP_Enabled);
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
	//		if (ImGui::BeginChild("besp_settings", ImVec2(425, 215), false))
	//		{
	//			Menu::KeybindButton(178, "Keybind", ImVec2(297, 0), settings::BlockESP_Key);
	//			Menu::Slider(45363, "Target ID", ImVec2(225, 0), &settings::BlockESP_TargetID, 1, 1000);
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
