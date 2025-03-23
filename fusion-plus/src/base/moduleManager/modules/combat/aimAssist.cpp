#include "aimAssist.h"
#include "moduleManager/commonData.h"
#include "sdk/sdk.h"
#include "util/logger/logger.h"
#include "imgui/imgui.h"
#include "util/math/worldToScreen.h"
#include "util/math/math.h"
#include "menu/menu.h"
#include "java/java.h"

#include <chrono>
#include <random>
#include <configManager/configManager.h>
#include <util/minecraft/minecraft.h>

static bool IsMouseMoving()
{
	static POINT lastMousePos;
	POINT currentMousePos;
	GetCursorPos(&currentMousePos);

	if (lastMousePos.x == currentMousePos.x && lastMousePos.y == currentMousePos.y)
	{
		return false;
	}

	lastMousePos = currentMousePos;
	return true;
}

/* 
How this Aim Assist works :

Essentially its a basic aim assist with smoothing, except that there are 2 aim angles caluclated, one at the feet and one at the head.
The reason why this is done is because if you notice while using fusions aim assist, you're free to move your pitch up and down when targetting a player,
however it does not allow you to exceed the players head or feet, meaning you would always be aiming at the player, however freely be able to look at any part of the players body.

Although this can bypass some servers, it does not bypass all of them.
This is because some anticheats don't really give a damn where you are aiming, they mostly want to see how you rotate when you move, and that is where they catch you.

I (deadshell) can create a bypass for it in the future.

For now, if you want to use fusion, just use it with weak settings.

Suggested settings:
30-40 FOV
15-30 Smooth
3.5 - 4 Locking Distance
*/
void AimAssist::Update()
{
	if (!settings::AA_Enabled) return;
	if (Menu::Open || Menu::OpenHudEditor) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	// Checks
	if (settings::AA_sprintCheck && !SDK::Minecraft->thePlayer->IsSprinting()) {
		AimAssist::data = Vector3();
		return;
	}
	if (settings::AA_blockBreakCheck && SDK::Minecraft->GetMouseOver().IsTypeOfBlock()) {
		AimAssist::data = Vector3();
		return;
	}
	if (settings::AA_weaponOnly && !MinecraftUtils::IsWeapon(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem())) {
		AimAssist::data = Vector3();
		return;
	}

	if ((settings::AA_mousePressCheck && (!GetAsyncKeyState(VK_LBUTTON) && 1))) {
		AimAssist::data = Vector3();
		return;
	}

	if (!IsMouseMoving() && settings::AA_mouseMoveCheck) {
		AimAssist::data = Vector3();
		return;
	}

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	Vector3 pos = thePlayer->GetPos();
	Vector3 headPos = thePlayer->GetEyePos();
	Vector2 currentLookAngles = thePlayer->GetAngles();

	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	CommonData::PlayerData target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = settings::AA_aimDistance;

	// The code from here and below is kind of dog water, however it does the job.
	// The real math for the aim angles if you're interested is located in Math::getAngles()
	// fusion/src/base/util/math/Math.cpp
	auto randomFloat = [](float min, float max)
	{
		float f = (float)rand() / RAND_MAX;
		return min + f * (max - min);
	};


	for (CommonData::PlayerData player : playerList)
	{
		if (!Java::Env->IsSameObject(thePlayer->GetInstance(), player.obj.GetInstance()) && !(settings::AA_ignoreFriends && ConfigManager::IsFriend(player.name))) {
			if (!thePlayer->CanEntityBeSeen(player.obj.GetInstance()) && settings::AA_visibilityCheck) continue;
			if (player.obj.IsInvisibleToPlayer(thePlayer->GetInstance()) && settings::AA_invisibleCheck) continue;

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

			if ((abs(difference.x) <= settings::AA_fov) && dist <= realAimDistance)
			{
				float health = player.health;
				switch(settings::AA_targetPriority)
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

	float offset = randomFloat(-settings::AA_randomYaw, settings::AA_randomYaw);
	if (settings::AA_adaptive) {
		if ((GetAsyncKeyState('D') & 0x8000) && !(GetAsyncKeyState('A') & 0x8000)) {
			offset -= settings::AA_adaptiveOffset;
		}

		if ((GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000)) {
			offset += settings::AA_adaptiveOffset;
		}
	}

	float targetYaw = currentLookAngles.x + ((difference.x + offset) / settings::AA_smooth);

	Vector3 renderPos = CommonData::renderPos;
	float renderPartialTicks = CommonData::renderPartialTicks;

	if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y) {
		float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / settings::AA_smooth);
		float targetPitchHead = currentLookAngles.y + (difference.y / settings::AA_smooth);

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
		targetPitch += randomFloat(-settings::AA_randomPitch, settings::AA_randomPitch);
		thePlayer->SetAngles(Vector2(targetYaw, targetPitch));
	}
	else {
		data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		pitchInfluenced = false;
		thePlayer->SetAngles(Vector2(targetYaw, currentLookAngles.y + randomFloat(-settings::AA_randomPitch, settings::AA_randomPitch)));
	}
}

void AimAssist::RenderOverlay()
{
	if (!settings::AA_Enabled || !CommonData::dataUpdated) return;
	if (settings::AA_fovCircle) {

		ImVec2 screenSize = ImGui::GetWindowSize();
		float radAimbotFov = (float)(settings::AA_fov * PI / 180);
		float radViewFov = (float)(CommonData::fov * PI / 180);
		float circleRadius = tanf(radAimbotFov / 2.f) / tanf(radViewFov / 2.f) * screenSize.x / 1.7325f;

		ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2.f, screenSize.y / 2.f), circleRadius, ImColor(settings::AA_fovCircleColor[0], settings::AA_fovCircleColor[1], settings::AA_fovCircleColor[2], settings::AA_fovCircleColor[3]), (int)(circleRadius / 3.f), 1.f);
	}

	if (settings::AA_aimAssistFeedback) {
		if (data.x == NAN) return;
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 w2s;
		if (CWorldToScreen::WorldToScreen(data, CommonData::modelView, CommonData::projection, screenSize.x, screenSize.y, w2s))
		{
			if (w2s.x == NAN) return;

			if (pitchInfluenced)
			{
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, w2s.y), ImColor(settings::AA_aimAssistFeedbackColor[0], settings::AA_aimAssistFeedbackColor[1], settings::AA_aimAssistFeedbackColor[2], settings::AA_aimAssistFeedbackColor[3]), 1.5);
			}
			else {
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, screenSize.y / 2), ImColor(settings::AA_aimAssistFeedbackColor[0], settings::AA_aimAssistFeedbackColor[1], settings::AA_aimAssistFeedbackColor[2], settings::AA_aimAssistFeedbackColor[3]), 1.5);
			}
		}
	}
}

