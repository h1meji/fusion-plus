#include "aimAssist.h"
#include "moduleManager/commonData.h"
#include "sdk/sdk.h"
#include "util/logger.h"
#include "imgui/imgui.h"
#include "util/math/worldToScreen.h"
#include "util/math/math.h"
#include "menu/menu.h"
#include "java/java.h"

#include <chrono>
#include <random>

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
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	if (Menu::Open) return;

	if ((settings::AA_aimKey && (!GetAsyncKeyState(VK_LBUTTON) && 1))) {
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
		if (!Java::Env->IsSameObject(thePlayer->GetInstance(), player.obj.GetInstance())) {
			if (!thePlayer->CanEntityBeSeen(player.obj.GetInstance())) continue;
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

	float eHeight = target.height - 0.1;
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
			data = renderPos - Vector3(0, 0.21, 0) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
		}
		else 
		{
			targetPitch = targetPitchFoot;
			data = renderPos - Vector3(0, 0.23, 0) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
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

void AimAssist::RenderUpdate()
{
	if (!settings::AA_Enabled || !CommonData::dataUpdated) return;
	if (settings::AA_fovCircle) {

		ImVec2 screenSize = ImGui::GetWindowSize();
		float radAimbotFov = (float)(settings::AA_fov * PI / 180);
		float radViewFov = (float)(CommonData::fov * PI / 180);
		float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * screenSize.x / 1.7325;

		ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), circleRadius, ImColor(settings::AA_fovCircleColor[0], settings::AA_fovCircleColor[1], settings::AA_fovCircleColor[2], settings::AA_fovCircleColor[3]), circleRadius / 3, 1);
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
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("aimassist", ImVec2(425, renderSettings ? 260 : 35))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(234402345634000, "Toggle Aim Assist", &settings::AA_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();
			Menu::DoSliderStuff(23084562545, "FOV", &settings::AA_fov, 5.0f, 180.0f);
			Menu::DoSliderStuff(869765007, "Lock Distance", &settings::AA_aimDistance, 1.0f, 8.0f);
			Menu::DoSliderStuff(2314057445345, "Smoothness", &settings::AA_smooth, 1.0f, 90.0f);
			Menu::DoToggleButtonStuff(22645342, "Visbility Check", &settings::AA_visibilityCheck);
			Menu::DoToggleButtonStuff(206573465433442, "Left Button To Aim", &settings::AA_aimKey);

			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));
			ImGui::Text("Target Priority");
			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 170);

			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.55, 0.55, 1));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.65, 0.65, 1));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.8, 0.8, 1));

			ImGui::Combo("tp", &settings::AA_targetPriority, settings::AA_targetPriorityList, 3);

			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();

			ImGui::Separator();

			Menu::DoToggleButtonStuff(5635678756247, "Adapt to strafing", &settings::AA_adaptive);
			Menu::DoSliderStuff(457323434, "Adaptive strafing offset", &settings::AA_adaptiveOffset, 0.1f, 15.f);
			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

			ImGui::Separator();
			Menu::DoSliderStuff(3464340056, "Yaw Randomness", &settings::AA_randomYaw, 0.0f, 10.0f);
			Menu::DoSliderStuff(54034352347, "Pitch Randomness", &settings::AA_randomPitch, 0.0f, 1);
			ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

			ImGui::Separator();
			Menu::DoToggleButtonStuff(76523436400, "FOV Circle", &settings::AA_fovCircle);
			if (settings::AA_fovCircle)
			{
				Menu::DoColorPickerStuff(4356354, "FOV Circle Color", settings::AA_fovCircleColor);
			}

			Menu::DoToggleButtonStuff(230476545677654654, "Feedback Line", &settings::AA_aimAssistFeedback);
			if (settings::AA_aimAssistFeedback)
			{
				Menu::DoColorPickerStuff(2745325, "Feedback Line Color", settings::AA_aimAssistFeedbackColor);
			}

			ImGui::Spacing();
		}

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
