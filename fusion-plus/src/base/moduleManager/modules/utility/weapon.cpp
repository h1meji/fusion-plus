#include "weapon.h"
#include <imgui/imgui.h>
#include <menu/menu.h>

void Weapon::RenderMenu()
{
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("weapon_header", ImVec2(425.f, renderSettings ? 170.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::Text(141, this->GetName().c_str(), ImVec2(368, 0), true);
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
	//		if (ImGui::BeginChild("weapon_settings", ImVec2(425, 125), false))
	//		{
	//			Menu::Text(142, "Select the items you consider weapons.", ImVec2(368, 0), false);
	//			Menu::ToggleButton(143, "Swords", ImVec2(368, 0), &settings::Weapon_Sword);
	//			Menu::ToggleButton(144, "Axes", ImVec2(368, 0), &settings::Weapon_Axe);
	//			Menu::ToggleButton(145, "Sticks", ImVec2(368, 0), &settings::Weapon_Stick);
	//			Menu::ToggleButton(146, "Fists", ImVec2(368, 0), &settings::Weapon_Fist);
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
