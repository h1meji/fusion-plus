#include "aimAssist.h"

#include "moduleManager/commonData.h"
#include "util/logger/logger.h"
#include "util/math/worldToScreen.h"
#include "util/math/math.h"
#include "util/minecraft/minecraft.h"
#include "util/keys.h"
#include "menu/menu.h"
#include "sdk/sdk.h"
#include "java/java.h"
#include "configManager/configManager.h"

static bool isMouseMoving()
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
	if (Menu::open) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::minecraft->IsInGuiState()) return;

	// Checks
	if (settings::AA_sprintCheck && !SDK::minecraft->thePlayer->IsSprinting())
	{
		AimAssist::m_data = Vector3();
		return;
	}
	if (settings::AA_blockBreakCheck && SDK::minecraft->GetMouseOver().IsTypeOfBlock())
	{
		AimAssist::m_data = Vector3();
		return;
	}
	if (settings::AA_weaponOnly && !MinecraftUtils::IsWeapon(SDK::minecraft->thePlayer->GetInventory().GetCurrentItem()))
	{
		AimAssist::m_data = Vector3();
		return;
	}

	if (settings::AA_mousePressCheck && Keys::IsKeyReleased(VK_LBUTTON))
	{
		AimAssist::m_data = Vector3();
		return;
	}

	if (!isMouseMoving() && settings::AA_mouseMoveCheck) {
		AimAssist::m_data = Vector3();
		return;
	}

	Vector3 pos = CommonData::playerPos;
	Vector3 headPos = CommonData::playerEyePos;
	Vector2 currentLookAngles = CommonData::playerAngles;

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
		if (!Java::env->IsSameObject(SDK::minecraft->thePlayer->GetInstance(), player.obj.GetInstance()) && !(settings::AA_ignoreFriends && configmanager::IsFriend(player.name))) {
			if (!SDK::minecraft->thePlayer->CanEntityBeSeen(player.obj.GetInstance()) && settings::AA_visibilityCheck) continue;
			if (player.obj.IsInvisibleToPlayer(SDK::minecraft->thePlayer->GetInstance()) && settings::AA_invisibleCheck) continue;

			Vector3 playerPos = player.pos;
			float playerHeight = target.height - 0.1f;
			Vector3 playerHeadPos = playerPos + Vector3(0, playerHeight, 0);

			Vector2 anglesFoot = Math::GetAngles(headPos, playerPos);
			Vector2 anglesHead = Math::GetAngles(headPos, playerHeadPos);

			Vector2 difference = Math::WrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::WrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());
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

	if (!target.obj.GetInstance())
	{
		m_data = Vector3();
		return;
	}


	Vector3 ePos = target.pos;
	Vector3 eLastPos = target.lastPos;

	float eHeight = target.height - 0.1f;
	Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
	Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


	Vector2 anglesFoot = Math::GetAngles(headPos, ePos);
	Vector2 anglesHead = Math::GetAngles(headPos, eHeadPos);

	Vector2 difference = Math::WrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
	Vector2 differenceFoot = Math::WrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

	float offset = randomFloat(-settings::AA_randomYaw, settings::AA_randomYaw);
	if (settings::AA_adaptive)
	{
		if ((GetAsyncKeyState('D') & 0x8000) && !(GetAsyncKeyState('A') & 0x8000))
		{
			offset -= settings::AA_adaptiveOffset;
		}

		if ((GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000))
		{
			offset += settings::AA_adaptiveOffset;
		}
	}

	float targetYaw = currentLookAngles.x + ((difference.x + offset) / settings::AA_smooth);

	Vector3 renderPos = CommonData::renderPos;
	float renderPartialTicks = CommonData::renderPartialTicks;

	if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y)
	{
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
			m_data = renderPos - Vector3(0.f, 0.21f, 0.f) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
		}
		else 
		{
			targetPitch = targetPitchFoot;
			m_data = renderPos - Vector3(0.f, 0.23f, 0.f) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		}
		m_pitchInfluenced = true;
		targetPitch += randomFloat(-settings::AA_randomPitch, settings::AA_randomPitch);
		SDK::minecraft->thePlayer->SetAngles(Vector2(targetYaw, targetPitch));
	}
	else
	{
		m_data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		m_pitchInfluenced = false;
		SDK::minecraft->thePlayer->SetAngles(Vector2(targetYaw, currentLookAngles.y + randomFloat(-settings::AA_randomPitch, settings::AA_randomPitch)));
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
		if (m_data.x == NAN) return;
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 w2s;
		if (CWorldToScreen::WorldToScreen(m_data, CommonData::modelView, CommonData::projection, screenSize.x, screenSize.y, w2s))
		{
			if (w2s.x == NAN) return;

			if (m_pitchInfluenced)
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
	Menu::ToggleWithKeybind(&settings::AA_Enabled, settings::AA_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Smoothness", &settings::AA_smooth, 1.0f, 90.0f);
	Menu::Slider("FOV", &settings::AA_fov, 5.0f, 180.f);
	Menu::Slider("Lock Distance", &settings::AA_aimDistance, 1.0f, 10.0f);
	Menu::Dropdown("Target Priority", settings::AA_targetPriorityList, &settings::AA_targetPriority, 3);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep2");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Yaw Randomness", &settings::AA_randomYaw, 0.0f, 10.0f);
	Menu::Slider("Pitch Randomness", &settings::AA_randomPitch, 0.0f, 1.0f);
	Menu::Checkbox("Adapt to strafing", &settings::AA_adaptive);
	if (settings::AA_adaptive)
	{
		Menu::Slider("Adaptive Strafing Offset", &settings::AA_adaptiveOffset, 0.0f, 15.f);
	}

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep3");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Checkbox("Weapon Only", &settings::AA_weaponOnly);
	Menu::Checkbox("Ignore Friends", &settings::AA_ignoreFriends);
	Menu::Checkbox("Visiblity Check", &settings::AA_visibilityCheck);
	Menu::Checkbox("Ignore Invisible", &settings::AA_invisibleCheck);
	Menu::Checkbox("Allow Block Breaking", &settings::AA_blockBreakCheck);
	Menu::Checkbox("Sprinting Only", &settings::AA_sprintCheck);
	Menu::Checkbox("Mouse Press Check", &settings::AA_mousePressCheck);
	Menu::Checkbox("Mouse Move Check", &settings::AA_mouseMoveCheck);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep3");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Checkbox("FOV Circle", &settings::AA_fovCircle);
	if (settings::AA_fovCircle)
	{
		Menu::ColorEdit("FOV Circle Color", settings::AA_fovCircleColor);
	}
	Menu::Checkbox("Feedback Line", &settings::AA_aimAssistFeedback);
	if (settings::AA_aimAssistFeedback)
	{
		Menu::ColorEdit("Feedback Line Color", settings::AA_aimAssistFeedbackColor);
	}
}
