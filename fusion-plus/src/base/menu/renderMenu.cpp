#include "menu.h"
#include "../../main.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

#include "util/window/borderless.h"

#include "moduleManager/moduleManager.h"

#include "sdk/net/minecraft/client/Minecraft.h"
#include "util/logger.h"
#include "menu/menu.h"
#include "configManager/configManager.h"

int currentTab = -1;

void RenderConfigMenu()
{
	ImGui::Spacing();

	// list of the config files that are selectable
	static std::vector<std::string> configFiles = ConfigManager::GetConfigList();
	static int selectedConfig = 0;

	if (ImGui::BeginChild("##configList", ImVec2(450, 232), false))
	{
		for (size_t i = 0; i < configFiles.size(); ++i)
		{
			if (ImGui::Selectable(configFiles[i].c_str()))
			{
				selectedConfig = i;
			}
		}
	}
	ImGui::EndChild();

	std::string selectedConfigName = configFiles.size() > 0 ? configFiles[selectedConfig] : "null";

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3, 0.3, 0.3, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4, 0.4, 0.4, 1));
	// buttons to load config
	if (ImGui::Button(("Load \"" + selectedConfigName + "\"").c_str(), ImVec2(247, 26)))
	{
		if (configFiles.size() > 0)
			ConfigManager::LoadConfig(selectedConfigName.c_str());
	}
	ImGui::SameLine();
	if (ImGui::Button("Open Folder"))
	{
		ShellExecuteA(NULL, "open", ConfigManager::GetDocumentsPath().c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
	ImGui::SameLine();
	if (ImGui::Button("Refresh"))
	{
		configFiles = ConfigManager::GetConfigList();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::Separator();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);

	// input box to save config
	static char saveConfigName[128] = "";
	// set width of input box
	ImGui::SetNextItemWidth(614);
	// set input box height
	ImGui::InputText("##saveConfigName", saveConfigName, IM_ARRAYSIZE(saveConfigName));

	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 4));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3, 0.3, 0.3, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4, 0.4, 0.4, 1));
	if (ImGui::Button("Save", ImVec2(65, 22)) && saveConfigName != "")
	{
		if (ConfigManager::SaveConfig(saveConfigName))
			configFiles = ConfigManager::GetConfigList();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void RenderSettingsMenu()
{
	ImGui::Spacing();

	Menu::DoColorPickerStuff(3457284, "Menu Accent Color", settings::Menu_AccentColor);
	
	Menu::DoToggleButtonStuff(9837592, "Show Watermark", &settings::Menu_Watermark);

	ImGui::Separator();

	Menu::DoToggleButtonStuff(83475893, "Disable All Rendering", &settings::Menu_DisableAllRendering);
}

void Menu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2(575, 300));
	ImGui::Begin(Menu::Title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImVec2 idk = ImGui::GetWindowSize();

	int buttonAmount = 6;
	int buttonHeight = 20;
	ImGui::Columns(2, "stuff");
	float columnWidth = 110;
	ImGui::SetColumnWidth(0, columnWidth);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, distTextSize, ImVec2(posX, posY), ImColor();
	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0.0f, "FUSION+");
	float posX = windowPos.x + (columnWidth / 2) - (textSize.x / 2);
	float posY = windowPos.y + 20;

	Menu::GlitchText("FUSION+", ImVec2(posX, posY));
	ImGui::SetCursorPosY(textSize.y + 30);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3, 0.3, 0.3, 1));
	if (ImGui::BeginChild("child_1", { 0, 140 }, false, ImGuiWindowFlags_NoScrollbar)) {
		std::vector<std::string> categories = g_ModuleManager->GetCategories();
		for (int i = 0; i < categories.size(); i++)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, currentTab == i ? ImVec4(0.4, 0.4, 0.4, 1) : ImVec4(0.2, 0.2, 0.2, 0.5));
			if (ImGui::Button((categories[i]).c_str(), ImVec2(94, 35)))
			{
				currentTab = i;
			}
			ImGui::PopStyleColor();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	ImGui::Spacing();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3, 0.3, 0.3, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4, 0.4, 0.4, 1));

	if (ImGui::Button("Settings", ImVec2(94, 0)))
	{
		currentTab = -3;
	}

	if (ImGui::Button("Config", ImVec2(94, 0)))
	{
		currentTab = -2;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.64, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.74, 0.4, 0.4, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0.4, 0.4, 1));

	if (ImGui::Button("Detach", ImVec2(94, 0)))
	{
		Menu::MoveCursorToCenter(true);
		Base::Running = false;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::InvisibleButton("##", ImVec2(1, idk.y));
	ImGui::NextColumn();

	if (ImGui::BeginChild("child_2", { 0, 0 }, false)) {
		g_ModuleManager->RenderMenu(currentTab);

		if (currentTab == -2)
		{
			RenderConfigMenu();
		}

		if (currentTab == -3)
		{
			RenderSettingsMenu();
		}

		ImGui::Spacing();
	}
	ImGui::EndChild();

	ImGui::End();
}