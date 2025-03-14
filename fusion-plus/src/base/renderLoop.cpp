#include "base.h"
#include "sdk/sdk.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

#include "moduleManager/moduleManager.h"
#include "notificationManager/notificationManager.h"
#include <util/window/windowHelpers.h>
#include <moduleManager/commonData.h>

static void DrawLine(int x, int height, int padding)
{
	ImVec2 lineStart = ImVec2(x, settings::Hud_WatermarkPosition[1] + (padding * 1.5));
	ImVec2 lineEnd = ImVec2(x, settings::Hud_WatermarkPosition[1] + height - (padding * 1.5));
	ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(155, 155, 155, 255), 2);
}

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
		std::string version = "v0.5";
		std::string fps = std::to_string(CommonData::fps) + " FPS";

		int margin = 10;
		int padding = 10;

		int watermarkSize = 24;
		int statsSize = 22;

		ImVec2 textSize = Menu::FontBold->CalcTextSizeA(watermarkSize, FLT_MAX, 0, watermark);
		ImVec2 versionSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, version.c_str());
		ImVec2 fpsSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, fps.c_str());

		int totalTextWidth = textSize.x + versionSize.x + padding;
		if (settings::Hud_WatermarkFps)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += fpsSize.x + padding * 2;
		}

		ImVec2 rectSize = ImVec2(totalTextWidth + padding * 2, textSize.y + padding * 2);

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
			Menu::GlitchText(watermark, textPos, watermarkSize);

			ImVec2 versionTextPos = ImVec2(textPos.x + textSize.x + padding, textPos.y + 1);
			ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, versionTextPos, IM_COL32(255, 255, 255, 255), version.c_str());
			int currentX = versionTextPos.x + versionSize.x;

			if (settings::Hud_WatermarkFps)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 fpsTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, fpsTextPos, IM_COL32(255, 255, 255, 255), fps.c_str());

				currentX = fpsTextPos.x + fpsSize.x;
			}
		}
		ImGui::End();

		ImGui::PopStyleVar();
	}

	g_ModuleManager->RenderHud();

	NotificationManager::Render();
}