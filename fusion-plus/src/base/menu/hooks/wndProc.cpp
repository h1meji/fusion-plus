#include "menu/menu.h"
#include "base.h"

#include "imgui/imgui_impl_win32.h"

#include "configManager/settings.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == Menu::Keybind)
		{
			if (Menu::Open || Menu::OpenHudEditor) Menu::MoveCursorToCenter(true);
			Menu::Open = !Menu::Open;
			Menu::OpenHudEditor = false;
		}

		//if (wParam == VK_ESCAPE && (Menu::Open || Menu::OpenHudEditor))
		//{
		//	Menu::MoveCursorToCenter(false);
		//	Menu::Open = false;
		//	Menu::OpenHudEditor = false;
		//}

		if (wParam == VK_END)
		{
			Base::Running = false;
		}
	}

	if ((Menu::Open || Menu::OpenHudEditor) && Menu::Initialized)
	{
		if (settings::Menu_GUIMovement)
		{
			// block imgui input from reaching minecraft
			if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
				return true;

			// block mouse move events from reaching minecraft
			if (msg == WM_MOUSEMOVE)
				return true;

			// block mouse click events from reaching minecraft
			if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN)
				return true;

			// block mouse scroll events from reaching minecraft
			if (msg == WM_MOUSEWHEEL)
				return true;

			// block "esc" key from reaching minecraft
			if (msg == WM_KEYDOWN && wParam == VK_ESCAPE)
				return true;
		}
		else
		{
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
			return true;
		}
	}

	return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}



void Menu::Hook_wndProc()
{
	original_wndProc = (template_WndProc)SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)hook_WndProc);
}

void Menu::Unhook_wndProc()
{
	SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}

void Menu::ResetSetupFlags()
{
	setupWatermarkFlag = std::make_unique<std::once_flag>();
	setupRadarFlag = std::make_unique<std::once_flag>();
	setupKeybindsFlag = std::make_unique<std::once_flag>();
}
