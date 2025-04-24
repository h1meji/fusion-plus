#pragma once

#include <string>
#include <vector>

#include <Windows.h>

#include <imgui/imgui.h>

#include "sdk/sdk.h"

enum FontSize
{
	SIZE_28,
	SIZE_26,
	SIZE_24,
	SIZE_22,
	SIZE_20,
	SIZE_18,
	SIZE_16,
	SIZE_14
};

struct Menu
{
	static void Init();
	static void Shutdown();

	static inline std::string title;
	static inline bool open;
	static inline bool openHudEditor;
	static inline ImFont* font;
	static inline ImFont* fontBold;
	static inline bool initialized;

	static inline bool isBindingKey;

	// Fonts
	static inline ImFont* font28;
	static inline ImFont* font26;
	static inline ImFont* font24;
	static inline ImFont* font22;
	static inline ImFont* font20;
	static inline ImFont* font18;
	static inline ImFont* font16;
	static inline ImFont* font14;
	static inline ImFont* boldFont28;
	static inline ImFont* boldFont26;
	static inline ImFont* boldFont24;
	static inline ImFont* boldFont22;
	static inline ImFont* boldFont20;
	static inline ImFont* boldFont18;
	static inline ImFont* boldFont16;
	static inline ImFont* boldFont14;

	static void SetupImgui();
	static void SetupStyle();

	static void RenderMenu();

	static bool ConfigItem(const char* name, bool* deleted, bool scrollbar);

	static void Text(const char* text, FontSize size);
	static void BoldText(const char* text, FontSize size);
	static void TextColored(const char* text, ImVec4 color, FontSize size);
	static void BoldTextColored(const char* text, ImVec4 color, FontSize size);
	static void GlitchText(const char* text, FontSize size);
	static void GlitchText(const char* text, ImVec2 pos, int size);

	static void VerticalSeparator(const char* str_id, float size = 0.f, float thickness = 1.f);
	static void HorizontalSeparator(const char* str_id, float size = 0.f, float thickness = 1.f);
	static void HorizontalSeparatorText(const char* text, FontSize font_size, float size = 0);

	static bool Button(const char* label, ImVec2 size = ImVec2(0, 0), FontSize font_size = SIZE_18);
	static void KeybindButton(const char* text, int& keybind, bool allowMouse = true, bool allowKeyboard = true, ImVec2 size = ImVec2(0, 0), FontSize font_size = SIZE_18);
	static bool TransparentButton(const char* text, ImVec2 btn_size, FontSize font_size);
	static bool MenuButton(const char* text, ImVec2 btn_size, FontSize font_size);
	static bool DetachButton(const char* text, ImVec2 btn_size, FontSize font_size);

	static void ToggleWithKeybind(bool* enabled, int& keybind, ImVec2 size = ImVec2(0, 0));

	static bool Slider(const char* label, int* value, int min, int max, ImVec2 size = ImVec2(0, 0), const char* format = "%d", ImGuiSliderFlags flags = 0);
	static bool Slider(const char* label, float* value, float min, float max, ImVec2 size = ImVec2(0, 0), const char* format = "%.2f", ImGuiSliderFlags flags = 0);

	static bool CheckboxBehavior(const char* label, bool* v);
	static bool Checkbox(const char* label, bool* v, ImVec2 size = ImVec2(0, 0));

	static bool ColorEdit(const char* label, float* col, ImVec2 size = ImVec2(0, 0), ImGuiColorEditFlags flags = 0);

	static bool Dropdown(const char* label, const char* items[], int* item_current, int items_count, ImVec2 size = ImVec2(0, 0));

	static void MoveCursorToCenter(bool checkInGame);

	static inline HWND handleWindow;
	static inline HDC handleDeviceContext;

	static inline HGLRC originalGLContext;
	static inline HGLRC menuGLContext;

	static inline ImGuiContext* currentImGuiContext;

	static void PlaceHooks();
	static void RemoveHooks();

	static void Hook_wglSwapBuffers();
	static void Hook_wndProc();

	static void Unhook_wglSwapBuffers();
	static void Unhook_wndProc();

	// Hud Setup Flags
	static void ResetSetupFlags();
	static inline auto setupWatermarkFlag = std::make_unique<std::once_flag>();
	static inline auto setupRadarFlag = std::make_unique<std::once_flag>();
	static inline auto setupKeybindsFlag = std::make_unique<std::once_flag>();
};

