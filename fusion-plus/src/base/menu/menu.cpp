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
	Menu::OpenHudEditor = false;
	Menu::Keybind = VK_INSERT;

	Menu::PlaceHooks();
	Logger::Log("Menu initialized");
}

//bool Menu::TabButton(const char* format, ImVec4 color)
//{
//	/*ImGui::PushStyleColor(ImGuiCol_Button, color);
//	bool result = ImGui::Button(format, ImVec2(100, 35));
//	ImGui::PopStyleColor();
//	return result;*/
//	return false;
//}
//
//void Menu::Slider(int id, const char* text, ImVec2 size, float* value, float min, float max, const char* format)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(settings::Menu_AccentColor[0] * 0.85f, settings::Menu_AccentColor[1] * 0.85f, settings::Menu_AccentColor[2] * 0.85f, settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImGui::SliderFloat("##slider", value, min, max, format);
//	ImGui::SameLine();
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
//	ImGui::InputFloat("##input", value, 0.0f, 0.0f, format);
//	ImGui::PopStyleVar();
//
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
//
//	ImGui::PopStyleColor(2);
//
//	ImGui::PopID();*/
//}
//
//void Menu::Slider(int id, const char* text, ImVec2 size, int* value, int min, int max, const char* format)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(settings::Menu_AccentColor[0] * 0.85f, settings::Menu_AccentColor[1] * 0.85f, settings::Menu_AccentColor[2] * 0.85f, settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImGui::SliderInt("", value, min, max, format);
//	ImGui::SameLine();
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
//	ImGui::InputInt("", value, 0);
//	ImGui::PopStyleVar();
//
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
//
//	ImGui::PopStyleColor(2);
//
//	ImGui::PopID();*/
//}
//
//void Menu::ToggleButton(int id, const char* text, ImVec2 size, bool* value)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImVec2 p = ImGui::GetCursorScreenPos();
//	ImDrawList* draw_list = ImGui::GetWindowDrawList();
//	float height = ImGui::GetFrameHeight() - 5;
//	float width = height * 1.65f;
//	float radius = height * 0.50f;
//
//	if (ImGui::InvisibleButton(text, ImVec2(width, height)))
//		*value = !*value;
//	ImU32 col_circle;
//	ImU32 col_bg;
//	if (ImGui::IsItemHovered())
//	{
//		col_circle = *value ? IM_COL32(255, 255, 255, 255) : IM_COL32(230, 230, 230, 255);
//		col_bg = *value ? IM_COL32(settings::Menu_AccentColor[0] * 255, settings::Menu_AccentColor[1] * 255, settings::Menu_AccentColor[2] * 255, settings::Menu_AccentColor[3] * 255) : IM_COL32(settings::Menu_AccentColor[0] * 125, settings::Menu_AccentColor[1] * 125, settings::Menu_AccentColor[2] * 125, settings::Menu_AccentColor[3] * 255);
//	}
//	else
//	{
//		col_circle = *value ? IM_COL32(230, 230, 230, 255) : IM_COL32(175, 175, 175, 255);
//		col_bg = *value ? IM_COL32(settings::Menu_AccentColor[0] * 210, settings::Menu_AccentColor[1] * 210, settings::Menu_AccentColor[2] * 210, settings::Menu_AccentColor[3] * 255) : IM_COL32(settings::Menu_AccentColor[0] * 80, settings::Menu_AccentColor[1] * 80, settings::Menu_AccentColor[2] * 80, settings::Menu_AccentColor[3] * 255);
//	}
//
//	draw_list->AddRectFilled(ImVec2(p.x, p.y), ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
//	draw_list->AddCircleFilled(ImVec2(*value ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, col_circle);
//
//	ImGui::PopID();*/
//}
//
//void Menu::ColorPicker(int id, const char* text, ImVec2 size, float* color)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImGui::ColorEdit4("", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
//
//	ImGui::PopID();*/
//}
//
//void Menu::ComboBox(int id, const char* text, ImVec2 size, int* value, const char* items[], int listSize)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//	ImGui::Combo("", value, items, listSize);
//	ImGui::PopStyleColor(3);
//	ImGui::PopStyleVar();
//
//	ImGui::PopID();*/
//}
//
//void Menu::KeybindButton(int id, const char* text, ImVec2 size, int& keybind)
//{
//	/*static std::unordered_map<int, bool> binding;
//
//	ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + size.x - textSize.x - 20);
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//
//	int keys_size = IM_ARRAYSIZE(keys);
//	char name[18];
//	strncpy_s(name, Keys::GetKeyName(keybind), 18);
//
//	if (binding[id])
//	{
//		ImGui::Button("[...]", ImVec2(76, 0));
//
//		for (int i = 0; i < keys_size; i++)
//		{
//			if (GetAsyncKeyState(i) & 0x8000)
//			{
//				if (i == VK_ESCAPE)
//					keybind = 0;
//				else
//					keybind = i;
//
//				strncpy_s(name, Keys::GetKeyName(keybind), 18);
//
//				binding[id] = false;
//
//				break;
//			}
//		}
//	}
//	else
//	{
//		if (ImGui::Button(name, ImVec2(100, 0)))
//			binding[id] = true;
//	}
//
//	ImGui::PopStyleColor(3);
//	ImGui::PopStyleVar();
//
//	ImGui::PopID();*/
//}
//
//bool Menu::Button(int id, const char* text, ImVec2 size)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//
//	bool result = ImGui::Button(text, size);
//
//	ImGui::PopStyleColor(3);
//	ImGui::PopStyleVar();
//
//	ImGui::PopID();
//
//	return result;*/
//	return false;
//}
//
//void Menu::Text(int id, const char* text, ImVec2 size, bool center)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	if (center)
//		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (size.x - textSize.x) / 2);
//
//	ImGui::Text(text);
//
//	ImGui::PopID();*/
//}
//
//void Menu::TextColored(int id, const char* text, ImVec2 size, ImVec4 color, bool center)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	if (center)
//		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (size.x - textSize.x) / 2);
//
//	ImGui::PushStyleColor(ImGuiCol_Text, color);
//	ImGui::Text(text);
//	ImGui::PopStyleColor();
//
//	ImGui::PopID();*/
//}
//
//bool Menu::TextInput(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
//	ImGui::SetNextItemWidth(max(0, size.x - textSize.x));
//	bool result = ImGui::InputText("", buf, bufSize, flags);
//
//	ImGui::PopStyleVar();
//
//	ImGui::PopID();
//
//	return result;*/
//	return false;
//}
//
//bool Menu::TextInputButton(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags, const char* buttonText)
//{
//	/*ImGui::PushID(id);
//	ImVec2 textSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, text);
//	ImVec2 buttonTextSize = Menu::Font->CalcTextSizeA(Menu::Font->FontSize, FLT_MAX, 0.0f, buttonText);
//
//	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 20, ImGui::GetCursorPosY() + 5));
//
//	ImGui::Text(text);
//	ImGui::SameLine();
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
//	ImGui::SetNextItemWidth(max(0, size.x - textSize.x - buttonTextSize.x - 16));
//	ImGui::InputText("", buf, bufSize, flags);
//	ImGui::SameLine();
//
//	ImGui::PopStyleVar();
//
//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
//
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
//	bool result = ImGui::Button(buttonText);
//
//	ImGui::PopStyleColor(3);
//	ImGui::PopStyleVar();
//
//	ImGui::PopID();
//
//	return result;*/
//	return false;
//}
//
//void Menu::GlitchText(const char* text, ImVec2 pos, int size)
//{
//	// Red Text
//	ImVec2 pos_one = ImVec2(pos.x - (1 + (rand() % 3)), pos.y - (rand() % 2));
//	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, size, pos_one, ImColor(235, 5, 90, 100 + (rand() % 60)), text);
//
//	// Cyan Text;
//	ImVec2 pos_two = ImVec2(pos.x + (1 + (rand() % 3)), pos.y + (rand() % 2));
//	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, size, pos_two, ImColor(32, 217, 217, 100 + (rand() % 60)), text);
//
//	// Real Text
//	ImGui::GetWindowDrawList()->AddText(Menu::FontBold, size, pos, ImColor(255, 255, 255), text);
//}


