#include "velocity.h"

#include <imgui/imgui.h>
#include "menu/menu.h"
#include <moduleManager/commonData.h>

inline void send_key(WORD vk_key, bool send_down = true)
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
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("velocity", ImVec2(425, renderSettings ? 130 : 35)))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(230044, "Toggle Velocity", &settings::Velocity_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();

			Menu::DoComboBoxStuff(9845739, "Mode", &settings::Velocity_Mode, settings::Velocity_ModeList, 1);

			if (settings::Velocity_Mode == 0)
			{
				Menu::DoSliderStuff(84528, "Reaction Time (ms)", &settings::Velocity_JRReactionTime, 0, 1000);
				Menu::DoSliderStuff(93845, "Chance %", &settings::Velocity_JRChange, 0, 100);
			}

			ImGui::Spacing();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
