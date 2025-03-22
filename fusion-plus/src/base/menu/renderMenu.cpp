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

const int CATEGORY_FONT_SIZE_INT = 20;
const FontSize CATEGORY_FONT_SIZE = FontSize::SIZE_20;
const int MODULE_FONT_SIZE_INT = 16;
const FontSize MODULE_FONT_SIZE = FontSize::SIZE_16;
const FontSize BUTTON_FONT_SIZE = FontSize::SIZE_16;

void Menu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2(1000.f, 650.f));
	ImGui::Begin("Fusion+", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{

		ImVec2 titleSize = Menu::FontBold->CalcTextSizeA(24, FLT_MAX, 0.0f, ("FUSION+" + std::string(Base::version)).c_str());
		float leftWidth = titleSize.x += 40.f;
		float topHeight = titleSize.y + 20.f;

		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10.f, ImGui::GetCursorPosY() + 10.f)); // Change padding from 10 to 20
		ImGui::BeginGroup(); // Group for the bottom left part

		ImGui::BeginChild("##LogoVersion", ImVec2(leftWidth, topHeight), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			Menu::GlitchText("FUSION+", FontSize::SIZE_24);
			ImGui::SameLine();
			Menu::VerticalSeparator("LogoSep", ImGui::GetWindowSize().y - 20.f);
			ImGui::SameLine();
			Menu::BoldText(Base::version, FontSize::SIZE_24);
		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
		ImGui::BeginChild("##ModulesList", ImVec2(leftWidth, ImGui::GetWindowHeight() - topHeight - 185.f), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{

		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
		if (Menu::MenuButton("Configs", ImVec2(leftWidth, 35.f), BUTTON_FONT_SIZE))
		{

		}

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
		if (Menu::MenuButton("Settings", ImVec2(leftWidth, 35.f), BUTTON_FONT_SIZE))
		{

		}

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
		if (Menu::DetachButton("Detach", ImVec2(leftWidth, 35.f), BUTTON_FONT_SIZE))
		{
			Base::Running = false;
		}

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup(); // Group for the right part

		static std::vector<std::string> categories = g_ModuleManager->GetCategories();
		static int selectedCategory = 0;
		static int selectedModule = 0;

		static float occupiedSpace = std::accumulate(categories.begin(), categories.end(), 0.f, [](float acc, const std::string& str) { return acc + ceil(Menu::Font->CalcTextSizeA(CATEGORY_FONT_SIZE_INT, FLT_MAX, 0.0f, str.c_str()).x) + 8; }) + (categories.size() - 1);
		static float availableSpace = ceil(ImGui::GetWindowSize().x - leftWidth - 50.f);
		static float spaceBetween = ceil(max(10.f, (availableSpace - occupiedSpace) / (categories.size() * 2)) - 8.f);

		ImGui::BeginChild("##CategoriesBar", ImVec2(ImGui::GetWindowSize().x - leftWidth - 50.f, topHeight), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() - 2.f, ImGui::GetCursorPosY() - 1.f));

			for (int i = 0; i < categories.size(); i++)
			{
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spaceBetween);

				// Render "selected" line
				if (i == selectedCategory)
				{
					ImVec2 currentPos = ImGui::GetCursorScreenPos();
					ImVec2 textSize = Menu::Font->CalcTextSizeA(CATEGORY_FONT_SIZE_INT, FLT_MAX, 0.0f, categories[i].c_str());

					currentPos.y += 33.f;

					ImColor color = ImColor(settings::Menu_PrimaryColor[0], settings::Menu_PrimaryColor[1], settings::Menu_PrimaryColor[2], settings::Menu_PrimaryColor[3]);
					ImGui::GetWindowDrawList()->AddRectFilled(currentPos, ImVec2(currentPos.x + textSize.x + 8, currentPos.y + 1), color);
				}

				if (Menu::TransparentButton(categories[i].c_str(), ImVec2(0.f, 0.f), CATEGORY_FONT_SIZE))
				{
					selectedCategory = i;
				}
				ImGui::SameLine();

				if (i != categories.size() - 1)
				{
					ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spaceBetween);
					Menu::VerticalSeparator(("CatSep" + std::to_string(i)).c_str(), ImGui::GetWindowSize().y - 20.f);
					ImGui::SameLine();
				}
			}
		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.f);
		ImGui::BeginChild("##ModuleSettings", ImVec2(ImGui::GetWindowSize().x - leftWidth - 50.f, ImGui::GetWindowHeight() - topHeight - 50.f), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{

		}
		ImGui::EndChild();

		ImGui::EndGroup();
	}
	ImGui::End();
}

void Menu::RenderHudEditor()
{
	/*ImGui::SetNextWindowSize(ImVec2(424.f, 325.f));
	ImGui::Begin("Hud Editor", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	
	Menu::Text(1011, "Hud Editor", ImVec2(384.f, 0.f), true);

	ImGui::Separator();

	Menu::ToggleButton(1005, "Disable all Hud/Overlay rendering", ImVec2(368.f, 0.f), &settings::Hud_DisableAllRendering);

	ImGui::SeparatorText("Watermark");
	Menu::ToggleButton(1006, "Show Watermark", ImVec2(368.f, 0.f), &settings::Hud_Watermark);
	Menu::ToggleButton(1007, "Version", ImVec2(368.f, 0.f), &settings::Hud_WatermarkVersion);
	Menu::ToggleButton(1008, "FPS", ImVec2(368.f, 0.f), &settings::Hud_WatermarkFps);
	Menu::ToggleButton(1009, "Ping", ImVec2(368.f, 0.f), &settings::Hud_WatermarkPing);
	Menu::ToggleButton(1010, "Coordinates", ImVec2(368.f, 0.f), &settings::Hud_WatermarkCoords);
	Menu::ToggleButton(1011, "Direction", ImVec2(368.f, 0.f), &settings::Hud_WatermarkDirection);
	Menu::ToggleButton(1012, "Time", ImVec2(368.f, 0.f), &settings::Hud_WatermarkTime);

	ImGui::Separator();

	Menu::ToggleButton(1013, "Show Keybinds", ImVec2(368.f, 0.f), &settings::Hud_ShowKeybinds);

	ImGui::Separator();

	if (Menu::Button(1100, "Close Hud Editor", ImVec2(384.f, 0.f)))
	{
		Menu::OpenHudEditor = false;
		Menu::Open = true;
	}

	ImGui::End();*/
}