void Menu::Text(const char* text, FontSize size)
{
	if (size == FontSize::SIZE_28) ImGui::PushFont(Menu::Font28);
	else if (size == FontSize::SIZE_26) ImGui::PushFont(Menu::Font26);
	else if (size == FontSize::SIZE_24) ImGui::PushFont(Menu::Font24);
	else if (size == FontSize::SIZE_22) ImGui::PushFont(Menu::Font22);
	else if (size == FontSize::SIZE_20) ImGui::PushFont(Menu::Font20);
	else if (size == FontSize::SIZE_18) ImGui::PushFont(Menu::Font18);
	else if (size == FontSize::SIZE_16) ImGui::PushFont(Menu::Font16);
	else if (size == FontSize::SIZE_14) ImGui::PushFont(Menu::Font14);

	ImGui::Text(text);

	ImGui::PopFont();
}

void Menu::BoldText(const char* text, FontSize size)
{
	if (size == FontSize::SIZE_28) ImGui::PushFont(Menu::BoldFont28);
	else if (size == FontSize::SIZE_26) ImGui::PushFont(Menu::BoldFont26);
	else if (size == FontSize::SIZE_24) ImGui::PushFont(Menu::BoldFont24);
	else if (size == FontSize::SIZE_22) ImGui::PushFont(Menu::BoldFont22);
	else if (size == FontSize::SIZE_20) ImGui::PushFont(Menu::BoldFont20);
	else if (size == FontSize::SIZE_18) ImGui::PushFont(Menu::BoldFont18);
	else if (size == FontSize::SIZE_16) ImGui::PushFont(Menu::BoldFont16);
	else if (size == FontSize::SIZE_14) ImGui::PushFont(Menu::BoldFont14);

	ImGui::Text(text);

	ImGui::PopFont();
}

