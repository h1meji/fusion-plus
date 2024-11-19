#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>

#include "base.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Base base;
    base.Run();
    return 0;
}