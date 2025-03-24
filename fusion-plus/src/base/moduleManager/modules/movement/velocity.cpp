#include "velocity.h"

#include <imgui/imgui.h>
#include "menu/menu.h"
#include <moduleManager/commonData.h>

inline static void send_key(WORD vk_key, bool send_down = true)
{
	static INPUT ip{ INPUT_KEYBOARD };

	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = vk_key;
	ip.ki.dwFlags = send_down ? 0 : KEYEVENTF_KEYUP;

	SendInput(1, &ip, sizeof(INPUT));
}

void Velocity::Update()
{
	static int lasting_time = 0;
	if (lasting_time == 1)
	{
		send_key(VK_SPACE, false);
		lasting_time = 0;
	}
	else if (lasting_time > 1)
	{
		lasting_time--;
	}

	if (!settings::Velocity_Enabled || !CommonData::SanityCheck() || SDK::Minecraft->IsInGuiState())
	{
		return;
	}

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;

	int hurtResistantTime = player->GetHurtResistantTime();

	static bool can_be_hit = true;
	if (!can_be_hit && hurtResistantTime == 0)
	{
		can_be_hit = true;
	}

	if (!can_be_hit)
	{
		return;
	}

	if (hurtResistantTime <= 10)
	{
		return;
	}

	if (settings::Velocity_Mode == 0)
	{
		if (rand_int(0, 100) <= settings::Velocity_JRChange)
		{
			send_key(VK_SPACE);
			lasting_time = rand_int(40, 70);
			can_be_hit = false;
		}
	}
}

void Velocity::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::Velocity_Enabled, settings::Velocity_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Dropdown("Mode", settings::Velocity_ModeList, &settings::Velocity_Mode, 1);
	if (settings::Velocity_Mode == 0)
	{
		Menu::Slider("Reaction Time", &settings::Velocity_JRReactionTime, 0.f, 1000.f, ImVec2(0,0), "%.2f ms");
		Menu::Slider("Chance", &settings::Velocity_JRChange, 0, 100, ImVec2(0, 0), "%d%%");
	}
}
