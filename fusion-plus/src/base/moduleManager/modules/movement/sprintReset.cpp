#include "sprintReset.h"
#include "moduleManager/commonData.h"

#include "menu/menu.h"

inline static void send_key(WORD vk_key, bool send_down = true) {
	unsigned long dwFlags = send_down ? 0 : KEYEVENTF_KEYUP;
	static INPUT ip{ INPUT_KEYBOARD };
	ip.ki = {
		vk_key,     // wVk
		0,          // wScan
		dwFlags,    // dwFlags
		0,          // time
		0           // dwExtraInfo
	};
	SendInput(1, &ip, sizeof(INPUT));
}

void SprintReset::Update()
{
	std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> sinceStart = currentTime - startTime;
	if (sinceStart.count() > settings::SR_LetGoDelay && sprintResetInAction)
	{
		send_key(0x53, false);

		sprintResetInAction = false;
		pauseTime = std::chrono::steady_clock::now();
		return;
	}
	std::chrono::duration<double> sincePause = currentTime - pauseTime;
	if (sincePause.count() > settings::SR_DelayBetween && !can_sprint_reset)
	{
		can_sprint_reset = true;
		return;
	}

	if (!settings::SR_Enabled || !CommonData::SanityCheck() || SDK::Minecraft->IsInGuiState() || Menu::Open || Menu::OpenHudEditor)
	{
		return;
	}

	bool isPressingW = GetAsyncKeyState(0x57);
	bool attackedInput = GetAsyncKeyState(0x01);
	if (!isPressingW || !attackedInput || !SDK::Minecraft->thePlayer->IsSprinting())
	{
		return;
	}

	CEntity entity = SDK::Minecraft->GetMouseOver().GetEntityHit();
	if (entity.GetInstance() == nullptr)
	{
		return;
	}

	int currentHurtResistantTime = entity.GetHurtResistantTime();
	if (currentHurtResistantTime > 10)
	{
		if (!sprintResetInAction && can_sprint_reset)
		{
			send_key(0x53, true);

			sprintResetInAction = true;
			can_sprint_reset = false;
			startTime = std::chrono::steady_clock::now();
		}
	}
}

void SprintReset::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::SR_Enabled, settings::SR_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Delay Between S-Taps", &settings::SR_DelayBetween, 0.1f, 3.f);
	Menu::Slider("Let Go Delay", &settings::SR_LetGoDelay, .01f, .3f, ImVec2(0,0), "%.3f");
}
