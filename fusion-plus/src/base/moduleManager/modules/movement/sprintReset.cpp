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
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("sr_header", ImVec2(425.f, renderSettings ? 99.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(18, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::SR_Enabled);
	//	ImGui::EndGroup();
	//	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	//	{
	//		renderSettings = !renderSettings;
	//	}

	//	ImGui::PopStyleColor();
	//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

	//	if (renderSettings)
	//	{
	//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//		ImGui::Separator();
	//		if (ImGui::BeginChild("sr_settings", ImVec2(425, 54), false))
	//		{
	//			Menu::KeybindButton(171, "Keybind", ImVec2(297, 0), settings::SR_Key);
	//			Menu::Slider(19, "Delay Between S-Taps", ImVec2(225, 0), &settings::SR_DelayBetween, 0.1f, 3.f, "%.2f");
	//			Menu::Slider(20, "Let Go Delay", ImVec2(225, 0), &settings::SR_LetGoDelay, .01f, .3f, "%.3f");
	//		}
	//		ImGui::EndChild();
	//		ImGui::Spacing();
	//	}
	//}
	//ImGui::EndChild();

	//ImGui::PopStyleVar();
	//ImGui::PopStyleColor();

	//ImGui::EndGroup();
}
