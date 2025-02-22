#include "tagBack.h"
#include <moduleManager/commonData.h>
#include "menu/menu.h"
#include <util/math/math.h>
#include <configManager/configManager.h>
#include <util/math/worldToScreen.h>

#include <chrono>
#include <random>

// ! this is just a crappy combination of the aim assist and left auto clicker modules

void TagBack::Update()
{
	if (!settings::TB_Enabled) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	if (Menu::Open) return;

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	// check if the head contains a tnt
	std::vector<CItemStack> armorInventory = thePlayer->GetInventory().GetArmorInventory();

	if (armorInventory[3].GetItem().GetInstance() == nullptr) return;
	if (armorInventory[3].GetItem().GetUnlocalizedName() != "tile.tnt") return;

	Vector3 pos = thePlayer->GetPos();
	Vector3 headPos = thePlayer->GetEyePos();
	Vector2 currentLookAngles = thePlayer->GetAngles();

	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	CommonData::PlayerData target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = 3.5f;

	auto randomFloat = [](float min, float max)
		{
			float f = (float)rand() / RAND_MAX;
			return min + f * (max - min);
		};

	for (CommonData::PlayerData player : playerList)
	{
		if (!Java::Env->IsSameObject(thePlayer->GetInstance(), player.obj.GetInstance()) && !(settings::TB_ignoreFriends && ConfigManager::IsFriend(player.name))) {

			if (player.headItem.GetInstance() != nullptr)
			{
				if (player.headItem.GetUnlocalizedName() == "tile.tnt") continue;
			}

			if (!thePlayer->CanEntityBeSeen(player.obj.GetInstance()) && settings::TB_visibilityCheck) continue;
			Vector3 playerPos = player.pos;
			float playerHeight = target.height - 0.1f;
			Vector3 playerHeadPos = playerPos + Vector3(0, playerHeight, 0);

			Vector2 anglesFoot = Math::getAngles(headPos, playerPos);
			Vector2 anglesHead = Math::getAngles(headPos, playerHeadPos);

			Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());
			if (differenceFoot.x < 0) differenceFoot.x = -differenceFoot.x;
			if (differenceFoot.y < 0) differenceFoot.y = -differenceFoot.y;

			float angleYaw = currentLookAngles.x - difference.x;

			Vector3 diff = pos - playerPos;
			float dist = sqrt(pow(diff.x, 2.f) + pow(diff.y, 2.f) + pow(diff.z, 2.f));

			if ((abs(difference.x) <= settings::TB_fov) && dist <= realAimDistance)
			{
				float health = player.health;
				switch (settings::TB_targetPriority)
				{
				case 1:
					if (finalHealth > health)
					{
						target = player;
						finalHealth = health;
					}
					break;

				case 2:
					if (finalDiff > difference.x)
					{
						target = player;
						finalDiff = difference.x;
					}
					break;
				default:
					if (finalDist > dist)
					{
						target = player;
						finalDist = (float)dist;
					}
				}
			}
		}
	}

	if (!target.obj.GetInstance()) {
		Vector3 null;
		data = null;
		return;
	}

	Vector3 ePos = target.pos;
	Vector3 eLastPos = target.lastPos;

	float eHeight = target.height - 0.1f;
	Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
	Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


	Vector2 anglesFoot = Math::getAngles(headPos, ePos);
	Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

	Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
	Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

	float offset = randomFloat(-settings::TB_randomYaw, settings::TB_randomYaw);
	if (settings::TB_adaptive) {
		if ((GetAsyncKeyState('D') & 0x8000) && !(GetAsyncKeyState('A') & 0x8000)) {
			offset -= settings::TB_adaptiveOffset;
		}

		if ((GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000)) {
			offset += settings::TB_adaptiveOffset;
		}
	}

	float targetYaw = currentLookAngles.x + ((difference.x + offset) / settings::TB_smooth);

	Vector3 renderPos = CommonData::renderPos;
	float renderPartialTicks = CommonData::renderPartialTicks;

	if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y) {
		float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / settings::TB_smooth);
		float targetPitchHead = currentLookAngles.y + (difference.y / settings::TB_smooth);

		float diffFoot = currentLookAngles.y - targetPitchFoot;
		float diffHead = currentLookAngles.y - targetPitchHead;
		diffFoot = diffFoot < 0 ? -diffFoot : diffFoot;
		diffHead = diffHead < 0 ? -diffHead : diffHead;

		float targetPitch;
		if (diffFoot > diffHead)
		{
			targetPitch = targetPitchHead;
			data = renderPos - Vector3(0.f, 0.21f, 0.f) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
		}
		else
		{
			targetPitch = targetPitchFoot;
			data = renderPos - Vector3(0.f, 0.23f, 0.f) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		}
		pitchInfluenced = true;
		targetPitch += randomFloat(-settings::TB_randomPitch, settings::TB_randomPitch);
		thePlayer->SetAngles(Vector2(targetYaw, targetPitch));
	}
	else {
		data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		pitchInfluenced = false;
		thePlayer->SetAngles(Vector2(targetYaw, currentLookAngles.y + randomFloat(-settings::TB_randomPitch, settings::TB_randomPitch)));

		long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (lastClickTime == 0) lastClickTime = milli;
		if ((milli - lastClickTime) < (1000 / nextCps)) return;

		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib((int)settings::LAC_leftMinCps, (int)settings::LAC_leftMaxCps);
		nextCps = distrib(gen);
	}
}

