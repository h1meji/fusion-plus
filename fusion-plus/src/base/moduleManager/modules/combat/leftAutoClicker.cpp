#include "leftAutoClicker.h"
#include "sdk/sdk.h"
#include "menu/menu.h"
#include "util/logger.h"
#include "menu/menu.h"

#include <chrono>
#include <random>

long lastClickTime = 0;
int nextCps = 10;

void LeftAutoClicker::Update()
{
	static bool fix = false;
	if (!settings::LAC_Enabled) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	if (settings::LAC_ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock())
	{
		if ((GetAsyncKeyState(VK_LBUTTON) && 1) && !fix) // fixes the issue where the autoclicker would not break blocks when already holding the mouse button
		{
			POINT pos_cursor;
			GetCursorPos(&pos_cursor);
			SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			fix = true;
		}
		return;
	}
	fix = false;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;

	if (GetAsyncKeyState(VK_LBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(settings::LAC_leftMinCps , settings::LAC_leftMaxCps);
		nextCps = distrib(gen);
	}
}

void LeftAutoClicker::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("autoclicker", ImVec2(425, renderSettings ? 130 : 35))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(857834, "Toggle Left Auto Clicker", &settings::LAC_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			Menu::DoSliderStuff(3280, "Min CPS", &settings::LAC_leftMinCps, 1, settings::LAC_leftMaxCps);
			Menu::DoSliderStuff(675, "Max CPS", &settings::LAC_leftMaxCps, settings::LAC_leftMinCps, 20);
			Menu::DoToggleButtonStuff(2136, "Ignore Blocks", &settings::LAC_ignoreBlocks);
			ImGui::Spacing();
		}

	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}