#include "reach.h"
#include "sdk/sdk.h"
#include "moduleManager/commonData.h"
#include "util/logger/logger.h"
#include "java/java.h"
#include "util/math/math.h"
#include "imgui/imgui.h"
#include "menu/menu.h"
#include "patcher/patcher.h"

#include <chrono>


//https://github.com/Lefraudeur/RiptermsGhost

std::chrono::steady_clock::time_point lastUpdate;
void Reach::Update()
{
	if (Java::Version != MinecraftVersion::LUNAR_1_8_9)
	{
		if (settings::Reach_Enabled)
		{
			settings::Reach_Enabled = false;
			Logger::Log("Reach is only supported on Lunar CLient 1.8.9");
		}
		return;
	}

	static float prev_reach = -1.0f;
	if (!settings::Reach_Enabled)
	{
		if (!CommonData::SanityCheck()) return;
		if (prev_reach != -1.0f)
		{
			Patcher::put("reach_distance", "3.0");
			prev_reach = -1.0f;
		}
		return;
	}
	if (prev_reach == settings::Reach_ReachDistance || !CommonData::SanityCheck())
		return;
	prev_reach = settings::Reach_ReachDistance;
	Patcher::put("reach_distance", std::to_string(settings::Reach_ReachDistance));
}


void Reach::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::Reach_Enabled, settings::Reach_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Reach Distance", &settings::Reach_ReachDistance, 0.1f, 5.0f);
}
