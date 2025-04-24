#include "rightAutoClicker.h"

#include <chrono>
#include <random>

#include "sdk/sdk.h"
#include "menu/menu.h"
#include "util/logger/logger.h"

void RightAutoClicker::Update()
{
	if (!settings::RAC_Enabled) return;
	if (Menu::open) return;
	if (SDK::minecraft->IsInGuiState()) return;

	if (SDK::minecraft->thePlayer->GetInventory().GetCurrentItem().GetInstance() == NULL) return;
	if (settings::RAC_blocksOnly && SDK::minecraft->thePlayer->GetInventory().GetCurrentItem().GetItem().GetUnlocalizedName().find("tile") == std::string::npos) return;
	if (GetAsyncKeyState(VK_RBUTTON) && 0) return; // maybe fix the right click bug with this

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (m_lastClickTime == 0) m_lastClickTime = milli;
	if ((milli - m_lastClickTime) < (1000 / m_nextCps)) return;

	if (GetAsyncKeyState(VK_RBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::handleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::handleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		m_lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(settings::RAC_rightMinCps, settings::RAC_rightMaxCps);
		m_nextCps = distrib(gen);
	}
}

void RightAutoClicker::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::RAC_Enabled, settings::RAC_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Min CPS", &settings::RAC_rightMinCps, 1, settings::RAC_rightMaxCps);
	Menu::Slider("Max CPS", &settings::RAC_rightMaxCps, settings::RAC_rightMinCps, 25);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep2");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Checkbox("Blocks Only", &settings::RAC_blocksOnly);
}