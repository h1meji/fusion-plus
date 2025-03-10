#pragma once
#include <imgui/imgui.h>
#include "menu/menu.h"

class TimeManager {
public:
    static float GetTime();
    
private:
    static float lastTime;
    static float pausedTime;
    static bool isPaused;
};
