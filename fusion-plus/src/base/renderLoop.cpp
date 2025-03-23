#include "base.h"
#include "sdk/sdk.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

#include "moduleManager/moduleManager.h"
#include "notificationManager/notificationManager.h"
#include <util/window/windowHelpers.h>
#include <moduleManager/commonData.h>
#include <util/math/math.h>
#include <ctime>

static void DrawLine(int x, int height, int padding)
{
	ImVec2 lineStart = ImVec2(x, settings::Hud_WatermarkPosition[1] + (padding * 1.5));
	ImVec2 lineEnd = ImVec2(x, settings::Hud_WatermarkPosition[1] + height - (padding * 1.5));
	ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(155, 155, 155, 255), 2);
}

static std::string floatToString(float value, int precision) {
	if (value == NAN || value == INFINITY || value == -INFINITY) return "0";

	std::ostringstream out;
	out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

static std::string yawToDirection(float yaw)
{
	float warpedYaw = Math::wrapAngleTo180(yaw);

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

void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running || settings::Hud_DisableAllRendering) return;

	g_ModuleManager->RenderOverlay();

	if (Menu::OpenHudEditor)
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
		std::string version = Base::version;
		std::string fps = std::to_string(CommonData::fps) + " FPS";
		std::string ping = std::to_string(CommonData::ping) + "ms";
		std::string coords = "X: " + floatToString(CommonData::playerPos.x, 1) + " Y: " + floatToString(CommonData::playerPos.y, 1) + " Z: " + floatToString(CommonData::playerPos.z, 1);
		std::string direction = yawToDirection(CommonData::playerYaw);
		std::string time = buffer;

		int margin = 10;
		int padding = 10;

		int watermarkSize = 24;
		int statsSize = 22;

		ImVec2 textSize = Menu::FontBold->CalcTextSizeA(watermarkSize, FLT_MAX, 0, watermark);
		ImVec2 versionSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, version.c_str());
		ImVec2 fpsSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, fps.c_str());
		ImVec2 pingSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, ping.c_str());
		ImVec2 coordsSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, coords.c_str());
		ImVec2 directionSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, direction.c_str());
		ImVec2 timeSize = Menu::FontBold->CalcTextSizeA(statsSize, FLT_MAX, 0, time.c_str());

		int totalTextWidth = textSize.x;
		if (settings::Hud_WatermarkVersion)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += versionSize.x + padding * 2;
		}
		if (settings::Hud_WatermarkFps)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += fpsSize.x + padding * 2;
		}
		if (settings::Hud_WatermarkPing)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += pingSize.x + padding * 2;
		}
		if (settings::Hud_WatermarkCoords)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += coordsSize.x + padding * 2;
		}
		if (settings::Hud_WatermarkDirection)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += directionSize.x + padding * 2;
		}
		if (settings::Hud_WatermarkTime)
		{
			totalTextWidth += 4; // line width
			totalTextWidth += timeSize.x + padding * 2;
		}

		ImVec2 rectSize = ImVec2(totalTextWidth + padding * 2, textSize.y + padding * 2);

		ImGuiWindowFlags windowFlags;
		if (!Menu::OpenHudEditor)
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
			//Menu::GlitchText(watermark, textPos, watermarkSize);

			int currentX = textPos.x + textSize.x;
			if (settings::Hud_WatermarkVersion)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 versionTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, versionTextPos, IM_COL32(255, 255, 255, 255), version.c_str());

				currentX = versionTextPos.x + versionSize.x;
			}

			if (settings::Hud_WatermarkFps)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 fpsTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, fpsTextPos, IM_COL32(255, 255, 255, 255), fps.c_str());

				currentX = fpsTextPos.x + fpsSize.x;
			}

			if (settings::Hud_WatermarkPing)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 pingTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, pingTextPos, IM_COL32(255, 255, 255, 255), ping.c_str());

				currentX = pingTextPos.x + pingSize.x;
			}

			if (settings::Hud_WatermarkCoords)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 coordsTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, coordsTextPos, IM_COL32(255, 255, 255, 255), coords.c_str());

				currentX = coordsTextPos.x + coordsSize.x;
			}

			if (settings::Hud_WatermarkDirection)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 directionTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, directionTextPos, IM_COL32(255, 255, 255, 255), direction.c_str());

				currentX = directionTextPos.x + directionSize.x;
			}

			if (settings::Hud_WatermarkTime)
			{
				DrawLine(currentX + padding, rectSize.y, padding);

				ImVec2 timeTextPos = ImVec2(currentX + padding * 2, textPos.y + 1);
				ImGui::GetWindowDrawList()->AddText(Menu::FontBold, statsSize, timeTextPos, IM_COL32(255, 255, 255, 255), time.c_str());

				currentX = timeTextPos.x + timeSize.x;
			}
		}
		ImGui::End();

		ImGui::PopStyleVar();
	}

	g_ModuleManager->RenderHud();

	NotificationManager::Render();
}