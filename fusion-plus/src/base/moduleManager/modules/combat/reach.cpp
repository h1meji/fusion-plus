#include "reach.h"
#include "sdk/sdk.h"
#include "moduleManager/commonData.h"
#include "util/logger/logger.h"
#include "java/java.h"
#include "util/math/math.h"
#include "imgui/imgui.h"
#include "menu/menu.h"
#include "patcher/patcher.h"

#include <chrono>


//https://github.com/Lefraudeur/RiptermsGhost

std::chrono::steady_clock::time_point lastUpdate;
void Reach::Update()
{
	if (Java::Version != MinecraftVersion::LUNAR_1_8_9)
	{
		if (settings::Reach_Enabled)
		{
			settings::Reach_Enabled = false;
			Logger::Log("Reach is only supported on Lunar CLient 1.8.9");
		}
		return;
	}

	static float prev_reach = -1.0f;
	if (!settings::Reach_Enabled)
	{
		if (!CommonData::SanityCheck()) return;
		if (prev_reach != -1.0f)
		{
			Patcher::put("reach_distance", "3.0");
			prev_reach = -1.0f;
		}
		return;
	}
	if (prev_reach == settings::Reach_ReachDistance || !CommonData::SanityCheck())
		return;
	prev_reach = settings::Reach_ReachDistance;
	Patcher::put("reach_distance", std::to_string(settings::Reach_ReachDistance));
}


void Reach::RenderMenu()
{
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("reach_header", ImVec2(425, renderSettings ? 73 : 35), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(16, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::Reach_Enabled);
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
	//		if (ImGui::BeginChild("reach_settings", ImVec2(425, 28), false))
	//		{
	//			Menu::KeybindButton(167, "Keybind", ImVec2(297, 0), settings::Reach_Key);
	//			Menu::Slider(17, "Reach Distance", ImVec2(225, 0), &settings::Reach_ReachDistance, 0, 4);
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
