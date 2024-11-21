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
			float playerHeight = target.height - 0.1;
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
			float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));

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

	float eHeight = target.height - 0.1;
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
			data = renderPos - Vector3(0, 0.21, 0) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
		}
		else
		{
			targetPitch = targetPitchFoot;
			data = renderPos - Vector3(0, 0.23, 0) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
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
		std::uniform_int_distribution<> distrib(settings::LAC_leftMinCps, settings::LAC_leftMaxCps);
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
		float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * screenSize.x / 1.7325;

		ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), circleRadius, ImColor(settings::TB_fovCircleColor[0], settings::TB_fovCircleColor[1], settings::TB_fovCircleColor[2], settings::TB_fovCircleColor[3]), circleRadius / 3, 1);
	}

	if (settings::TB_aimAssistFeedback) {
		if (data.x == NAN) return;
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 w2s;
		if (CWorldToScreen::WorldToScreen(data, CommonData::modelView, CommonData::projection, screenSize.x, screenSize.y, w2s))
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

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("tagback", ImVec2(425, renderSettings ? 260 : 35))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(234402345634000, "Toggle Tag Back", &settings::TB_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			Menu::DoSliderStuff(23084562545, "FOV", &settings::TB_fov, 5.0f, 180.0f);
			Menu::DoSliderStuff(2314057445345, "Smoothness", &settings::TB_smooth, 1.0f, 90.0f);
			Menu::DoToggleButtonStuff(22645342, "Visbility Check", &settings::TB_visibilityCheck);

			Menu::DoComboBoxStuff(987983, "Target Priority", &settings::TB_targetPriority, settings::TB_targetPriorityList, 3);

			ImGui::Separator();

			Menu::DoToggleButtonStuff(5635678756247, "Adapt to strafing", &settings::TB_adaptive);
			Menu::DoSliderStuff(457323434, "Adaptive strafing offset", &settings::TB_adaptiveOffset, 0.1f, 15.f);
			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

			ImGui::Separator();
			Menu::DoSliderStuff(3464340056, "Yaw Randomness", &settings::TB_randomYaw, 0.0f, 10.0f);
			Menu::DoSliderStuff(54034352347, "Pitch Randomness", &settings::TB_randomPitch, 0.0f, 1);
			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

			Menu::DoToggleButtonStuff(3989843578, "Ignore Friends", &settings::TB_ignoreFriends);

			ImGui::Separator();
			Menu::DoToggleButtonStuff(76523436400, "FOV Circle", &settings::TB_fovCircle);
			if (settings::TB_fovCircle)
			{
				Menu::DoColorPickerStuff(4356354, "FOV Circle Color", settings::TB_fovCircleColor);
			}

			Menu::DoToggleButtonStuff(230476545677654654, "Feedback Line", &settings::TB_aimAssistFeedback);
			if (settings::TB_aimAssistFeedback)
			{
				Menu::DoColorPickerStuff(2745325, "Feedback Line Color", settings::TB_aimAssistFeedbackColor);
			}

			ImGui::Separator();

			Menu::DoToggleButtonStuff(934287539, "Auto Click", &settings::TB_autoClick);
			if (settings::TB_autoClick)
			{
				Menu::DoSliderStuff(98473, "Min CPS", &settings::TB_minCps, 1, settings::TB_maxCps);
				Menu::DoSliderStuff(984734, "Max CPS", &settings::TB_maxCps, settings::TB_minCps, 20);
			}

			ImGui::Spacing();
			ImGui::Spacing();
		}

	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