void AimAssist::RenderMenu()
{
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f); // Manual window padding

	ImGui::SetCursorPosX(20.f);
	Menu::ToggleWithKeybind(&settings::AA_Enabled, settings::AA_Key);

	ImGui::SetCursorPosX(20.f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("AA_Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	ImGui::SetCursorPosX(20.f);
	Menu::Slider("Smoothness", &settings::AA_smooth, 1.0f, 90.0f);

	ImGui::SetCursorPosX(20.f);
	Menu::Slider("FOV", &settings::AA_fov, 5.0f, 180.f);

	ImGui::SetCursorPosX(20.f);
	Menu::Slider("Lock Distance", &settings::AA_aimDistance, 1.0f, 10.0f);

	ImGui::SetCursorPosX(20.f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("AA_Sep2");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	ImGui::SetCursorPosX(20.f);
	Menu::Slider("Yaw Randomness", &settings::AA_randomYaw, 0.0f, 10.0f);

	ImGui::SetCursorPosX(20.f);
	Menu::Slider("Pitch Randomness", &settings::AA_randomPitch, 0.0f, 1.0f);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Adapt to strafing", &settings::AA_adaptive);

	if (settings::AA_adaptive)
	{
		ImGui::SetCursorPosX(20.f);
		Menu::Slider("Adaptive Strafing Offset", &settings::AA_adaptiveOffset, 0.0f, 15.f);
	}

	ImGui::SetCursorPosX(20.f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("AA_Sep3");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Weapon Only", &settings::AA_weaponOnly);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Ignore Friends", &settings::AA_ignoreFriends);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Visiblity Check", &settings::AA_visibilityCheck);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Ignore Invisible", &settings::AA_invisibleCheck);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Allow Block Breaking", &settings::AA_blockBreakCheck);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Sprinting Only", &settings::AA_sprintCheck);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Mouse Press Check", &settings::AA_mousePressCheck);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Mouse Move Check", &settings::AA_mouseMoveCheck);

	ImGui::SetCursorPosX(20.f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("AA_Sep3");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("FOV Circle", &settings::AA_fovCircle);

	if (settings::AA_fovCircle)
	{
		ImGui::SetCursorPosX(20.f);
		Menu::ColorEdit("FOV Circle Color", settings::AA_fovCircleColor);
	}

	ImGui::SetCursorPosX(20.f);
	Menu::Checkbox("Feedback Line", &settings::AA_aimAssistFeedback);

	if (settings::AA_aimAssistFeedback)
	{
		ImGui::SetCursorPosX(20.f);
		Menu::ColorEdit("Feedback Line Color", settings::AA_aimAssistFeedbackColor);
	}

	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("aa_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(1, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::AA_Enabled);
	//	ImGui::EndGroup();
	//	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	//	{
	//		renderSettings = !renderSettings;
	//	}

	//	ImGui::PopStyleColor();
	//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.0));

	//	if (renderSettings)
	//	{
	//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//		ImGui::Separator();
	//		if (ImGui::BeginChild("aa_settings", ImVec2(425, 215), false))
	//		{
	//			Menu::KeybindButton(165, "Keybind", ImVec2(297, 0), settings::AA_Key);
	//			Menu::Slider(1, "FOV", ImVec2(225, 0), &settings::AA_fov, 5.0f, 180.0f);
	//			Menu::Slider(2, "Lock Distance", ImVec2(225, 0), &settings::AA_aimDistance, 1.0f, 8.0f);
	//			Menu::Slider(3, "Smoothness", ImVec2(225, 0), &settings::AA_smooth, 1.0f, 90.0f);

	//			Menu::ComboBox(6, "Target Priority", ImVec2(270, 0), &settings::AA_targetPriority, settings::AA_targetPriorityList, 3);

	//			ImGui::Separator();

	//			Menu::ToggleButton(4, "Visibility Check", ImVec2(368, 0), &settings::AA_visibilityCheck);
	//			Menu::ToggleButton(5, "Sprint Check", ImVec2(368, 0), &settings::AA_sprintCheck);
	//			Menu::ToggleButton(127, "Invisible Check", ImVec2(368, 0), &settings::AA_invisibleCheck);
	//			Menu::ToggleButton(128, "Block Break Check", ImVec2(368, 0), &settings::AA_blockBreakCheck);
	//			Menu::ToggleButton(129, "Weapon Only", ImVec2(368, 0), &settings::AA_weaponOnly);
	//			Menu::ToggleButton(130, "Mouse Move Check", ImVec2(368, 0), &settings::AA_mouseMoveCheck);
	//			Menu::ToggleButton(131, "Mouse Press Check", ImVec2(368, 0), &settings::AA_mousePressCheck);

	//			ImGui::Separator();

	//			Menu::ToggleButton(7, "Adapt to strafing", ImVec2(368, 0), &settings::AA_adaptive);
	//			Menu::Slider(8, "Adaptive strafing offset", ImVec2(225, 0), &settings::AA_adaptiveOffset, 0.1f, 15.f);
	//			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

	//			ImGui::Separator();

	//			Menu::Slider(9, "Yaw Randomness", ImVec2(225, 0), &settings::AA_randomYaw, 0.0f, 10.0f);
	//			Menu::Slider(10, "Pitch Randomness", ImVec2(225, 0), &settings::AA_randomPitch, 0.0f, 1);
	//			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

	//			ImGui::Separator();

	//			Menu::ToggleButton(11, "FOV Circle", ImVec2(368, 0), &settings::AA_fovCircle);
	//			if (settings::AA_fovCircle)
	//			{
	//				Menu::ColorPicker(12, "FOV Circle Color", ImVec2(374, 0), settings::AA_fovCircleColor);
	//			}

	//			Menu::ToggleButton(13, "Feedback Line", ImVec2(368, 0), &settings::AA_aimAssistFeedback);
	//			if (settings::AA_aimAssistFeedback)
	//			{
	//				Menu::ColorPicker(14, "Feedback Line Color", ImVec2(374, 0), settings::AA_aimAssistFeedbackColor);
	//			}

	//			Menu::ToggleButton(15, "Ignore Friends", ImVec2(368, 0), &settings::AA_ignoreFriends);
	//		}
	//		ImGui::EndChild();
	//		ImGui::Spacing();
	//	}
	//}
	//ImGui::EndChild();

	//ImGui::PopStyleVar();
	//ImGui::PopStyleColor();

	//ImGui::EndGroup();
}
