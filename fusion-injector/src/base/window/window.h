#ifndef WINDOW_H
#define WINDOW_H

#include <d3d9.h>
#include <windows.h>

#include "screen/screen.h"

class Window {
public:
    void Init();
    bool Update();
    void Cleanup();

private:
    // Direct3D data
    LPDIRECT3D9 g_pD3D = nullptr;
    LPDIRECT3DDEVICE9 g_pd3dDevice = nullptr;
    D3DPRESENT_PARAMETERS g_d3dpp = {};
    bool g_DeviceLost = false;

    HWND hwnd = nullptr;

    void Render();

    // Helper functions
    bool CreateDeviceD3D(HWND hWnd);
    void CleanupDeviceD3D();
    void ResetDevice();
    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Screen screen;
};

#endif // WINDOW_H