void Menu::GlitchText(const char* text, FontSize size)
{
	ImVec2 cursorPos = ImGui::GetCursorPos();  // Get the current cursor position in screen space
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	// Push the custom font with the given size
	if (size == FontSize::SIZE_28) ImGui::PushFont(Menu::BoldFont28);
	else if (size == FontSize::SIZE_26) ImGui::PushFont(Menu::BoldFont26);
	else if (size == FontSize::SIZE_24) ImGui::PushFont(Menu::BoldFont24);
	else if (size == FontSize::SIZE_22) ImGui::PushFont(Menu::BoldFont22);
	else if (size == FontSize::SIZE_20) ImGui::PushFont(Menu::BoldFont20);
	else if (size == FontSize::SIZE_18) ImGui::PushFont(Menu::BoldFont18);
	else if (size == FontSize::SIZE_16) ImGui::PushFont(Menu::BoldFont16);
	else if (size == FontSize::SIZE_14) ImGui::PushFont(Menu::BoldFont14);

	// Red Glitch Offset (slightly displaced)
	ImVec2 pos_red = ImVec2(cursorPos.x - (1 + (rand() % 3)), cursorPos.y - (rand() % 2));
	ImGui::SetCursorPos(pos_red);  // Set the cursor to the new position
	ImGui::TextColored(ImColor(235, 5, 90, 100 + (rand() % 60)), "%s", text);  // Red text

	// Cyan Glitch Offset (slightly displaced)
	ImVec2 pos_cyan = ImVec2(cursorPos.x + (1 + (rand() % 3)), cursorPos.y + (rand() % 2));
	ImGui::SetCursorPos(pos_cyan);  // Set the cursor to the new position
	ImGui::TextColored(ImColor(32, 217, 217, 100 + (rand() % 60)), "%s", text);  // Cyan text

	// Main Text (centered)
	ImGui::SetCursorPos(cursorPos);  // Reset cursor to original position
	ImGui::TextColored(ImColor(255, 255, 255), "%s", text);  // Main white text

	// Pop the custom font to restore the default
	ImGui::PopFont();
}

void Menu::VerticalSeparator(const char* str_id, float size, float thickness)
{
	// Get the current cursor position
	ImVec2 p1 = ImGui::GetCursorScreenPos();

	// Define the position for the separator (just use thickness for the vertical separator)
	ImVec2 p2 = ImVec2(p1.x + thickness, p1.y + size);

	// Define the color for the separator
	ImColor color = ImColor(settings::Menu_SeperatorColor[0], settings::Menu_SeperatorColor[1], settings::Menu_SeperatorColor[2], settings::Menu_SeperatorColor[3]);

	// Draw the vertical separator using ImGui's window draw list
	ImGui::GetWindowDrawList()->AddRectFilled(p1, p2, color);

	// Use an invisible button to reserve space, with no visible UI change
	ImGui::InvisibleButton(("###VerticalSeparator" + std::string(str_id)).c_str(), ImVec2(thickness, size));
}

