#include "base.h"

#include <thread>

#include <minhook/minhook.h>

#include "main.h"
#include "java/java.h"
#include "java/hotspot/hotspot.h"
#include "java/javahook.h"
#include "util/logger/logger.h"
#include "util/minecraft/minecraft.h"
#include "util/math/math.h"
#include "util/window/borderless.h"
#include "util/keys.h"
#include "menu/menu.h"
#include "moduleManager/moduleManager.h"
#include "moduleManager/commonData.h"
#include "sdk/sdk.h"
#include "sdk/net/minecraft/client/ClientBrandRetriever.h"
#include "configManager/configManager.h"
#include "notificationManager/notificationManager.h"

static void drawLine(int x, int height, int padding)
{
	ImVec2 lineStart = ImVec2(x, settings::Hud_WatermarkPosition[1] + (padding * 1.5));
	ImVec2 lineEnd = ImVec2(x, settings::Hud_WatermarkPosition[1] + height - (padding * 1.5));
	ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(155, 155, 155, 255), 2);
}

static std::string floatToString(float value, int precision)
{
	if (value == NAN || value == INFINITY || value == -INFINITY) return "0";

	std::ostringstream out;
	out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

static std::string yawToDirection(float yaw)
{
	float warpedYaw = Math::WrapAngleTo180(yaw);

	// 0 = South, 45 = South-West, 90 = West, 135 = North-West, -180 = North, -135 = North-East, -90 = East, -45 = South-East
	if (warpedYaw >= -22.5 && warpedYaw < 22.5) return "S";
	if (warpedYaw >= 22.5 && warpedYaw < 67.5) return "SW";
	if (warpedYaw >= 67.5 && warpedYaw < 112.5) return "W";
	if (warpedYaw >= 112.5 && warpedYaw < 157.5) return "NW";
	if (warpedYaw >= 157.5 || warpedYaw < -157.5) return "N";
	if (warpedYaw >= -157.5 && warpedYaw < -112.5) return "NE";
	if (warpedYaw >= -112.5 && warpedYaw < -67.5) return "E";
	if (warpedYaw >= -67.5 && warpedYaw < -22.5) return "SE";

	return "N/A";
}

void Base::Init()
{
#ifdef _DEBUG
	Logger::Init();
#endif

	MH_Initialize();

	Java::Init();
	switch (Java::version)
	{
	case MinecraftVersion::LUNAR_1_8_9:
		LOG_INFO("Lunar Client 1.8.9 detected");
		break;
	case MinecraftVersion::LUNAR_1_7_10:
		LOG_INFO("Lunar Client 1.7.10 detected");
		break;
	case MinecraftVersion::VANILLA_1_8_9:
		LOG_INFO("Vanilla 1.8.9 detected");
		break;
	case MinecraftVersion::VANILLA_1_7_10:
		LOG_INFO("Vanilla 1.7.10 detected");
		break;
	case MinecraftVersion::FORGE_1_8_9:
		LOG_INFO("Forge 1.8.9 detected");
		break;
	case MinecraftVersion::FORGE_1_7_10:
		LOG_INFO("Forge 1.7.10 detected");
		break;
	case MinecraftVersion::UNKNOWN:
		LOG_INFO("Unknown Minecraft version detected");
		MessageBoxA(nullptr, "Unknown Minecraft version detected", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Shutdown();
		MH_Uninitialize();
		Java::Shutdown();
		FreeLibraryAndExitThread(Main::hModule, 0);
		break;
	default:
		LOG_INFO("Unknown Minecraft version detected");
		MessageBoxA(nullptr, "Unknown Minecraft version detected", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Shutdown();
		MH_Uninitialize();
		Java::Shutdown();
		FreeLibraryAndExitThread(Main::hModule, 0);
		break;
	}

	SDK::Init();

	if (!HotSpot::Init())
	{
		LOG_INFO("Failed to initialize HotSpot");
		MessageBoxA(nullptr, "Failed to initialize HotSpot", "fusion+", MB_OK | MB_ICONERROR);
		Logger::Shutdown();
		MH_Uninitialize();
		Java::Shutdown();
		FreeLibraryAndExitThread(Main::hModule, 0);
		return;
	}
	
	Menu::Init();

	g_moduleManager = std::make_unique<ModuleManager>();
	g_moduleManager->Init();

	MinecraftItems::Init();

	Base::m_running = true;

	while (Base::m_running)
	{
		//LOG_DEBUG("CHEAT LOOP!");
		if (Keys::IsKeyPressed(VK_END))
		{
			Base::m_running = false;
		}
		//LOG_DEBUG("Key Check Passed!");
		g_moduleManager->UpdateModules();
		//LOG_DEBUG("Modules Updated.");
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		//LOG_DEBUG("Slept!");
	}

	Main::Shutdown();
}	

void Base::Shutdown()
{
	if (Borderless::enabled) Borderless::Restore(Menu::handleWindow);
	JavaHook::Shutdown();
	SDK::Shutdown();
	Java::Shutdown();
	Menu::Shutdown();
	Logger::Shutdown();

	MH_Uninitialize();
}

void Base::renderLoop() // Runs every frame
{
	if (!Base::m_running || settings::Hud_DisableAllRendering) return;

	g_moduleManager->RenderOverlay();

	if (Menu::openHudEditor)
	{
		// Render a black background to make the HUD editor more visible
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), windowSize, IM_COL32(0, 0, 0, 100));
	}

	if (settings::Hud_Watermark)
	{
		std::time_t now = std::time(nullptr);
		std::tm localTime{};  // Declare a local std::tm struct
		localtime_s(&localTime, &now); // Pass the address of localTime
		char buffer[9]; // HH:mm:ss
		std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTime);

		const char* watermark = "Fusion+";
		std::string version = Base::m_version;
		std::string fps = std::to_string(CommonData::fps) + " FPS";
		std::string ping = std::to_string(CommonData::ping) + "ms";
		std::string coords = "X: " + floatToString(CommonData::playerPos.x, 1) + " Y: " + floatToString(CommonData::playerPos.y, 1) + " Z: " + floatToString(CommonData::playerPos.z, 1);
		std::string direction = yawToDirection(CommonData::playerYaw);
		std::string time = buffer;

		int margin = 10;
		int padding = 10;

		int watermarkSize = 24;
		int statsSize = 22;

		ImVec2 textSize = Menu::fontBold->CalcTextSizeA(watermarkSize, FLT_MAX, 0, watermark);
		ImVec2 versionSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, version.c_str());
		ImVec2 fpsSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, fps.c_str());
		ImVec2 pingSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, ping.c_str());
		ImVec2 coordsSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, coords.c_str());
		ImVec2 directionSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, direction.c_str());
		ImVec2 timeSize = Menu::fontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, "00:00:00"); // Use a fixed size for time, so the text doesn't jump around

		int totalTextWidth = textSize.x;
		if (settings::Hud_WatermarkVersion)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += versionSize.x;
		}
		if (settings::Hud_WatermarkFps)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += fpsSize.x;
		}
		if (settings::Hud_WatermarkPing)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += pingSize.x;
		}
		if (settings::Hud_WatermarkCoords)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += coordsSize.x;
		}
		if (settings::Hud_WatermarkDirection)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += directionSize.x;
		}
		if (settings::Hud_WatermarkTime)
		{
			totalTextWidth += padding * 2;
			totalTextWidth += timeSize.x;
		}

		ImVec2 rectSize = ImVec2(totalTextWidth + padding * 2, textSize.y + padding * 2);

		ImGuiWindowFlags windowFlags;
		if (!Menu::openHudEditor)
		{
			windowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMouseInputs;
		}
		else
		{
			windowFlags = 0;
		}

		std::call_once(*Menu::setupWatermarkFlag, [&]() {
			ImGui::SetNextWindowPos(ImVec2(settings::Hud_WatermarkPosition[0], settings::Hud_WatermarkPosition[1]));
			});

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

		ImGui::SetNextWindowSize(rectSize);
		ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | windowFlags);
		{
			settings::Hud_WatermarkPosition[0] = ImGui::GetWindowPos().x;
			settings::Hud_WatermarkPosition[1] = ImGui::GetWindowPos().y;

			ImVec2 textPos = ImVec2(settings::Hud_WatermarkPosition[0] + padding, settings::Hud_WatermarkPosition[1] + padding);
			Menu::GlitchText(watermark, textPos, watermarkSize);

			int currentX = textPos.x + textSize.x;
			if (settings::Hud_WatermarkVersion)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 versionTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, versionTextPos, IM_COL32(255, 255, 255, 255), version.c_str());

				currentX = versionTextPos.x + versionSize.x;
			}

			if (settings::Hud_WatermarkFps)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 fpsTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, fpsTextPos, IM_COL32(255, 255, 255, 255), fps.c_str());

				currentX = fpsTextPos.x + fpsSize.x;
			}

			if (settings::Hud_WatermarkPing)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 pingTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, pingTextPos, IM_COL32(255, 255, 255, 255), ping.c_str());

				currentX = pingTextPos.x + pingSize.x;
			}

			if (settings::Hud_WatermarkCoords)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 coordsTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, coordsTextPos, IM_COL32(255, 255, 255, 255), coords.c_str());

				currentX = coordsTextPos.x + coordsSize.x;
			}

			if (settings::Hud_WatermarkDirection)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 directionTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, directionTextPos, IM_COL32(255, 255, 255, 255), direction.c_str());

				currentX = directionTextPos.x + directionSize.x;
			}

			if (settings::Hud_WatermarkTime)
			{
				drawLine(currentX + padding, rectSize.y, padding);

				ImVec2 timeTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::fontBold, statsSize, timeTextPos, IM_COL32(255, 255, 255, 255), time.c_str());

				currentX = timeTextPos.x + timeSize.x;
			}
		}
		ImGui::End();

		ImGui::PopStyleVar();
	}

	g_moduleManager->RenderHud();

	NotificationManager::Render();
}