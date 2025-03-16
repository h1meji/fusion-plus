#include "leftAutoClicker.h"
#include "sdk/sdk.h"
#include "menu/menu.h"
#include "util/logger/logger.h"
#include "menu/menu.h"

#include <chrono>
#include <random>
#include <util/minecraft/minecraft.h>

long lastClickTime = 0;
int nextCps = 10;
bool shouldDrop = false;
bool shouldSpike = false;

float normalCps = 0.0f;
float lastKurtosisValue = 0.0f;

void LeftAutoClicker::Update()
{
	static bool fix = false;
	if (!settings::LAC_Enabled) return;
	if (Menu::Open || Menu::OpenHudEditor) return;
	if (SDK::Minecraft->IsInGuiState() && !(settings::LAC_allowInventory && SDK::Minecraft->IsInInventory())) return;
	if (settings::LAC_weaponOnly && !MinecraftUtils::IsWeapon(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem())) return;
	if (settings::LAC_ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock())
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && !fix)
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

	std::random_device rd;
	std::mt19937 gen(rd());
	if (settings::LAC_advancedMode && settings::LAC_dropChance > 0)
	{
		std::uniform_real_distribution<> dropDist(0.0, 100.0);
		shouldDrop = dropDist(gen) < settings::LAC_dropChance;
	}
	else
	{
		shouldDrop = false;
	}

	if (settings::LAC_advancedMode && settings::LAC_spikeChance > 0)
	{
		std::uniform_real_distribution<> spikeDist(0.0, 100.0);
		shouldSpike = spikeDist(gen) < settings::LAC_spikeChance;
	}
	else
	{
		shouldSpike = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if (shouldDrop)
		{
			lastClickTime = milli;
			return;
		}

		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		lastClickTime = milli;

		float multiplier = SDK::Minecraft->IsInInventory() ? settings::LAC_inventoryMultiplier : 1.0f;

		if (settings::LAC_advancedMode)
		{
			float minCps = settings::LAC_leftMinCps * multiplier;
			float maxCps = settings::LAC_leftMaxCps * multiplier;

			if (shouldSpike)
			{
				maxCps = (std::min)(maxCps * settings::LAC_spikeMultiplier, 25.0f);
			}

			if (settings::LAC_kurtosis > 0)
			{
				float meanCps = (minCps + maxCps) / 2.0f;

				if (normalCps == 0.0f || std::abs(settings::LAC_kurtosis - lastKurtosisValue) > 0.1f)
				{
					std::normal_distribution<float> normalDist(meanCps, (maxCps - minCps) / (4.0f + settings::LAC_kurtosis * 2.0f));
					normalCps = normalDist(gen);
					lastKurtosisValue = settings::LAC_kurtosis;
				}

				std::normal_distribution<float> walkDist(0.0f, 0.5f);
				normalCps += walkDist(gen);

				normalCps = std::max<float>(minCps, std::min<float>(maxCps, normalCps));
				nextCps = static_cast<int>(normalCps);
			}
			else
			{
				std::uniform_int_distribution<> distrib(minCps, maxCps);
				nextCps = distrib(gen);
			}

			if (settings::LAC_burstEnabled)
			{
				std::uniform_real_distribution<> burstChanceDist(0.0, 100.0);
				if (burstChanceDist(gen) < settings::LAC_burstChance)
				{
					float meanCps = (settings::LAC_leftMinCps + settings::LAC_leftMaxCps) / 2.0f;
					nextCps = static_cast<int>(meanCps * multiplier);
				}
			}
		}
		else
		{
			std::uniform_int_distribution<> distrib(settings::LAC_leftMinCps * multiplier, settings::LAC_leftMaxCps * multiplier);
			nextCps = distrib(gen);
		}

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

	float childHeight = 35;
	if (renderSettings) {
		childHeight += 153;
		if (settings::LAC_advancedMode) {
			childHeight += 110;
		}
	}

	if (ImGui::BeginChild("lac_header", ImVec2(425, childHeight), false))
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
			if (ImGui::BeginChild("lac_settings", ImVec2(425, childHeight - 40), false))
			{
				Menu::KeybindButton(166, "Keybind", ImVec2(297, 0), settings::LAC_Key);
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