void Menu::HorizontalSeparator(const char* str_id, float size, float thickness)
{
	if (size == 0)
	{
		size = ImGui::GetWindowSize().x - 40.f;
	}

	// Get the current cursor position
	ImVec2 p1 = ImGui::GetCursorScreenPos();

	// Define the position for the separator (just use thickness for the horizontal separator)
	ImVec2 p2 = ImVec2(p1.x + size, p1.y + thickness);

	// Define the color for the separator
	ImColor color = ImColor(settings::Menu_SeperatorColor[0], settings::Menu_SeperatorColor[1], settings::Menu_SeperatorColor[2], settings::Menu_SeperatorColor[3]);

	// Draw the horizontal separator using ImGui's window draw list
	ImGui::GetWindowDrawList()->AddRectFilled(p1, p2, color);

	// Now, use an invisible button to move the cursor by just the thickness
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + thickness);

	// Use an invisible button to reserve space, with no visible UI change
	ImGui::InvisibleButton(("###HorizontalSeparator_" + std::string(str_id)).c_str(), ImVec2(size, thickness));
}

bool Menu::TransparentButton(const char* text, ImVec2 btn_size, FontSize font_size)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
	
	if (font_size == FontSize::SIZE_28) ImGui::PushFont(Menu::Font28);
	else if (font_size == FontSize::SIZE_26) ImGui::PushFont(Menu::Font26);
	else if (font_size == FontSize::SIZE_24) ImGui::PushFont(Menu::Font24);
	else if (font_size == FontSize::SIZE_22) ImGui::PushFont(Menu::Font22);
	else if (font_size == FontSize::SIZE_20) ImGui::PushFont(Menu::Font20);
	else if (font_size == FontSize::SIZE_18) ImGui::PushFont(Menu::Font18);
	else if (font_size == FontSize::SIZE_16) ImGui::PushFont(Menu::Font16);
	else if (font_size == FontSize::SIZE_14) ImGui::PushFont(Menu::Font14);

	bool result = ImGui::Button(text, btn_size);
	if (ImGui::IsItemHovered())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	ImGui::PopFont();

	ImGui::PopStyleColor(3);

	return result;
}

bool Menu::MenuButton(const char* text, ImVec2 btn_size, FontSize font_size)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_ChildBackgroundColor[0], settings::Menu_ChildBackgroundColor[1], settings::Menu_ChildBackgroundColor[2], settings::Menu_ChildBackgroundColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImClamp<float>(settings::Menu_ChildBackgroundColor[0] * 0.8f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_ChildBackgroundColor[1] * 0.8f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_ChildBackgroundColor[2] * 0.8f, 0.0f, 1.0f), settings::Menu_ChildBackgroundColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImClamp<float>(settings::Menu_ChildBackgroundColor[0] * 0.6f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_ChildBackgroundColor[1] * 0.6f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_ChildBackgroundColor[2] * 0.6f, 0.0f, 1.0f), settings::Menu_ChildBackgroundColor[3]));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(settings::Menu_OutlineColor[0], settings::Menu_OutlineColor[1], settings::Menu_OutlineColor[2], settings::Menu_OutlineColor[3]));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, settings::Menu_WindowRounding);

	if (font_size == FontSize::SIZE_28) ImGui::PushFont(Menu::Font28);
	else if (font_size == FontSize::SIZE_26) ImGui::PushFont(Menu::Font26);
	else if (font_size == FontSize::SIZE_24) ImGui::PushFont(Menu::Font24);
	else if (font_size == FontSize::SIZE_22) ImGui::PushFont(Menu::Font22);
	else if (font_size == FontSize::SIZE_20) ImGui::PushFont(Menu::Font20);
	else if (font_size == FontSize::SIZE_18) ImGui::PushFont(Menu::Font18);
	else if (font_size == FontSize::SIZE_16) ImGui::PushFont(Menu::Font16);
	else if (font_size == FontSize::SIZE_14) ImGui::PushFont(Menu::Font14);

	bool result = ImGui::Button(text, btn_size);
	if (ImGui::IsItemHovered())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	ImGui::PopFont();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);

	return result;
}

