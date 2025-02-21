#include "leftAutoClicker.h"
#include "sdk/sdk.h"
#include "menu/menu.h"
#include "util/logger.h"
#include "menu/menu.h"

#include <chrono>
#include <random>
#include <util/minecraft.h>

long lastClickTime = 0;
int nextCps = 10;

void LeftAutoClicker::Update()
{
	static bool fix = false;
	if (!settings::LAC_Enabled) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	if (settings::LAC_swordOnly && !MinecraftUtils::IsWeapon(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem())) return;
	if (settings::LAC_emptyHandOnly && !MinecraftUtils::IsEmpty(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem())) return;
	if (settings::LAC_ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock())
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !fix) // fixes the issue where the autoclicker would not break blocks when already holding the mouse button
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

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(settings::LAC_leftMinCps , settings::LAC_leftMaxCps);
		nextCps = distrib(gen);

		if (settings::LAC_swordBlock && MinecraftUtils::IsWeapon(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem()))
		{
			static bool blocked = false;
			CEntity entity = SDK::Minecraft->GetMouseOver().GetEntityHit();
			if (entity.GetInstance() != nullptr)
			{
				if (entity.GetHurtResistantTime() > 11 && !blocked)
				{
					SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
					SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
					blocked = true;
				}
				else if (entity.GetHurtResistantTime() <= 11)
				{
					blocked = false;
				}
			}
		}
	}
}

void LeftAutoClicker::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("lac_header", ImVec2(425, renderSettings ? 120 : 35), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(21, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::LAC_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			if (ImGui::BeginChild("lac_settings", ImVec2(425, 75), false))
			{
				Menu::Slider(22, "Min CPS", ImVec2(225, 0), &settings::LAC_leftMinCps, 1, settings::LAC_leftMaxCps);
				Menu::Slider(23, "Max CPS", ImVec2(225, 0), &settings::LAC_leftMaxCps, settings::LAC_leftMinCps, 25);
				Menu::ToggleButton(24, "Ignore Blocks", ImVec2(368, 0), &settings::LAC_ignoreBlocks);
				Menu::ToggleButton(2501, "Sword Block", ImVec2(368, 0), &settings::LAC_swordBlock);
				Menu::ToggleButton(2502, "Sword Only", ImVec2(368, 0), &settings::LAC_swordOnly);
				Menu::ToggleButton(2503, "Empty Hand Only", ImVec2(368, 0), &settings::LAC_emptyHandOnly);
			}
			ImGui::EndChild();
			ImGui::Spacing();
		}
	}
	ImGui::EndChild();

	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	ImGui::EndGroup();
}