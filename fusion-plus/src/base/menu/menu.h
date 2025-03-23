#pragma once

#include <string>
#include <Windows.h>
#include <vector>

#include "imgui/imgui.h"

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
	static void Kill();

	static inline std::string Title;
	static inline bool Open;
	static inline bool OpenHudEditor;
	static inline int Keybind;
	static inline ImFont* Font;
	static inline ImFont* FontBold;
	static inline bool Initialized;

	// Fonts
	static inline ImFont* Font28;
	static inline ImFont* Font26;
	static inline ImFont* Font24;
	static inline ImFont* Font22;
	static inline ImFont* Font20;
	static inline ImFont* Font18;
	static inline ImFont* Font16;
	static inline ImFont* Font14;
	static inline ImFont* BoldFont28;
	static inline ImFont* BoldFont26;
	static inline ImFont* BoldFont24;
	static inline ImFont* BoldFont22;
	static inline ImFont* BoldFont20;
	static inline ImFont* BoldFont18;
	static inline ImFont* BoldFont16;
	static inline ImFont* BoldFont14;

	static void SetupImgui();

	static void RenderMenu();
	static void RenderHudEditor();

	//static bool TabButton(const char* format, ImVec4 color);
	//static void Slider(int id, const char* text, ImVec2 size, float* value, float min, float max, const char* format = "%.2f");
	//static void Slider(int id, const char* text, ImVec2 size, int* value, int min, int max, const char* format = "%d");
	//static void ToggleButton(int id, const char* text, ImVec2 size, bool* value);
	//static void ColorPicker(int id, const char* text, ImVec2 size, float* color);
	//static void ComboBox(int id, const char* text, ImVec2 size, int* value, const char* items[], int listSize);
	//static void KeybindButton(int id, const char* text, ImVec2 size, int& keybind);
	//static bool Button(int id, const char* text, ImVec2 size);
	//static void Text(int id, const char* text, ImVec2 size, bool center = false);
	//static void TextColored(int id, const char* text, ImVec2 size, ImVec4 color, bool center = false);
	//static bool TextInput(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags = 0);
	//static bool TextInputButton(int id, const char* text, ImVec2 size, char* buf, size_t bufSize, ImGuiInputTextFlags flags = 0, const char* buttonText = "Save");
	//static void GlitchText(const char* text, ImVec2 pos, int size);


	static void Text(const char* text, FontSize size);
	static void BoldText(const char* text, FontSize size);
	static void GlitchText(const char* text, FontSize size);

	static void VerticalSeparator(const char* str_id, float size = 0, float thickness = 1.f);
	static void HorizontalSeparator(const char* str_id, float size = 0, float thickness = 1.);

	static bool TransparentButton(const char* text, ImVec2 btn_size, FontSize font_size);
	static bool MenuButton(const char* text, ImVec2 btn_size, FontSize font_size);
	static bool DetachButton(const char* text, ImVec2 btn_size, FontSize font_size);

	static void ToggleWithKeybind(bool* enabled, int& keybind, ImVec2 size = ImVec2(0, 0));

	static bool Slider(const char* label, int* value, int min, int max, ImVec2 size = ImVec2(0, 0), const char* format = "%d", ImGuiSliderFlags flags = 0);
	static bool Slider(const char* label, float* value, float min, float max, ImVec2 size = ImVec2(0, 0), const char* format = "%.2f", ImGuiSliderFlags flags = 0);

	static bool CheckboxBehavior(const char* label, bool* v);
	static bool Checkbox(const char* label, bool* v, ImVec2 size = ImVec2(0, 0));

	static void MoveCursorToCenter(bool checkInGame);

	static inline HWND HandleWindow;
	static inline HDC HandleDeviceContext;

	static inline HGLRC OriginalGLContext;
	static inline HGLRC MenuGLContext;

	static inline ImGuiContext* CurrentImGuiContext;

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