bool Menu::DetachButton(const char* text, ImVec2 btn_size, FontSize font_size)
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_DetachButtonColor[0], settings::Menu_DetachButtonColor[1], settings::Menu_DetachButtonColor[2], settings::Menu_DetachButtonColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImClamp<float>(settings::Menu_DetachButtonColor[0] * 0.8f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_DetachButtonColor[1] * 0.8f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_DetachButtonColor[2] * 0.8f, 0.0f, 1.0f), settings::Menu_DetachButtonColor[3]));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImClamp<float>(settings::Menu_DetachButtonColor[0] * 0.6f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_DetachButtonColor[1] * 0.6f, 0.0f, 1.0f), ImClamp<float>(settings::Menu_DetachButtonColor[2] * 0.6f, 0.0f, 1.0f), settings::Menu_DetachButtonColor[3]));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(settings::Menu_OutlineColor[0], settings::Menu_OutlineColor[1], settings::Menu_OutlineColor[2], settings::Menu_OutlineColor[3]));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, settings::Menu_WindowRounding);

	if (font_size == FontSize::SIZE_28) ImGui::PushFont(Menu::Font28);
	else if (font_size == FontSize::SIZE_26) ImGui::PushFont(Menu::Font26);
	else if (font_size == FontSize::SIZE_24) ImGui::PushFont(Menu::Font24);
	else if (font_size == FontSize::SIZE_22) ImGui::PushFont(Menu::Font22);
	else if (font_size == FontSize::SIZE_20) ImGui::PushFont(Menu::Font20);
	else if (font_size == FontSize::SIZE_18) ImGui::PushFont(Menu::Font18);
	else if (font_size == FontSize::SIZE_16) ImGui::PushFont(Menu::Font16);
	else if (font_size == FontSize::SIZE_14) ImGui::PushFont(Menu::Font14);

	bool result = ImGui::Button(text, btn_size);
	if (ImGui::IsItemHovered())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}

	ImGui::PopFont();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(4);

	return result;
}

void Menu::ToggleWithKeybind(bool* enabled, int& keybind, ImVec2 size)
{
	if (size.x == 0)
	{
		size.x = ImGui::GetWindowSize().x - 40.f;
	}

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
	Menu::Text("Enabled", FontSize::SIZE_18);
	ImGui::SameLine();

	const float w = 160.f; // Width of checkbox and keybind button
	const float space = size.x - Font18->CalcTextSizeA(18, FLT_MAX, 0.0f, "Enabled").x - w;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + space - 10);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5.f);

	CheckboxBehavior("##Toggle", enabled);
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5.f);
	int keys_size = IM_ARRAYSIZE(keys);
	char name[18];
	strncpy_s(name, keys[std::clamp(keybind, 0, keys_size)], 18);
	static bool binding = false;
	if (binding)
	{
		ImGui::Button("[...]", ImVec2(120, 0));

		for (int i = 0; i < keys_size; i++)
		{
			if (!Keys::IsKeyPressed(i)) continue;

			if (i == VK_ESCAPE) keybind = 0;
			else keybind = i;

			strncpy_s(name, keys[std::clamp(keybind, 0, keys_size)], 18);
			binding = false;
			break;
		}
	}
	else
	{
		if (ImGui::Button(Keys::GetKeyName(keybind), ImVec2(120, 0)))
		{
			binding = true;
		}
	}
}

