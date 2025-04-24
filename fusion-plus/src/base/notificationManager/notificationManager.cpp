#include "notificationManager.h"

#include <cstdarg>

#include "menu/menu.h"
#include "util/logger.h"

bool NotificationManager::Render()
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    const int padding = 5;
    const int margin = 10;
    int x = windowSize.x, y = windowSize.y;

    for (int i = 0; i < notifications.size(); i++)
    {
        Notification notification = notifications[i];

        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        
        std::chrono::duration<double> diff = now - notification.startTime;

        if (diff.count() > ALIVE_TIME_S)
        {
            notifications.erase(notifications.begin() + i);
        }

        ImVec2 msgSize = Menu::font->CalcTextSizeA(fontSize - 8, FLT_MAX, 0.0f, notification.title.c_str());
        ImVec2 titleSize = Menu::font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, notification.message.c_str());

        int width = max(max(300, msgSize.x), titleSize.x);
        int height = margin * 2 + msgSize.y;

        x = windowSize.x - padding - width;
        y = y - height - padding;

        if (diff.count() < SLIDE_IN_TIME_S)
        {
            x = windowSize.x + ((x - windowSize.x) / SLIDE_IN_TIME_S) * diff.count();
        }
        else if (diff.count() >= (ALIVE_TIME_S - SLIDE_OUT_TIME_S))
        {
            x = x - ((x - windowSize.x) / SLIDE_OUT_TIME_S) * (diff.count() - (ALIVE_TIME_S - SLIDE_OUT_TIME_S));
        }

        RenderNotification(notification, x, y, width, height);
    }

    return true;
}

bool NotificationManager::RenderNotification(Notification notification, int x, int y, int width, int height)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), ImColor(0.0f, 0.0f, 0.0f, 0.8f), 5.0f);

    ImGui::GetWindowDrawList()->AddText(Menu::font, fontSize - 8, ImVec2(x + 10, y + 10), ImColor(1.0f, 1.0f, 1.0f), notification.message.c_str());

    return true;
}

bool NotificationManager::Send(const char* title, const char* format, ...)
{
    std::va_list args;
    va_start(args, format);
    char messageBuffer[1024];
    std::vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);
    va_end(args);

    // check if the notifications len is larget than maxNotifications, if so remove the first one
    if (notifications.size() >= maxNotifications)
    {
        notifications.erase(notifications.begin());
    }

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    notifications.push_back(Notification(title, messageBuffer, now));

    return true;
}
