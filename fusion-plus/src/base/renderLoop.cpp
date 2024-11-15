#include "base.h"
#include "sdk/sdk.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

#include "moduleManager/moduleManager.h"

void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running) return;

	if (settings::Menu_Watermark)
	{
		const char* watermarkfusionplus = "fusion+ by himeji";
		const char* watermarkfusion = "fusion by deity & deadshxll";
		// goofy ahh css
		float margin = 3;
		float font_size = 24;

		ImVec2 screenSize = ImGui::GetWindowSize();
		ImVec2 textSizefusionplus = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermarkfusionplus);
		ImVec2 textSizefusion = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermarkfusion);

		ImVec2 textPosfusionplus = ImVec2(screenSize.x - textSizefusionplus.x - margin, screenSize.y - textSizefusionplus.y - margin - textSizefusion.y);
		ImVec2 textPosfusion = ImVec2(screenSize.x - textSizefusion.x - margin, screenSize.y - textSizefusion.y - margin);

		// add text border
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusionplus.x + 1, textPosfusionplus.y), ImColor(0, 0, 0), watermarkfusionplus);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusion.x + 1, textPosfusion.y), ImColor(0, 0, 0), watermarkfusion);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusionplus.x - 1, textPosfusionplus.y), ImColor(0, 0, 0), watermarkfusionplus);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusion.x - 1, textPosfusion.y), ImColor(0, 0, 0), watermarkfusion);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusionplus.x, textPosfusionplus.y + 1), ImColor(0, 0, 0), watermarkfusionplus);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusion.x, textPosfusion.y + 1), ImColor(0, 0, 0), watermarkfusion);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusionplus.x, textPosfusionplus.y - 1), ImColor(0, 0, 0), watermarkfusionplus);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(textPosfusion.x, textPosfusion.y - 1), ImColor(0, 0, 0), watermarkfusion);

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, textPosfusionplus, ImColor(255, 255, 255), watermarkfusionplus);
		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, textPosfusion, ImColor(255, 255, 255), watermarkfusion);
	}

	g_ModuleManager->RenderUpdate();
}