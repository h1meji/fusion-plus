#include "bridgeAssist.h"
#include <imgui/imgui.h>
#include <menu/menu.h>
#include <util/logger.h>
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

void BridgeAssist::Update() // Thanks to Steve987321 @ https://github.com/Steve987321/toadclient for the idea / implementation.
{
	bool isSneaking = (bool)GetAsyncKeyState(VK_SHIFT);

	if (!settings::BA_Enabled || !CommonData::SanityCheck() || SDK::Minecraft->IsInGuiState())
	{
		if (!m_has_pressed_shift && isSneaking)
			UnSneak();

		m_has_pressed_shift = false;
		return;
	}

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	CWorld* world = SDK::Minecraft->theWorld;

	CItemStack item = player->GetInventory().GetCurrentItem();
	if (item.GetInstance() == nullptr || item.GetItem().GetUnlocalizedName().find("tile") == std::string::npos)
	{
		if (!m_has_pressed_shift && isSneaking)
			UnSneak();

		m_has_pressed_shift = false;
		return;
	}

	if (settings::BA_OnlyOnShift)
	{
		if (!m_has_pressed_shift && isSneaking)
		{
			m_has_pressed_shift = true;
		}
	}

	if (player->GetRotationPitch() < settings::BA_PitchCheck)
	{
		if (!m_has_pressed_shift && isSneaking)
			UnSneak();

		m_has_pressed_shift = false;
		return;
	}

	if (settings::BA_OnlyOnShift && !m_has_pressed_shift)
	{
		return;
	}

	m_from = player->GetPos();
	m_from.y += 1;
	Vector3 hitBlockPos;

	bool res = world->rayTraceBlocks(m_from, m_direction, hitBlockPos, false, false, false);

	// the vertical diff between the player and block under the player
	auto diffY = player->GetPos().y - hitBlockPos.y;
	diffY -= 1;

	static bool jumped = false;
	if (GetAsyncKeyState(VK_SPACE) & 1)
	{
		jumped = true;
	}

	if (jumped)
	{
		UnSneak();

		// check if we are back on ground or going down
		if (player->GetMotion().y < 0.0f || diffY <= 0.0f)
			jumped = false;
		return;
	}

	if (diffY != 0 && diffY <= settings::BA_BlockCheck)
	{
		UnSneak();
		return;
	}


	m_prev = m_is_edge;
	m_is_edge = false;

	bool isFalling = std::abs(player->GetMotion().y) > 0.5f;

	if (!isFalling)
	{
		if (static_cast<int>(diffY) != 0 || res == false)
		{
			Sneak();
		}
		else
		{
			UnSneak();
		}
	}
	else
	{
		UnSneak();
	}
}

void BridgeAssist::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("bridgeassist", ImVec2(425, renderSettings ? 130 : 35)))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(230044, "Toggle Bridge Assist", &settings::BA_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();

			Menu::DoSliderStuff(34634645, "Block Check", &settings::BA_BlockCheck, 1, 10);

			Menu::DoSliderStuff(34634646, "Pitch Check", &settings::BA_PitchCheck, 0.0f, 90.0f);

			Menu::DoToggleButtonStuff(34634647, "Only on Shift", &settings::BA_OnlyOnShift);

			ImGui::Spacing();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void BridgeAssist::Sneak()
{
	m_is_edge = true;
	if (!m_prev)
	{
		send_key(VK_SHIFT, true);
		m_prev = true;
	}
}

void BridgeAssist::UnSneak()
{
	m_is_edge = false;
	if (m_prev)
	{
		send_key(VK_SHIFT, false);
		m_prev = false;
	}
}
