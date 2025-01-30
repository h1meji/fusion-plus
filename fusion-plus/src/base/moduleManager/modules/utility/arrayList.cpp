#include "arrayList.h"

#include <imgui/imgui.h>
#include "menu/menu.h"
#include "moduleManager/commonData.h"

// Modules
#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/visual/radar.h"
#include "moduleManager/modules/visual/blockEsp.h"
#include "moduleManager/modules/combat/aimAssist.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/combat/wTap.h"
#include "moduleManager/modules/combat/leftAutoClicker.h"
#include "moduleManager/modules/combat/rightAutoClicker.h"
#include "moduleManager/modules/movement/bridgeAssist.h"
#include "moduleManager/modules/movement/velocity.h"
#include "moduleManager/modules/inventory/chestStealer.h"
#include "moduleManager/modules/inventory/inventorySorter.h"
#include "moduleManager/modules/tnt-tag/tagBack.h"
#include "moduleManager/modules/tnt-tag/ITEsp.h"

void ArrayList::RenderUpdate()
{
	if (!settings::AL_Enabled) return;

	std::vector<std::string> enabledModules;

	if (Esp().IsEnabled()) enabledModules.push_back(Esp().GetName());
	if (Radar().IsEnabled()) enabledModules.push_back(Radar().GetName());
	if (BlockEsp().IsEnabled()) enabledModules.push_back(BlockEsp().GetName());
	if (AimAssist().IsEnabled()) enabledModules.push_back(AimAssist().GetName());
	if (Reach().IsEnabled()) enabledModules.push_back(Reach().GetName());
	if (WTap().IsEnabled()) enabledModules.push_back(WTap().GetName());
	if (LeftAutoClicker().IsEnabled()) enabledModules.push_back(LeftAutoClicker().GetName());
	if (RightAutoClicker().IsEnabled()) enabledModules.push_back(RightAutoClicker().GetName());
	if (BridgeAssist().IsEnabled()) enabledModules.push_back(BridgeAssist().GetName());
	if (Velocity().IsEnabled()) enabledModules.push_back(Velocity().GetName());
	if (ChestStealer().IsEnabled()) enabledModules.push_back(ChestStealer().GetName());
	if (InventorySorter().IsEnabled()) enabledModules.push_back(InventorySorter().GetName());
	if (TagBack().IsEnabled()) enabledModules.push_back(TagBack().GetName());
	if (ITEsp().IsEnabled()) enabledModules.push_back(ITEsp().GetName());

	// sort string length
	std::sort(enabledModules.begin(), enabledModules.end(), [](const std::string& a, const std::string& b) { return Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, a.c_str()).x > Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, b.c_str()).x; });

	// render
	int textHeight = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, enabledModules[0].c_str()).y + (2 * settings::AL_backgroundPadding);
	switch (settings::AL_renderPosition)
	{
	case 0: // Top Left
		for (int i = 0; i < enabledModules.size(); i++)
		{
			const char* name = enabledModules[i].c_str();
			ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);

			ImVec2 pos_min = ImVec2(0, (textHeight * i));
			ImVec2 pos_max = ImVec2(textSize.x + (2 * settings::AL_backgroundPadding), textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
			ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]));
			ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::AL_textSize, ImVec2(settings::AL_backgroundPadding, settings::AL_backgroundPadding + (textHeight * i)), ImColor(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]), name);
		}
		break;
	case 1: // Top Right
		for (int i = 0; i < enabledModules.size(); i++)
		{
			const char* name = enabledModules[i].c_str();
			ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);

			ImVec2 pos_min = ImVec2(ImGui::GetWindowSize().x - textSize.x - (2 * settings::AL_backgroundPadding), (textHeight * i));
			ImVec2 pos_max = ImVec2(ImGui::GetWindowSize().x, textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
			ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]));
			ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::AL_textSize, ImVec2(ImGui::GetWindowSize().x - textSize.x - settings::AL_backgroundPadding, settings::AL_backgroundPadding + (textHeight * i)), ImColor(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]), name);
		}
		break;
	case 2: // Bottom Left
		for (int i = 0; i < enabledModules.size(); i++)
		{
			const char* name = enabledModules[i].c_str();
			ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);

			ImVec2 pos_min = ImVec2(0, ImGui::GetWindowSize().y - textSize.y - (2 * settings::AL_backgroundPadding) - (textHeight * i));
			ImVec2 pos_max = ImVec2(textSize.x + (2 * settings::AL_backgroundPadding), textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
			ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]));
			ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::AL_textSize, ImVec2(settings::AL_backgroundPadding, ImGui::GetWindowSize().y - textSize.y - settings::AL_backgroundPadding - (textHeight * i)), ImColor(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]), name);
		}
		break;
	case 3: // Bottom Right
		for (int i = 0; i < enabledModules.size(); i++)
		{
			const char* name = enabledModules[i].c_str();
			ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::AL_textSize, FLT_MAX, 0.0f, name);

			ImVec2 pos_min = ImVec2(ImGui::GetWindowSize().x - textSize.x - (2 * settings::AL_backgroundPadding), ImGui::GetWindowSize().y - textSize.y - (2 * settings::AL_backgroundPadding) - (textHeight * i));
			ImVec2 pos_max = ImVec2(ImGui::GetWindowSize().x, textSize.y + (2 * settings::AL_backgroundPadding) + pos_min.y);
			ImGui::GetWindowDrawList()->AddRectFilled(pos_min, pos_max, ImColor(settings::AL_backgroundColor[0], settings::AL_backgroundColor[1], settings::AL_backgroundColor[2], settings::AL_backgroundColor[3]));
			ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::AL_textSize, ImVec2(ImGui::GetWindowSize().x - textSize.x - settings::AL_backgroundPadding, ImGui::GetWindowSize().y - textSize.y - settings::AL_backgroundPadding - (textHeight * i)), ImColor(settings::AL_textColor[0], settings::AL_textColor[1], settings::AL_textColor[2], settings::AL_textColor[3]), name);
		}
		break;
	}
}

void ArrayList::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("al_header", ImVec2(425, renderSettings ? 185 : 35), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(80, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::AL_Enabled);
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
			if (ImGui::BeginChild("al_settings", ImVec2(425, 140), false))
			{
				Menu::ComboBox(81, "Position", ImVec2(270, 0), &settings::AL_renderPosition, settings::AL_renderPositionList, 4);
				Menu::Slider(82, "Text Size", ImVec2(225, 0), &settings::AL_textSize, 1, 50);
				Menu::ColorPicker(83, "Text Color", ImVec2(374, 0), settings::AL_textColor);
				Menu::Slider(84, "Background Padding", ImVec2(225, 0), &settings::AL_backgroundPadding, 0, 20);
				Menu::ColorPicker(85, "Background Color", ImVec2(374, 0), settings::AL_backgroundColor);
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