void TagBack::RenderUpdate()
{
	if (!settings::TB_Enabled || !CommonData::dataUpdated) return;
	if (settings::TB_fovCircle) {

		ImVec2 screenSize = ImGui::GetWindowSize();
		float radAimbotFov = (float)(settings::TB_fov * PI / 180);
		float radViewFov = (float)(CommonData::fov * PI / 180);
		float circleRadius = tanf(radAimbotFov / 2.f) / tanf(radViewFov / 2.f) * screenSize.x / 1.7325f;

		ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), circleRadius, ImColor(settings::TB_fovCircleColor[0], settings::TB_fovCircleColor[1], settings::TB_fovCircleColor[2], settings::TB_fovCircleColor[3]), (int)(circleRadius / 3.f), 1.f);
	}

	if (settings::TB_aimAssistFeedback) {
		if (data.x == NAN) return;
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 w2s;
		if (CWorldToScreen::WorldToScreen(data, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, w2s))
		{
			if (w2s.x == NAN) return;

			if (pitchInfluenced)
			{
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, w2s.y), ImColor(settings::TB_aimAssistFeedbackColor[0], settings::TB_aimAssistFeedbackColor[1], settings::TB_aimAssistFeedbackColor[2], settings::TB_aimAssistFeedbackColor[3]), 1.5);
			}
			else {
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, screenSize.y / 2), ImColor(settings::TB_aimAssistFeedbackColor[0], settings::TB_aimAssistFeedbackColor[1], settings::TB_aimAssistFeedbackColor[2], settings::TB_aimAssistFeedbackColor[3]), 1.5);
			}
		}
	}
}

void TagBack::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("tb_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(86, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::TB_Enabled);
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
			if (ImGui::BeginChild("tb_settings", ImVec2(425, 215), false))
			{
				Menu::Slider(87, "FOV", ImVec2(225, 0), &settings::TB_fov, 5.0f, 180.0f);
				Menu::Slider(89, "Smoothness", ImVec2(225, 0), &settings::TB_smooth, 1.0f, 90.0f);

				Menu::ToggleButton(90, "Visbility Check", ImVec2(368, 0), &settings::TB_visibilityCheck);

				Menu::ComboBox(91, "Target Priority", ImVec2(270, 0), &settings::TB_targetPriority, settings::TB_targetPriorityList, 3);

				ImGui::Separator();

				Menu::ToggleButton(92, "Adapt to strafing", ImVec2(368, 0), &settings::TB_adaptive);
				Menu::Slider(93, "Adaptive strafing offset", ImVec2(225, 0), &settings::TB_adaptiveOffset, 0.1f, 15.f);
				ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

				ImGui::Separator();

				Menu::Slider(94, "Yaw Randomness", ImVec2(225, 0), &settings::TB_randomYaw, 0.0f, 10.0f);
				Menu::Slider(95, "Pitch Randomness", ImVec2(225, 0), &settings::TB_randomPitch, 0.0f, 1);
				ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

				ImGui::Separator();

				Menu::ToggleButton(96, "FOV Circle", ImVec2(368, 0), &settings::TB_fovCircle);
				if (settings::TB_fovCircle)
				{
					Menu::ColorPicker(97, "FOV Circle Color", ImVec2(374, 0), settings::TB_fovCircleColor);
				}

				Menu::ToggleButton(98, "Feedback Line", ImVec2(368, 0), &settings::TB_aimAssistFeedback);
				if (settings::TB_aimAssistFeedback)
				{
					Menu::ColorPicker(99, "Feedback Line Color", ImVec2(374, 0), settings::TB_aimAssistFeedbackColor);
				}

				Menu::ToggleButton(100, "Ignore Friends", ImVec2(368, 0), &settings::TB_ignoreFriends);

				ImGui::Separator();

				Menu::ToggleButton(101, "Auto Click", ImVec2(368, 0), &settings::TB_autoClick);
				if (settings::TB_autoClick)
				{
					Menu::Slider(102, "Min CPS", ImVec2(225, 0), &settings::TB_minCps, 1, settings::TB_maxCps);
					Menu::Slider(103, "Max CPS", ImVec2(225, 0), &settings::TB_maxCps, settings::TB_minCps, 25);
				}
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
