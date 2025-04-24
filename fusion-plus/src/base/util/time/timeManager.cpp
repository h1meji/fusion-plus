#include "timeManager.h"

float TimeManager::m_lastTime = 0.0f;
float TimeManager::m_pausedTime = 0.0f;
bool TimeManager::m_isPaused = false;

float TimeManager::GetTime()
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
