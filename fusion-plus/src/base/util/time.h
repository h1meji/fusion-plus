#pragma once

#include <Windows.h>

#include <imgui/imgui.h>

#include "menu/menu.h"

struct Time
{
    static float GetTime()
    {
        if (IsIconic(Menu::handleWindow))
        {
            if (!m_isPaused)
            {
                m_isPaused = true;
                m_pausedTime = m_lastTime;
            }
            return m_pausedTime;
        }

        m_isPaused = false;
        m_lastTime = ImGui::GetTime();
        return m_lastTime;
    }

    static void Pause()
    {
        m_isPaused = true;
    }

    static void Resume()
    {
        m_isPaused = false;
    }

private:
    static inline float m_lastTime;
    static inline float m_pausedTime;
    static inline bool m_isPaused;
};
