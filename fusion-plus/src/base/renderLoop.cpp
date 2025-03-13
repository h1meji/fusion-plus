#include "base.h"
#include "sdk/sdk.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

#include "moduleManager/moduleManager.h"
#include "notificationManager/notificationManager.h"
#include <util/window/windowHelpers.h>

void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running || settings::Hud_DisableAllRendering) return;

	g_ModuleManager->RenderOverlay();

	if (Menu::OpenHudEditor)
	{
		// Render a black background to make the HUD editor more visible
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), windowSize, IM_COL32(0, 0, 0, 100));
	}

	if (settings::Hud_Watermark)
	{
		const char* watermark = "Fusion+";

		int margin = 10;
		int padding = 10;

		ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0, watermark);
		ImVec2 rectSize = ImVec2(textSize.x + padding * 2, textSize.y + padding * 2);

		ImGuiWindowFlags windowFlags;
		if (!Menu::OpenHudEditor)
		{
			windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs;
		}
		else
		{
			windowFlags = 0;
		}

		std::call_once(*Menu::setupWatermarkFlag, [&]() {
			ImGui::SetNextWindowPos(ImVec2(settings::Hud_WatermarkPosition[0], settings::Hud_WatermarkPosition[1]));
			});

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
		
		ImGui::SetNextWindowSize(rectSize);
		ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | windowFlags);
		{
			settings::Hud_WatermarkPosition[0] = ImGui::GetWindowPos().x;
			settings::Hud_WatermarkPosition[1] = ImGui::GetWindowPos().y;

			ImVec2 textPos = ImVec2(settings::Hud_WatermarkPosition[0] + padding, settings::Hud_WatermarkPosition[1] + padding);
			Menu::GlitchText(watermark, textPos);
		}
		ImGui::End();

		ImGui::PopStyleVar();
	}

	g_ModuleManager->RenderHud();

	NotificationManager::Render();
}