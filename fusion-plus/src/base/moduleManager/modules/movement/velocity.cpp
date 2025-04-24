#include "velocity.h"

#include "menu/menu.h"
#include "moduleManager/commonData.h"

inline static void sendKey(WORD vkKey, bool sendDown = true)
{
	static INPUT ip{ INPUT_KEYBOARD };

	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = vkKey;
	ip.ki.dwFlags = sendDown ? 0 : KEYEVENTF_KEYUP;

	SendInput(1, &ip, sizeof(INPUT));
}

inline static int randInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void Velocity::Update()
{
	static int lastingTime = 0;
	if (lastingTime == 1)
	{
		sendKey(VK_SPACE, false);
		lastingTime = 0;
	}
	else if (lastingTime > 1)
	{
		lastingTime--;
	}

	if (!settings::Velocity_Enabled || !CommonData::SanityCheck() || SDK::minecraft->IsInGuiState())
	{
		return;
	}

	int hurtResistantTime = SDK::minecraft->thePlayer->GetHurtResistantTime();

	static bool canBeHit = true;
	if (!canBeHit && hurtResistantTime == 0)
	{
		canBeHit = true;
	}

	if (!canBeHit)
	{
		return;
	}

	if (hurtResistantTime <= 10)
	{
		return;
	}

	if (settings::Velocity_Mode == 0)
	{
		if (randInt(0, 100) <= settings::Velocity_JRChange)
		{
			sendKey(VK_SPACE);
			lastingTime = randInt(40, 70);
			canBeHit = false;
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
