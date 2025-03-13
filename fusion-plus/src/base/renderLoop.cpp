#include "base.h"
#include "sdk/sdk.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

#include "moduleManager/moduleManager.h"
#include "notificationManager/notificationManager.h"

void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running || settings::Menu_DisableAllRendering) return;

	g_ModuleManager->RenderOverlay();

	if (settings::Menu_Watermark)
	{
		const char* watermark = "Fusion+";

		int margin = 10;
		int padding = 10;

		ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0, watermark);
		ImVec2 rectSize = ImVec2(textSize.x + padding * 2, textSize.y + padding * 2);
		ImVec2 screenSize = ImGui::GetIO().DisplaySize;

		ImVec2 rectPos = ImVec2(screenSize.x - margin - padding * 2 - textSize.x, screenSize.y - margin - padding * 2 - textSize.y);
		ImVec2 textPos = ImVec2(rectPos.x + padding, rectPos.y + padding);

		ImGui::GetWindowDrawList()->AddRectFilled(rectPos, ImVec2(rectPos.x + rectSize.x, rectPos.y + rectSize.y), IM_COL32(0, 0, 0, 200), 5.0f);

		Menu::GlitchText(watermark, textPos);
	}

	g_ModuleManager->RenderHud();

	NotificationManager::Render();
}