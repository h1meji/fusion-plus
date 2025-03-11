#include "rightAutoClicker.h"
#include "sdk/sdk.h"
#include "menu/menu.h"
#include "util/logger/logger.h"
#include "menu/menu.h"

#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;

void RightAutoClicker::Update()
{
	if (!settings::RAC_Enabled) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	jclass blockClass;
	Java::AssignClass("net.minecraft.item.ItemBlock", blockClass);
	if (SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetInstance() == NULL) return;
	if (settings::RAC_blocksOnly && SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetItem().GetUnlocalizedName().find("tile") == std::string::npos) return;
	if (GetAsyncKeyState(VK_RBUTTON) && 0) return; // maybe fix the right click bug with this

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	if (GetAsyncKeyState(VK_RBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		rightLastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(settings::RAC_rightMinCps, settings::RAC_rightMaxCps);
		rightNextCps = distrib(gen);
	}
}

void RightAutoClicker::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("rac_header", ImVec2(425, renderSettings ? 120 : 35), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(25, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::RAC_Enabled);
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
			if (ImGui::BeginChild("rac_settings", ImVec2(425, 75), false))
			{
				Menu::Slider(26, "Min CPS", ImVec2(225, 0), &settings::RAC_rightMinCps, 1, settings::RAC_rightMaxCps);
				Menu::Slider(27, "Max CPS", ImVec2(225, 0), &settings::RAC_rightMaxCps, settings::RAC_rightMinCps, 20);
				Menu::ToggleButton(28, "Blocks Only", ImVec2(368, 0), &settings::RAC_blocksOnly);
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