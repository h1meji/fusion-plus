#include "menu.h"
#include "util/logger.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

#include "configManager/settings.h"

void Menu::Init()
{
	Menu::Title = "fusion+";
	Menu::Initialized = false;
	Menu::Open = false;
	Menu::Keybind = VK_INSERT;

	Menu::PlaceHooks();
}

void Menu::ToggleButton(const char* format, bool* value)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float height = ImGui::GetFrameHeight() - 5;
	float width = height * 1.65f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(format, ImVec2(width, height)))
		*value = !*value;
	ImU32 col_circle;
	ImU32 col_bg;
	if (ImGui::IsItemHovered()) 
	{
		col_circle = *value ? IM_COL32(255, 255, 255, 255) : IM_COL32(230, 230, 230, 255);
		col_bg = *value ? IM_COL32(settings::Menu_AccentColor[0] * 255, settings::Menu_AccentColor[1] * 255, settings::Menu_AccentColor[2] * 255, settings::Menu_AccentColor[3] * 255) : IM_COL32(settings::Menu_AccentColor[0] * 125, settings::Menu_AccentColor[1] * 125, settings::Menu_AccentColor[2] * 125, settings::Menu_AccentColor[3] * 255);
	}
	else 
	{
		col_circle = *value ? IM_COL32(230, 230, 230, 255) : IM_COL32(175, 175, 175, 255);
		col_bg = *value ? IM_COL32(settings::Menu_AccentColor[0] * 210, settings::Menu_AccentColor[1] * 210, settings::Menu_AccentColor[2] * 210, settings::Menu_AccentColor[3] * 255) : IM_COL32(settings::Menu_AccentColor[0] * 80, settings::Menu_AccentColor[1] * 80, settings::Menu_AccentColor[2] * 80, settings::Menu_AccentColor[3] * 255);
	}

	float offsetX = 8;
	float offsetY = 3;

	draw_list->AddRectFilled(ImVec2(p.x + offsetX, p.y + offsetY), ImVec2(p.x + width + offsetX, p.y + height + offsetY), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(*value ? (p.x + width - radius + offsetX) : (p.x + radius + offsetX), p.y + radius + offsetY), radius - 1.5f, col_circle);
}

bool Menu::TabButton(const char* format, ImVec4 color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, color);
	bool result = ImGui::Button(format, ImVec2(100, 35));
	ImGui::PopStyleColor();
	return result;
}

void Menu::DoSliderStuff(int id, const char* text, float* bruh, float min, float max) {
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	// change the line color
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(settings::Menu_AccentColor[0] * 0.85, settings::Menu_AccentColor[1] * 0.85, settings::Menu_AccentColor[2] * 0.85, settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	ImGui::PushID(id);
	ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));
	ImGui::Text(text);
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 230 - textSize.x - 20);
	ImGui::SliderFloat("", bruh, min, max);
	ImGui::SameLine();
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PopID();

	ImGui::PushID(id - 9);
	ImGui::InputFloat("", bruh);
	ImGui::PopStyleVar();
	ImGui::PopID();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Menu::DoToggleButtonStuff(int id, const char* text, bool* bruh) {
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

	ImGui::PushID(id);
	ImGui::Text(text);
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 340 - textSize.x);
	Menu::ToggleButton(text, bruh);
	ImGui::PopID();
}

void Menu::DoColorPickerStuff(int id, const char* text, float* color)
{
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

	ImGui::PushID(id);
	ImGui::Text(text);
	ImGui::SameLine();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 340 - textSize.x);
	ImGui::ColorEdit4("", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
	ImGui::PopID();
}


void Menu::GlitchText(const char* text, ImVec2 pos)
{
	// Red Text
	ImVec2 pos_one = ImVec2(pos.x - (1 + (rand() % 3)), pos.y - (rand() % 2));
	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, 28, pos_one, ImColor(235, 5, 90, 100 + (rand() % 60)), text);

	// Cyan Text;
	ImVec2 pos_two = ImVec2(pos.x + (1 + (rand() % 3)), pos.y + (rand() % 2));
	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, 28, pos_two, ImColor(32, 217, 217, 100 + (rand() % 60)), text);

	// Real Text
	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, 28, pos, ImColor(255, 255, 255), text);
}

void Menu::MoveCursorToCenter(bool checkInGame)
{
	if (checkInGame && SDK::Minecraft->IsInGuiState())
		return;

	RECT clientRect;
	if (GetClientRect(HandleWindow, &clientRect)) {
		// Calculate the center of the client area
		int clientCenterX = (clientRect.right - clientRect.left) / 2;
		int clientCenterY = (clientRect.bottom - clientRect.top) / 2;

		// Create a POINT to hold the center in client coordinates
		POINT clientCenterPoint = { clientCenterX, clientCenterY };

		// Convert client coordinates to screen coordinates
		ClientToScreen(HandleWindow, &clientCenterPoint);

		// Move the cursor to the center of the client area
		SetCursorPos(clientCenterPoint.x, clientCenterPoint.y);
	}
}

void Menu::Kill()
{
	Menu::Open = false;
	Menu::RemoveHooks();
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	wglDeleteContext(Menu::MenuGLContext);
	ImGui::DestroyContext();
}

void Menu::PlaceHooks()
{
	Menu::Hook_wglSwapBuffers();
	//Menu::Hook_tick();
}

void Menu::RemoveHooks()
{
	Menu::Unhook_wndProc();
	Menu::Unhook_wglSwapBuffers();
}
