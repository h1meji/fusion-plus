#pragma once

#include <vector>
#include <string>
#include <chrono>

struct NotificationManager
{
	struct Notification
	{
		std::string title;
		std::string message;
		std::chrono::time_point<std::chrono::system_clock> startTime;

		Notification(const char* t, const char* m, std::chrono::time_point<std::chrono::system_clock> s)
			: title(t), message(m), startTime(s) {}
	};

	static bool Render();
	static bool RenderNotification(Notification notification, int x, int y, int width, int height);

	static bool Send(const char* title, const char* format, ...);

	static inline std::vector<Notification> notifications;

	static inline const int maxNotifications = 3;
	static inline const float fontSize = 28;

	static inline const double ALIVE_TIME_S = 5;
	static inline const double SLIDE_OUT_TIME_S = 0.5;
	static inline const double SLIDE_IN_TIME_S = 0.5;
};

#define NotificationInfo(message, ...) NotificationManager::Send("Fusion+ :: Info", message, ##__VA_ARGS__)
#define NotificationWarning(message, ...) NotificationManager::Send("Fusion+ :: Warning", message, ##__VA_ARGS__)
#define NotificationError(message, ...) NotificationManager::Send("Fusion+ :: Error", message, ##__VA_ARGS__)