#include "timeManager.h"

float TimeManager::lastTime = 0.0f;
float TimeManager::pausedTime = 0.0f;
bool TimeManager::isPaused = false;

float TimeManager::GetTime() {
    if (IsIconic(Menu::HandleWindow)) {
        if (!isPaused) {
            isPaused = true;
            pausedTime = lastTime;
        }
        return pausedTime;
    }
    
    isPaused = false;
    lastTime = ImGui::GetTime();
    return lastTime;
}
