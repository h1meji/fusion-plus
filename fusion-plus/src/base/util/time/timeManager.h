#pragma once

#include <imgui/imgui.h>

#include "menu/menu.h"

class TimeManager {
public:
    static float GetTime();
    
private:
    static float m_lastTime;
    static float m_pausedTime;
    static bool m_isPaused;
};
