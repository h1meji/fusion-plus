#include "borderless.h"

#include "menu/menu.h"

void Borderless::Enable(HWND hWindow)
{
	Borderless::enabled = true;
	Menu::open = false;
	Menu::openHudEditor = false;
	Borderless::originalStyle = GetWindowLongPtr(hWindow, GWL_STYLE);

	ShowWindow(hWindow, SW_MAXIMIZE);
	LONG_PTR currentStyle = GetWindowLongPtr(hWindow, GWL_STYLE);

	currentStyle &= ~(WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLongPtr(hWindow, GWL_STYLE, currentStyle);
	SetWindowPos(hWindow, hWindow, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_NOZORDER);
	SetForegroundWindow(hWindow);
}

void Borderless::Restore(HWND hWindow)
{
	Borderless::enabled = false;
	SetWindowLongPtr(hWindow, GWL_STYLE, Borderless::originalStyle);
	ShowWindow(hWindow, SW_SHOWDEFAULT);
	SetWindowPos(hWindow, hWindow, (GetSystemMetrics(SM_CXSCREEN) / 2) - 428, (GetSystemMetrics(SM_CYSCREEN) / 2) - 241, 856, 482, SWP_NOZORDER);
}