//
// Copied from ImGui::SliderScalar and modified it.
//
bool Menu::Slider(const char* label, int* value, int min, int max, ImVec2 size, const char* format, ImGuiSliderFlags flags)
{
	if (size.x == 0)
	{
		size.x = ImGui::GetWindowSize().x - 40.f;
	}

	const float w = ImGui::CalcItemWidth() - 150; // Width of the slider
	const float space = size.x - Font18->CalcTextSizeA(18, FLT_MAX, 0.0f, label).x - w;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
	Menu::Text(label, FontSize::SIZE_18);
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5.f);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + space - 10);

	// ===== Slider behavior ===== //
	ImGuiDataType data_type = ImGuiDataType_S32;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImVec2 frame_bb_max = ImVec2(window->DC.CursorPos.x + w, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos, frame_bb_max);
	const ImVec2 total_bb_max = ImVec2(frame_bb.Max.x + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), frame_bb.Max.y);
	const ImRect total_bb(frame_bb.Min, total_bb_max);

	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
		return false;

	// Default format string when passing NULL
	if (format == NULL)
		format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);
	bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
	if (!temp_input_is_active)
	{
		// Tabbing or CTRL-clicking on Slider turns it into an input box
		const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
		const bool clicked = hovered && ImGui::IsMouseClicked(0, id);
		const bool make_active = (input_requested_by_tabbing || clicked || g.NavActivateId == id || g.NavActivateInputId == id);
		if (make_active && clicked)
			ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
		if (make_active && temp_input_allowed)
			if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || g.NavActivateInputId == id)
				temp_input_is_active = true;

		if (make_active && !temp_input_is_active)
		{
			ImGui::SetActiveID(id, window);
			ImGui::SetFocusID(id, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
		}
	}

	if (temp_input_is_active)
	{
		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
		const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
		return ImGui::TempInputScalar(frame_bb, id, label, data_type, value, format, is_clamp_input ? &min : NULL, is_clamp_input ? &max : NULL);
	}

	// Draw frame
	const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	ImGui::RenderNavHighlight(frame_bb, id);
	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, value, &min, &max, format, flags, &grab_bb);
	if (value_changed)
		ImGui::MarkItemEdited(id);

	// Render grab
	ImVec2 modified_grab_bb_min = ImVec2(frame_bb.Min.x + 3, frame_bb.Min.y + 3);
	ImVec2 modified_grab_bb_max = ImVec2(grab_bb.Max.x - 1, grab_bb.Max.y - 1);
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(modified_grab_bb_min, modified_grab_bb_max, ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.FrameRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, value, format);
	ImVec2 value_buf_size = ImGui::CalcTextSize(value_buf);
	ImVec2 value_buf_pos_min = ImVec2(frame_bb.Max.x - value_buf_size.x - 12.f, frame_bb.Min.y);
	ImGui::RenderTextClipped(value_buf_pos_min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

	//// Display label
	//if (label_size.x > 0.0f)
	//	ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));
	return value_changed;
}

bool Menu::Slider(const char* label, float* value, float min, float max, ImVec2 size, const char* format, ImGuiSliderFlags flags)
{
	if (size.x == 0)
	{
		size.x = ImGui::GetWindowSize().x - 40.f;
	}

	const float w = ImGui::CalcItemWidth() - 150; // Width of the slider
	const float space = size.x - Font18->CalcTextSizeA(18, FLT_MAX, 0.0f, label).x - w;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
	Menu::Text(label, FontSize::SIZE_18);
	ImGui::SameLine();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5.f);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + space - 10);

	// ===== Slider behavior ===== //
	ImGuiDataType data_type = ImGuiDataType_Float;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImVec2 frame_bb_max = ImVec2(window->DC.CursorPos.x + w, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos, frame_bb_max);
	const ImVec2 total_bb_max = ImVec2(frame_bb.Max.x + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), frame_bb.Max.y + 0.0f);
	const ImRect total_bb(frame_bb.Min, total_bb_max);

	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
		return false;

	// Default format string when passing NULL
	if (format == NULL)
		format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);
	bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
	if (!temp_input_is_active)
	{
		// Tabbing or CTRL-clicking on Slider turns it into an input box
		const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
		const bool clicked = hovered && ImGui::IsMouseClicked(0, id);
		const bool make_active = (input_requested_by_tabbing || clicked || g.NavActivateId == id || g.NavActivateInputId == id);
		if (make_active && clicked)
			ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
		if (make_active && temp_input_allowed)
			if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || g.NavActivateInputId == id)
				temp_input_is_active = true;

		if (make_active && !temp_input_is_active)
		{
			ImGui::SetActiveID(id, window);
			ImGui::SetFocusID(id, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
		}
	}

	if (temp_input_is_active)
	{
		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
		const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
		return ImGui::TempInputScalar(frame_bb, id, label, data_type, value, format, is_clamp_input ? &min : NULL, is_clamp_input ? &max : NULL);
	}

	// Draw frame
	const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	ImGui::RenderNavHighlight(frame_bb, id);
	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, value, &min, &max, format, flags, &grab_bb);
	if (value_changed)
		ImGui::MarkItemEdited(id);

	// Render grab
	ImVec2 modified_grab_bb_min = ImVec2(frame_bb.Min.x + 3, frame_bb.Min.y + 3);
	ImVec2 modified_grab_bb_max = ImVec2(grab_bb.Max.x - 1, grab_bb.Max.y - 1);
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddRectFilled(modified_grab_bb_min, modified_grab_bb_max, ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.FrameRounding);

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, value, format);
	ImVec2 value_buf_size = ImGui::CalcTextSize(value_buf);
	ImVec2 value_buf_pos_min = ImVec2(frame_bb.Max.x - value_buf_size.x - 12.f, frame_bb.Min.y);
	ImGui::RenderTextClipped(value_buf_pos_min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

	//// Display label
	//if (label_size.x > 0.0f)
	//	ImGui::RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (temp_input_allowed ? ImGuiItemStatusFlags_Inputable : 0));

	return value_changed;
}

