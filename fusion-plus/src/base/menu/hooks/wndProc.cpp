#include "menu/menu.h"

#include "base.h"
#include "configManager/settings.h"
#include "util/keys.h"

static bool mouseButtonUp(UINT msg)
{
	return msg == WM_LBUTTONUP || msg == WM_RBUTTONUP || msg == WM_MBUTTONUP || msg == WM_XBUTTONUP;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool listenForKeys = true;
	if (Menu::isBindingKey) listenForKeys = false;

	if (msg == WM_KEYDOWN && listenForKeys)
	{
		if (wParam == settings::Menu_Keybind)
		{
			if (Menu::open) Menu::MoveCursorToCenter(true);
			Menu::open = !Menu::open;
			Menu::openHudEditor = false;
		}

		if (wParam == VK_ESCAPE && Menu::open)
		{
			Menu::MoveCursorToCenter(true);
			Menu::open = false;
			Menu::openHudEditor = false;
		}

		if (wParam == settings::Menu_DetachKey)
		{
			Base::m_running = false;
			Menu::MoveCursorToCenter(true);
		}
	}

	if ((msg == WM_KEYUP || mouseButtonUp(msg)) && !Menu::isBindingKey)
	{
		listenForKeys = true;
	}

	if (Menu::open && Menu::initialized)
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
	original_wndProc = (template_WndProc)SetWindowLongPtr(Menu::handleWindow, GWLP_WNDPROC, (LONG_PTR)hook_WndProc);
}

void Menu::Unhook_wndProc()
{
	SetWindowLongPtr(Menu::handleWindow, GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}

void Menu::ResetSetupFlags()
{
	setupWatermarkFlag = std::make_unique<std::once_flag>();
	setupRadarFlag = std::make_unique<std::once_flag>();
	setupKeybindsFlag = std::make_unique<std::once_flag>();
}
