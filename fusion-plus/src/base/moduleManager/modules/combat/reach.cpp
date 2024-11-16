#include "reach.h"
#include "sdk/sdk.h"
#include "moduleManager/commonData.h"
#include "util/logger.h"
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
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("reach", ImVec2(425, renderSettings ? 75 : 35)))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(230044, "Toggle Reach", &settings::Reach_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			Menu::DoSliderStuff(560117, "Reach Distance", &settings::Reach_ReachDistance, 0, 4);
			ImGui::Spacing();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
