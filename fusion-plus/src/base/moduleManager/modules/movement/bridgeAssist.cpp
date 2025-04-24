#include "bridgeAssist.h"

#include "menu/menu.h"
#include "util/logger/logger.h"
#include "util/keys.h"
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

static void sendShiftKey(HWND hWnd, bool sendDown)
{
	if (sendDown)
	{
		PostMessage(hWnd, WM_KEYDOWN, VK_SHIFT, static_cast<LPARAM>(MapVirtualKey(VK_SHIFT, 0) << 16));
	}
	else
	{
		PostMessage(hWnd, WM_KEYUP, VK_SHIFT, (static_cast<LPARAM>(MapVirtualKey(VK_SHIFT, 0)) << 16) | (static_cast<long long>(1) << 30) | (static_cast<long long>(1) << 31));
	}
}

void BridgeAssist::Update() // Thanks to Steve987321 @ https://github.com/Steve987321/toadclient for the idea / implementation.
{
	bool isSneaking = Keys::IsKeyPressed(VK_SHIFT); //(bool)GetAsyncKeyState(VK_SHIFT);

	if (!settings::BA_Enabled || !CommonData::SanityCheck() || SDK::minecraft->IsInGuiState())
	{
		if (!m_hasPressedShift && isSneaking && !settings::BA_OnlyOnShift)
		{
			UnSneak();
		}

		m_hasPressedShift = false;
		m_isBridging = false;
		return;
	}

	if (settings::BA_IgnoreForwardsMovement && (GetAsyncKeyState(0x57) & 0x8000))
	{
		if (!m_hasPressedShift && isSneaking && !settings::BA_OnlyOnShift)
		{
			UnSneak();
		}

		m_hasPressedShift = false;
		m_isBridging = false;
		return;
	}

	CItemStack item = SDK::minecraft->thePlayer->GetInventory().GetCurrentItem();
	if (item.GetInstance() == nullptr || item.GetItem().GetUnlocalizedName().find("tile") == std::string::npos)
	{
		bool found = false;
		if (m_isBridging && settings::BA_AutoSwap)
		{
			std::vector<CItemStack> hotbar = SDK::minecraft->thePlayer->GetInventory().GetMainInventory();
			for (int i = 0; i < 9; i++)
			{
				CItemStack stack = hotbar[i];
				if (stack.GetInstance() != nullptr && stack.GetItem().GetUnlocalizedName().find("tile") != std::string::npos)
				{
					SDK::minecraft->thePlayer->GetInventory().SetCurrentItemIndex(i);
					found = true;
					break;
				}
			}
		}

		if (!found)
		{
			if (!m_hasPressedShift && isSneaking && !settings::BA_OnlyOnShift)
			{
				UnSneak();
			}

			m_hasPressedShift = false;
			m_isBridging = false;
			return;
		}
	}

	if (settings::BA_OnlyOnShift)
	{
		if (!m_hasPressedShift && isSneaking)
		{
			m_hasPressedShift = true;
		}
	}

	if (CommonData::playerPitch < settings::BA_PitchCheck)
	{
		if (!m_hasPressedShift && isSneaking && !settings::BA_OnlyOnShift)
		{
			UnSneak();
		}

		m_hasPressedShift = false;
		m_isBridging = false;
		return;
	}

	if (settings::BA_OnlyOnShift && !m_hasPressedShift)
	{
		m_isBridging = false;
		return;
	}

	m_from = CommonData::playerPos;
	m_from.y += 1;
	Vector3 hitBlockPos;

	bool res = SDK::minecraft->theWorld->RayTraceBlocks(m_from, m_direction, hitBlockPos, false, false, false);

	// the vertical diff between the player and block under the player
	auto diffY = CommonData::playerPos.y - hitBlockPos.y;
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
		if (SDK::minecraft->thePlayer->GetMotion().y < 0.0f || diffY <= 0.0f)
			jumped = false;
		m_isBridging = false;
		return;
	}

	if (diffY != 0 && diffY <= settings::BA_BlockCheck - 1)
	{
		UnSneak();
		m_isBridging = false;
		return;
	}


	m_prev = m_isEdge;
	m_isEdge = false;

	bool isFalling = std::abs(SDK::minecraft->thePlayer->GetMotion().y) > 0.5f;

	if (!isFalling)
	{
		m_isBridging = true;
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
	Menu::ToggleWithKeybind(&settings::BA_Enabled, settings::BA_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Checkbox("Only on Shift", &settings::BA_OnlyOnShift);
	Menu::Checkbox("Ignore Forwards Movement", &settings::BA_IgnoreForwardsMovement);
	Menu::Checkbox("Auto Swap", &settings::BA_AutoSwap);
	Menu::Slider("Block Check", &settings::BA_BlockCheck, 1, 10);
	Menu::Slider("Pitch Check", &settings::BA_PitchCheck, 0.0f, 90.0f);
}

void BridgeAssist::Sneak()
{
	m_isEdge = true;
	if (!m_prev)
	{
		if (!settings::BA_OnlyOnShift) sendKey(VK_SHIFT, true);
		if (settings::BA_OnlyOnShift) sendShiftKey(Menu::handleWindow, true);
		m_prev = true;
	}
}

void BridgeAssist::UnSneak()
{
	m_isEdge = false;
	if (m_prev)
	{
		if (!settings::BA_OnlyOnShift) sendKey(VK_SHIFT, false);
		if (settings::BA_OnlyOnShift) sendShiftKey(Menu::handleWindow, false);
		m_prev = false;
	}
}
