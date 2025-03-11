#include "menu.h"
#include "util/logger/logger.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

#include "configManager/settings.h"

#include "util/keys.h"

void Menu::Init()
{
	Menu::Title = "fusion+";
	Menu::Initialized = false;
	Menu::Open = false;
	Menu::Keybind = VK_INSERT;

	Menu::PlaceHooks();
	Logger::Log("Menu initialized");
}
bool Menu::TabButton(const char* format, ImVec4 color)
{
	ImGui::PushStyleColor(ImGuiCol_Button, color);
	bool result = ImGui::Button(format, ImVec2(100, 35));
	ImGui::PopStyleColor();
	return result;
}

void Menu::Slider(int id, const char* text, ImVec2 size, float* value, float min, float max, const char* format)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(settings::Menu_AccentColor[0] * 0.85f, settings::Menu_AccentColor[1] * 0.85f, settings::Menu_AccentColor[2] * 0.85f, settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImGui::SliderFloat("##slider", value, min, max, format);
	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::InputFloat("##input", value, 0.0f, 0.0f, format);
	ImGui::PopStyleVar();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);

	ImGui::PopStyleColor(2);

	ImGui::PopID();
}

void Menu::Slider(int id, const char* text, ImVec2 size, int* value, int min, int max, const char* format)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(settings::Menu_AccentColor[0] * 0.85f, settings::Menu_AccentColor[1] * 0.85f, settings::Menu_AccentColor[2] * 0.85f, settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImGui::SliderInt("", value, min, max, format);
	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::InputInt("", value, 0);
	ImGui::PopStyleVar();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);

	ImGui::PopStyleColor(2);

	ImGui::PopID();
}

void Menu::ToggleButton(int id, const char* text, ImVec2 size, bool* value)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float height = ImGui::GetFrameHeight() - 5;
	float width = height * 1.65f;
	float radius = height * 0.50f;

	if (ImGui::InvisibleButton(text, ImVec2(width, height)))
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

	draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(*value ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, col_circle);

	ImGui::PopID();
}

void Menu::ColorPicker(int id, const char* text, ImVec2 size, float* color)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImGui::ColorEdit4("", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

	ImGui::PopID();
}

void Menu::ComboBox(int id, const char* text, ImVec2 size, int* value, const char* items[], int listSize)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	ImGui::Combo("", value, items, listSize);
	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

	ImGui::PopID();
}

void Menu::KeybindButton(int id, const char* text, ImVec2 size, int& keybind)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	int keys_size = IM_ARRAYSIZE(keys);
	char name[18];
	strncpy_s(name, keys[std::clamp(keybind, 0, keys_size)], 18);
	static bool binding = false;

	if (binding)
	{
		ImGui::Button("[...]", ImVec2(76, 0));

		for (int i = 0; i < keys_size; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				if (i == VK_ESCAPE)
					keybind = 0;
				else
					keybind = i;

				strncpy_s(name, keys[std::clamp(keybind, 0, keys_size)], 18);

				binding = false;

				break;
			}
		}
	}
	else
	{
		if (ImGui::Button(name, ImVec2(100, 0)))
			binding = true;
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

	ImGui::PopID();
}

bool Menu::Button(int id, const char* text, ImVec2 size)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	bool result = ImGui::Button(text, size);

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

	ImGui::PopID();

	return result;
}

void Menu::Text(int id, const char* text, ImVec2 size, bool center)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	if (center)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (size.x - textSize.x) / 2);

	ImGui::Text(text);

	ImGui::PopID();
}

void Menu::TextColored(int id, const char* text, ImVec2 size, ImVec4 color, bool center)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	if (center)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (size.x - textSize.x) / 2);

	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::Text(text);
	ImGui::PopStyleColor();

	ImGui::PopID();
}

bool Menu::TextInput(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
	ImGui::SetNextItemWidth(max(0, size.x - textSize.x));
	bool result = ImGui::InputText("", buf, bufSize, flags);

	ImGui::PopStyleVar();

	ImGui::PopID();

	return result;
}

bool Menu::TextInputButton(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags, const char* buttonText)
{
	ImGui::PushID(id);
	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
	ImVec2 buttonTextSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, buttonText);

	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));

	ImGui::Text(text);
	ImGui::SameLine();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
	ImGui::SetNextItemWidth(max(0, size.x - textSize.x - buttonTextSize.x - 16));
	ImGui::InputText("", buf, bufSize, flags);
	ImGui::SameLine();

	ImGui::PopStyleVar();

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
	bool result = ImGui::Button(buttonText);

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar();

	ImGui::PopID();

	return result;
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
