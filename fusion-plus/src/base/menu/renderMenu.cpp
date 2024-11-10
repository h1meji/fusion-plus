#include "menu.h"
#include "../../main.h"

#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../../../ext/imgui/imgui_impl_opengl2.h"

#include "../util/window/borderless.h"

#include "../moduleManager/moduleManager.h"

#include "../sdk/net/minecraft/client/Minecraft.h"
#include "../util/logger.h"

int currentTab = -1;

void Menu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2(575, 300));
	ImGui::Begin(Menu::Title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImVec2 idk = ImGui::GetWindowSize();

	int buttonAmount = 6;
	int buttonHeight = 20;
	ImGui::PushID("Start");
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

	std::vector<std::string> categories = g_ModuleManager->GetCategories();
	for (int i = 0; i < categories.size(); i++)
	{
		if (Menu::TabButton(categories[i].c_str(), (currentTab == i ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = i;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.64, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.74, 0.4, 0.4, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0.4, 0.4, 1));

	ImGui::SetCursorPos(ImVec2(17.5, ImGui::GetCursorPosY() + 85));
	if (ImGui::Button("Detach"))
	{
		Base::Running = false;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::InvisibleButton("", ImVec2(1, idk.y));
	ImGui::NextColumn();

	if (ImGui::BeginChild("child_2", { 0, 0 }, false)) {

		ImGui::PushID("menus");

		g_ModuleManager->RenderMenu(currentTab);
		ImGui::Spacing();

		ImGui::PopID();

		ImGui::EndChild();
	}
	ImGui::PopID();

	ImGui::End();
}