bool Menu::CheckboxBehavior(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImVec2 total_bb_max(pos.x + square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y + style.FramePadding.y * 2.0f);
	const ImRect total_bb(pos, total_bb_max);
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
	{
		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
		return false;
	}

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		ImGui::MarkItemEdited(id);
	}

	const ImVec2 check_bb_max(pos.x + square_sz, pos.y + square_sz);
	const ImRect check_bb(pos, check_bb_max);
	ImGui::RenderNavHighlight(total_bb, id);
	ImGui::RenderFrame(check_bb.Min, check_bb.Max, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, style.FrameRounding);
	ImU32 check_col = ImGui::GetColorU32(ImGuiCol_CheckMark);
	bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;
	if (mixed_value)
	{
		// Undocumented tristate/mixed/indeterminate checkbox (#2644)
		// This may seem awkwardly designed because the aim is to make ImGuiItemFlags_MixedValue supported by all widgets (not just checkbox)
		ImVec2 pad(ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)), ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)));
		ImVec2 min_r(check_bb.Min.x + pad.x, check_bb.Min.y + pad.y);
		ImVec2 max_r(check_bb.Max.x - pad.x, check_bb.Max.y - pad.y);
		window->DrawList->AddRectFilled(min_r, max_r, check_col, style.FrameRounding);
	}
	else if (*v)
	{
		const float pad = 3.0f;
		//ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2(pad, pad), check_col, square_sz - pad * 2.0f);
		window->DrawList->AddRectFilled(ImVec2(check_bb.Min.x + pad, check_bb.Min.y + pad), ImVec2(check_bb.Max.x - pad, check_bb.Max.y - pad), check_col, style.FrameRounding);
	}

	ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
	if (g.LogEnabled)
		ImGui::LogRenderedText(&label_pos, mixed_value ? "[~]" : *v ? "[x]" : "[ ]");
	if (label_size.x > 0.0f)
		ImGui::RenderText(label_pos, label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;
}

bool Menu::Checkbox(const char* label, bool* v, ImVec2 size)
{
	if (size.x == 0)
	{
		size.x = ImGui::GetWindowSize().x - 40.f;
	}

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);
	Menu::Text(label, FontSize::SIZE_18);
	ImGui::SameLine();

	const float w = 30.f; // Width of checkbox
	const float space = size.x - Font18->CalcTextSizeA(18, FLT_MAX, 0.0f, label).x - w;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + space - 10);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5.f);

	return CheckboxBehavior(("##" + std::string(label)).c_str(), v);
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
	Menu::OpenHudEditor = false;
	Menu::RemoveHooks();
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	wglDeleteContext(Menu::MenuGLContext);
	//ImGui::DestroyContext(); // This is causing a crash
}

void Menu::PlaceHooks()
{
	Menu::Hook_wglSwapBuffers();
}

void Menu::RemoveHooks()
{
	Menu::Unhook_wndProc();
	Menu::Unhook_wglSwapBuffers();
}
