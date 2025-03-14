#include "menu.h"
#include "../../main.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

#include "util/window/borderless.h"

#include "moduleManager/moduleManager.h"

#include "sdk/net/minecraft/client/Minecraft.h"
#include "util/logger/logger.h"
#include "menu/menu.h"
#include "configManager/configManager.h"

#include "notificationManager/notificationManager.h"

int currentTab = -1;
std::unique_ptr<std::once_flag> setConfigName = std::make_unique<std::once_flag>();

static void RenderConfigMenu()
{
	ImGui::Spacing();

	// list of the config files that are selectable
	static std::vector<std::string> configFiles = ConfigManager::GetConfigList();
	static int selectedConfig = 0;

	if (ImGui::BeginChild("##configList", ImVec2(450, 232), false))
	{
		for (int i = 0; i < configFiles.size(); ++i)
		{
			if (ImGui::Selectable(configFiles[i].c_str()))
			{
				selectedConfig = i;
				setConfigName = std::make_unique<std::once_flag>();
			}
		}
	}
	ImGui::EndChild();

	std::string selectedConfigName = configFiles.size() > 0 ? configFiles[selectedConfig] : "null";

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 5.f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.f));
	// buttons to load config
	if (ImGui::Button(("Load \"" + selectedConfigName + "\"").c_str(), ImVec2(247, 26)))
	{
		if (configFiles.size() > 0)
		{
			if (ConfigManager::LoadConfig(selectedConfigName.c_str()))
			{
				NotificationManager::Send("Fusion+ :: Config", "Config \"%s\" has been loaded.", selectedConfigName.c_str());
				Menu::ResetSetupFlags();
			}
			else
			{
				NotificationManager::Send("Fusion+ :: Config", "Config \"%s\" could not be loaded.", selectedConfigName.c_str());
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Open Folder"))
	{
		ShellExecuteA(NULL, "open", ConfigManager::GetConfigPath().c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
	ImGui::SameLine();
	if (ImGui::Button("Refresh"))
	{
		configFiles = ConfigManager::GetConfigList();
		NotificationManager::Send("Fusion+ :: Config", "Config list has been refreshed.");
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
	std::call_once(*setConfigName, []() {
		const char* selectedConfigNameC = configFiles.size() > 0 ? configFiles[selectedConfig].c_str() : "";
		strcpy_s(saveConfigName, selectedConfigNameC);
		});

	// set width of input box
	ImGui::SetNextItemWidth(614);
	// set input box height
	ImGui::InputText("##saveConfigName", saveConfigName, IM_ARRAYSIZE(saveConfigName));

	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 4.f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.f));
	if (ImGui::Button("Save", ImVec2(65.f, 22.f)) && saveConfigName != "")
	{
		int result = ConfigManager::SaveConfig(saveConfigName);
		if (result != -1)
		{
			configFiles = ConfigManager::GetConfigList();
			selectedConfig = result;
			NotificationManager::Send("Fusion+ :: Config", "Config \"%s\" has been saved.", saveConfigName);
		}
		else
		{
			NotificationManager::Send("Fusion+ :: Config", "Config \"%s\" could not be saved.", saveConfigName);
		}
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

static void RenderSettingsMenu()
{
	ImGui::Spacing();

	ImGui::SeparatorText("Friends List");

	int height = 6;
	static int friendIndex = -1;
	if (ImGui::BeginChild("##friendslist", ImVec2(450.f, ImGui::GetTextLineHeightWithSpacing() * height), false))
	{
		for (int i = 0; i < settings::friends.size(); ++i)
		{
			ImGui::Selectable(settings::friends[i].c_str());
			// if right clicked on a friend, show popup to remove friend
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				friendIndex = i;
				ImGui::OpenPopup("##removeFriend");
			}
		}
	}
	if (ImGui::BeginPopup("##removeFriend"))
	{
		if (ImGui::Button(("Remove \"" + settings::friends[friendIndex] + "\"").c_str()))
		{
			const char* friendName = settings::friends[friendIndex].c_str();
			if (ConfigManager::RemoveFriend(settings::friends[friendIndex]))
			{
				friendIndex = -1;
				ImGui::CloseCurrentPopup();
				NotificationManager::Send("Fusion+ :: Friends", "Friend \"%s\" has been removed from your friends list.", friendName);
			}
		}
		ImGui::EndPopup();
	}
	ImGui::EndChild();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);

	// input box to save config
	static char friendName[128] = "";
	// set width of input box
	ImGui::SetNextItemWidth(614.f);
	// set input box height
	ImGui::InputText("##addFriend", friendName, IM_ARRAYSIZE(friendName));

	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 4.f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.f));
	if (ImGui::Button("Add", ImVec2(65, 22)) && friendName != "")
	{
		ConfigManager::AddFriend(friendName);
		NotificationManager::Send("Fusion+ :: Friends", "Friend \"%s\" has been added to your friends list.", std::string(friendName).c_str());

		friendName[0] = '\0';
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::Separator();

	Menu::ColorPicker(1001, "Menu Accent Color", ImVec2(374.f, 0.f), settings::Menu_AccentColor);
	Menu::ToggleButton(1002, "GUI Movement", ImVec2(368.f, 0.f), &settings::Menu_GUIMovement);
	Menu::ToggleButton(1003, "Show Hidden Categories", ImVec2(368.f, 0.f), &settings::Menu_ShowHiddenCategories);

	if (Menu::Button(1004, "Open Hud Editor", ImVec2(384.f, 0.f)))
	{
		Menu::OpenHudEditor = true;
		Menu::Open = false;
	}
}

void Menu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2(575.f, 300.f));
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
	float posY = windowPos.y + 15;

	Menu::GlitchText("FUSION+", ImVec2(posX, posY), 28);
	ImGui::SetCursorPosY(textSize.y + 30.f);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
	if (ImGui::BeginChild("child_1", { 0.f, 140.f }, false, ImGuiWindowFlags_NoScrollbar)) {
		std::vector<std::string> categories = g_ModuleManager->GetCategories();
		for (int i = 0; i < categories.size(); i++)
		{
			if (std::find(settings::Menu_HiddenCategoriesList.begin(), settings::Menu_HiddenCategoriesList.end(), categories[i]) != settings::Menu_HiddenCategoriesList.end() && !settings::Menu_ShowHiddenCategories)
					continue;

			ImGui::PushStyleColor(ImGuiCol_Button, currentTab == i ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
			if (ImGui::Button((categories[i]).c_str(), ImVec2(94.f, 35.f)))
			{
				currentTab = i;
			}
			ImGui::PopStyleColor();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	ImGui::BeginChild("seperatorchild", { 0.f, 1.f }, false);
	ImGui::Separator();
	ImGui::EndChild();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20.f, 5.f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.4f, 1.f));

	ImGui::PushStyleColor(ImGuiCol_Button, currentTab == -3 ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	if (ImGui::Button("Settings", ImVec2(94.f, 0.f)))
	{
		currentTab = -3;
	}
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Button, currentTab == -2 ? ImVec4(0.4f, 0.4f, 0.4f, 1.f) : ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
	if (ImGui::Button("Config", ImVec2(94.f, 0.f)))
	{
		currentTab = -2;
	}
	ImGui::PopStyleColor();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.64f, 0.2f, 0.2f, 0.5f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.74, 0.4f, 0.4f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.f, 0.4f, 0.4f, 1.f));

	if (ImGui::Button("Detach", ImVec2(94.f, 0.f)))
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

void Menu::RenderHudEditor()
{
	ImGui::SetNextWindowSize(ImVec2(424.f, 300.f));
	ImGui::Begin("Hud Editor", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	
	Menu::Text(1011, "Hud Editor", ImVec2(384.f, 0.f), true);

	ImGui::Separator();

	Menu::ToggleButton(1005, "Disable all Hud/Overlay rendering", ImVec2(368.f, 0.f), &settings::Hud_DisableAllRendering);
	Menu::ToggleButton(1006, "Show Watermark", ImVec2(368.f, 0.f), &settings::Hud_Watermark);
	Menu::ToggleButton(1007, "Show FPS in Watermark", ImVec2(368.f, 0.f), &settings::Hud_WatermarkFps);

	ImGui::Separator();

	if (Menu::Button(1010, "Close Hud Editor", ImVec2(384.f, 0.f)))
	{
		Menu::OpenHudEditor = false;
		Menu::Open = true;
	}

	ImGui::End();
}
