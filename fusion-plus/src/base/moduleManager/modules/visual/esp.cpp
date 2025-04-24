#include "esp.h"

#include <gl/GL.h>

#include "moduleManager/commonData.h"
#include "sdk/sdk.h"
#include "util/logger/logger.h"
#include "util/math/math.h"
#include "util/math/worldToScreen.h"
#include "util/render/renderqolf.h"
#include "menu/menu.h"
#include "configManager/configManager.h"

void Esp::Update()
{
	if (!settings::ESP_Enabled) return;
	if (!CommonData::SanityCheck()) return;

	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	Vector3 renderPos = CommonData::renderPos;
	Vector3 pos = CommonData::playerPos;

	if (CommonData::thirdPersonView != 0)
	{
		Vector3 cameraPos = CWorldToScreen::GetCameraPosition(CommonData::modelView);
		Vector2 angles = CommonData::playerAngles;
		float eyeHeight = SDK::minecraft->thePlayer->IsSneaking() ? 1.54f : 1.62f;

		Vector3 relativeEyePosToPlayer = { 0, eyeHeight, 0 };
		cameraPos = cameraPos - relativeEyePosToPlayer;

		float distance = sqrt(cameraPos.x * cameraPos.x + cameraPos.y * cameraPos.y + cameraPos.z * cameraPos.z) * 2;

		if (CommonData::thirdPersonView == 2) {
			distance = -distance;
		}

		// This whole calculation came from gaspers source from their reach module, which you can find in this cheat as well
		float cos = std::cos(Math::DegToRadiants(angles.x + 90.0f));
		float sin = std::sin(Math::DegToRadiants(angles.x + 90.0f));
		float cosPitch = std::cos(Math::DegToRadiants(angles.y));
		float sinPitch = std::sin(Math::DegToRadiants(angles.y));

		float x = renderPos.x - (cos * distance * cosPitch);
		float y = renderPos.y + (distance * sinPitch);
		float z = renderPos.z - (sin * distance * cosPitch);

		renderPos = Vector3{ x,y,z };
	}

	std::vector<Data> newData;
	
	float renderPartialTicks = CommonData::renderPartialTicks;
	for (CommonData::PlayerData entity : playerList)
	{
		Vector3 entityPos = entity.pos;
		Vector3 entityLastPos = entity.lastPos;

		float entityWidth = settings::ESP_BoxType == 0 ? 0.7f : (float)(entity.width / 2);
		float entityHeight = (float)(entity.height / 2);
		entityHeight += settings::ESP_BoxType == 0 ? 0.2f : 0;

		Vector3 diff = pos - entityPos;
		float dist = sqrt(pow(diff.x, 2.f) + pow(diff.y, 2.f) + pow(diff.z, 2.f)); // Sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2)
		// Regular distance check.
		if (dist > 300) {
			continue;
		}

		// You can't put one vector3 for fixing the jittering and use that to subtract all of them with it
		// it will mess screw up for some weird reason. Try it for yourself if you wish!
		//Vector3 fixedEntityPos{ entityLastPos + (entityLastPos - entityPos) * renderPartialTicks };
		
		// This stops the jittering, the calculations must be inverted for some reason from the original
		Vector3 origin { renderPos - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks}; // At the feet

		// Same with the offset of the point, it must be offset from the render position, not the entity position for some weird reason.
		Vector3 top{ (renderPos - Vector3{0, entityHeight * 2, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // Over the head
		Vector3 left{ (renderPos - Vector3{entityWidth, entityHeight, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the left
		Vector3 right{ (renderPos - Vector3{-entityWidth, entityHeight, 0}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the right
		Vector3 back{ (renderPos - Vector3{0, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the back
		Vector3 front{ (renderPos - Vector3{0, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // And in the middle to the front

		entityWidth /= settings::ESP_BoxType == 0 ? 1.388888f : 1.f;
		Vector3 left2{ (renderPos - Vector3{entityWidth, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the left
		Vector3 right2{ (renderPos - Vector3{-entityWidth, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the right
		Vector3 back2{ (renderPos - Vector3{-entityWidth, entityHeight, entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // In the middle to the back
		Vector3 front2{ (renderPos - Vector3{entityWidth, entityHeight, -entityWidth}) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // And in the middle to the front

		// ^ This shapes a diamond like formation which results in 6 world to screens instead of 8.
		// However if a 3d ESP is desired, 8 world to screens would be required.

		// Another note for this data, is we cannot use the bounding box values because it can be changed by the reach module, so its best we make our own values with the cost
		// of consuming a little bit of resources for a bit of math.
		std::vector<Vector3> boxVerticies{
			origin, top, left, right, back, front, left2, right2, back2, front2
		};

		Vector3 maxBB = Vector3{ (float)entity.boundingBox.maxX, (float)entity.boundingBox.maxY, (float)entity.boundingBox.maxZ };
		Vector3 minBB = Vector3{ (float)entity.boundingBox.minX, (float)entity.boundingBox.minY, (float)entity.boundingBox.minZ };
		Vector3 max = { (renderPos - (maxBB - entityPos)) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks };
		Vector3 min = { (renderPos - (minBB - entityPos)) - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks };
		max.y -= 0.15f;
		min.y -= 0.15f;
		std::vector<Vector3> boundingBoxVerticies{
			Vector3{max.x, max.y, max.z},
			Vector3{max.x, min.y, max.z},
			Vector3{min.x, min.y, max.z},
			Vector3{min.x, max.y, max.z},
			Vector3{max.x, max.y, min.z},
			Vector3{max.x, min.y, min.z},
			Vector3{min.x, min.y, min.z},
			Vector3{min.x, max.y, min.z}
		};

		// For when the player gets close to an entity, a fade factor; a value between 0 and 1, with basic math, can get a cool looking fade effect if the player is too close
		// or inside the FadeDistance radius.
		float fadeFactor = 1.0f;
		if ((dist - 1) <= settings::ESP_FadeDistance)
			fadeFactor = ((dist - 1) / settings::ESP_FadeDistance);

		// To render the distance value under the ESP box.
		char distC[32];
		std::snprintf(distC, sizeof(distC), "%.1f", dist);
		std::string distS(distC);

		// Then finally taking all the data we acquired for this loop and pushing it to the data list.
		newData.push_back(Data{
			boxVerticies, // Box data
			entity.name, // Entity name
			distS + "m", // Distance
			dist, // Real distance value (for fade)
			fadeFactor, // Fade factor
			entity.health, // Entity health
			entity.maxHealth, // And max health (for health bar)
			boundingBoxVerticies,
		});
	}
	m_renderData = newData;
}

void Esp::RenderOverlay()
{
	if (!settings::ESP_Enabled || !CommonData::dataUpdated) return;

	for (Data data : m_renderData)
	{
		ImVec2 screenSize = ImGui::GetWindowSize();
		bool skip = false;
		
		float left = FLT_MAX;
		float top = FLT_MAX;
		float right = FLT_MIN;
		float bottom = FLT_MIN;
		if (settings::ESP_BoxType == 0/* || settings::ESP_HealthBar || (settings::ESP_Text && Menu::Font->IsLoaded())*/)
		{
			std::vector<Vector3> bv = data.boxVerticies;

			for (Vector3 position : bv)
			{
				Vector2 p;

				if (!CWorldToScreen::WorldToScreen(position, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, p))
				{
					skip = true;
					break;
				}

				//ImGui::GetWindowDrawList()->AddCircle(ImVec2(p.x, p.y), 3, ImColor(255, 0, 0), 100, 2);

				// This is a neat trick to get the top left and bottom right corners of all the box verticies quickly.
				left = fmin(p.x, left);
				top = fmin(p.y, top);
				right = fmax(p.x, right);
				bottom = fmax(p.y, bottom);
			}
		}

		std::vector<Vector2> boxCorners;
		if (settings::ESP_BoxType == 1)
		{
			std::vector<Vector3> bb = data.boundingBoxVerticies;

			for (Vector3 position : bb)
			{
				Vector2 p;

				if (!CWorldToScreen::WorldToScreen(position, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, p))
				{
					skip = true;
					break;
				}

				boxCorners.push_back(p);

				// This is a neat trick to get the top left and bottom right corners of all the box verticies quickly.
				left = fmin(p.x, left);
				top = fmin(p.y, top);
				right = fmax(p.x, right);
				bottom = fmax(p.y, bottom);
			}
		}

		// This is for when the world to screen fails, we just want to ignore rendering the entire box completely.
		// The fade stuff will compensate for it randomly disappearing when you're too close.
		if (skip)
			continue;

		bool IsFriend = configmanager::IsFriend(data.name) && settings::ESP_HighlightFriends;

		// The rest is just rendering the ESP with the customizable options, self explanitory.

		if (settings::ESP_BoxType == 0)
		{
			if (settings::ESP_FilledBox)
			{
				ImColor bottomColor = ImColor(settings::ESP_SecondFilledBoxColor[0], settings::ESP_SecondFilledBoxColor[1], settings::ESP_SecondFilledBoxColor[2], settings::ESP_SecondFilledBoxColor[3] * data.opacityFadeFactor);
				ImColor bottomColorFriend = ImColor(settings::ESP_FriendSecondFilledBoxColor[0], settings::ESP_FriendSecondFilledBoxColor[1], settings::ESP_FriendSecondFilledBoxColor[2], settings::ESP_FriendSecondFilledBoxColor[3] * data.opacityFadeFactor);
				ImColor topColor = ImColor(settings::ESP_FilledBoxColor[0], settings::ESP_FilledBoxColor[1], settings::ESP_FilledBoxColor[2], settings::ESP_FilledBoxColor[3] * data.opacityFadeFactor);
				ImColor topColorFriend = ImColor(settings::ESP_FriendFilledBoxColor[0], settings::ESP_FriendFilledBoxColor[1], settings::ESP_FriendFilledBoxColor[2], settings::ESP_FriendFilledBoxColor[3] * data.opacityFadeFactor);

				ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(left, top), ImVec2(right, bottom), IsFriend ? topColorFriend : topColor, IsFriend ? topColorFriend : topColor, IsFriend ? bottomColorFriend : bottomColor, IsFriend ? bottomColorFriend : bottomColor);
			}

			if (settings::ESP_Box)
			{
				ImColor color = ImColor(settings::ESP_BoxColor[0], settings::ESP_BoxColor[1], settings::ESP_BoxColor[2], settings::ESP_BoxColor[3] * data.opacityFadeFactor);
				ImColor colorFriend = ImColor(settings::ESP_FriendBoxColor[0], settings::ESP_FriendBoxColor[1], settings::ESP_FriendBoxColor[2], settings::ESP_FriendBoxColor[3] * data.opacityFadeFactor);

				ImGui::GetWindowDrawList()->AddRect(ImVec2(left, top), ImVec2(right, bottom), IsFriend ? colorFriend : color);
			}

			if (settings::ESP_Outline)
			{
				ImColor color = ImColor(settings::ESP_OutlineColor[0], settings::ESP_OutlineColor[1], settings::ESP_OutlineColor[2], settings::ESP_OutlineColor[3] * data.opacityFadeFactor);
				ImColor colorFriend = ImColor(settings::ESP_FriendOutlineColor[0], settings::ESP_FriendOutlineColor[1], settings::ESP_FriendOutlineColor[2], settings::ESP_FriendOutlineColor[3] * data.opacityFadeFactor);

				ImGui::GetWindowDrawList()->AddRect(ImVec2(left - 1, top - 1), ImVec2(right + 1, bottom + 1), IsFriend ? colorFriend : color);
				ImGui::GetWindowDrawList()->AddRect(ImVec2(left + 1, top + 1), ImVec2(right - 1, bottom - 1), IsFriend ? colorFriend : color);
			}
		}

		if (settings::ESP_BoxType == 1 && boxCorners.size() == 8)
		{
			if (settings::ESP_Outline)
			{
				ImColor colorOutline = ImColor(settings::ESP_OutlineColor[0], settings::ESP_OutlineColor[1], settings::ESP_OutlineColor[2], settings::ESP_OutlineColor[3] * data.opacityFadeFactor);
				ImColor colorOutlineFriend = ImColor(settings::ESP_FriendOutlineColor[0], settings::ESP_FriendOutlineColor[1], settings::ESP_FriendOutlineColor[2], settings::ESP_FriendOutlineColor[3] * data.opacityFadeFactor);

				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[0].x, boxCorners[0].y), ImVec2(boxCorners[1].x, boxCorners[1].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[1].x, boxCorners[1].y), ImVec2(boxCorners[2].x, boxCorners[2].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[2].x, boxCorners[2].y), ImVec2(boxCorners[3].x, boxCorners[3].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[3].x, boxCorners[3].y), ImVec2(boxCorners[0].x, boxCorners[0].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);

				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[4].x, boxCorners[4].y), ImVec2(boxCorners[5].x, boxCorners[5].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[5].x, boxCorners[5].y), ImVec2(boxCorners[6].x, boxCorners[6].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[6].x, boxCorners[6].y), ImVec2(boxCorners[7].x, boxCorners[7].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[7].x, boxCorners[7].y), ImVec2(boxCorners[4].x, boxCorners[4].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);

				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[0].x, boxCorners[0].y), ImVec2(boxCorners[4].x, boxCorners[4].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[1].x, boxCorners[1].y), ImVec2(boxCorners[5].x, boxCorners[5].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[2].x, boxCorners[2].y), ImVec2(boxCorners[6].x, boxCorners[6].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
				ImGui::GetWindowDrawList()->AddLine(ImVec2(boxCorners[3].x, boxCorners[3].y), ImVec2(boxCorners[7].x, boxCorners[7].y), IsFriend ? colorOutlineFriend : colorOutline, settings::ESP_3DBoxThickness);
			}

			if (settings::ESP_FilledBox)
			{
				ImColor colorFilledBox = ImColor(settings::ESP_FilledBoxColor[0], settings::ESP_FilledBoxColor[1], settings::ESP_FilledBoxColor[2], settings::ESP_FilledBoxColor[3] * data.opacityFadeFactor);
				ImColor colorFilledBoxFriend = ImColor(settings::ESP_FriendFilledBoxColor[0], settings::ESP_FriendFilledBoxColor[1], settings::ESP_FriendFilledBoxColor[2], settings::ESP_FriendFilledBoxColor[3] * data.opacityFadeFactor);

				ImVec2 faceTop[] = { ImVec2(boxCorners[0].x, boxCorners[0].y), ImVec2(boxCorners[1].x, boxCorners[1].y), ImVec2(boxCorners[2].x, boxCorners[2].y), ImVec2(boxCorners[3].x, boxCorners[3].y) };
				ImVec2 faceBottom[] = { ImVec2(boxCorners[4].x, boxCorners[4].y), ImVec2(boxCorners[5].x, boxCorners[5].y), ImVec2(boxCorners[6].x, boxCorners[6].y), ImVec2(boxCorners[7].x, boxCorners[7].y) };
				ImVec2 faceLeft[] = { ImVec2(boxCorners[0].x, boxCorners[0].y), ImVec2(boxCorners[4].x, boxCorners[4].y), ImVec2(boxCorners[7].x, boxCorners[7].y), ImVec2(boxCorners[3].x, boxCorners[3].y) };
				ImVec2 faceRight[] = { ImVec2(boxCorners[1].x, boxCorners[1].y), ImVec2(boxCorners[5].x, boxCorners[5].y), ImVec2(boxCorners[6].x, boxCorners[6].y), ImVec2(boxCorners[2].x, boxCorners[2].y) };
				ImVec2 faceFront[] = { ImVec2(boxCorners[0].x, boxCorners[0].y), ImVec2(boxCorners[1].x, boxCorners[1].y), ImVec2(boxCorners[5].x, boxCorners[5].y), ImVec2(boxCorners[4].x, boxCorners[4].y) };
				ImVec2 faceBack[] = { ImVec2(boxCorners[2].x, boxCorners[2].y), ImVec2(boxCorners[3].x, boxCorners[3].y), ImVec2(boxCorners[7].x, boxCorners[7].y), ImVec2(boxCorners[6].x, boxCorners[6].y) };

				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceTop, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceBottom, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceLeft, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceRight, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceFront, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
				ImGui::GetWindowDrawList()->AddConvexPolyFilled(faceBack, 4, IsFriend ? colorFilledBoxFriend : colorFilledBox);
			}
		}

		if (settings::ESP_HealthBar)
		{
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(left - 3, top), ImVec2(left - 1, bottom), ImColor(settings::ESP_FilledBoxColor[0], settings::ESP_FilledBoxColor[1], settings::ESP_FilledBoxColor[2], settings::ESP_FilledBoxColor[3] * data.opacityFadeFactor));

			if (data.health <= 0)
				data.health = 0.00001f;

			float scaleFactor = data.health / data.maxHealth;
			float diff = bottom - top;

			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(left - 3, bottom - (diff * scaleFactor)), ImVec2(left - 1, bottom), ImColor((int)(255 * (1.0 - scaleFactor)), (int)(255 * scaleFactor), 0, (int)(255 * data.opacityFadeFactor)));
		}
	}
}

void Esp::RenderMenu()
{
	Menu::ToggleWithKeybind(&settings::ESP_Enabled, settings::ESP_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Fade Distance", &settings::ESP_FadeDistance, 0.0f, 10.0f);
	Menu::Checkbox("Show Healthbar", &settings::ESP_HealthBar);
	Menu::Checkbox("Highlight Friends", &settings::ESP_HighlightFriends);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep2");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Checkbox("Filled Box", &settings::ESP_FilledBox);
	if (settings::ESP_FilledBox)
	{
		Menu::ColorEdit("Filled Box Color", settings::ESP_FilledBoxColor);
		if (settings::ESP_BoxType == 0)
			Menu::ColorEdit("Second Filled Box Color", settings::ESP_SecondFilledBoxColor);
		if (settings::ESP_HighlightFriends)
		{
			Menu::ColorEdit("Friend Filled Box Color", settings::ESP_FriendFilledBoxColor);
			if (settings::ESP_BoxType == 0)
				Menu::ColorEdit("Friend Second Filled Box Color", settings::ESP_FriendSecondFilledBoxColor);
		}
	}
	Menu::Checkbox("Outline", &settings::ESP_Outline);
	if (settings::ESP_Outline)
	{
		Menu::ColorEdit("Outline Color", settings::ESP_OutlineColor);
		if (settings::ESP_HighlightFriends)
		{
			Menu::ColorEdit("Friend Outline Color", settings::ESP_FriendOutlineColor);
		}
	}
	Menu::Dropdown("Box Type", settings::ESP_BoxTypeList, &settings::ESP_BoxType, 2);
	if (settings::ESP_BoxType == 0)
	{
		Menu::Checkbox("Box", &settings::ESP_Box);
		if (settings::ESP_Box)
		{
			Menu::ColorEdit("Box Color", settings::ESP_BoxColor);
			if (settings::ESP_HighlightFriends)
			{
				Menu::ColorEdit("Friend Box Color", settings::ESP_FriendBoxColor);
			}
		}
	}
	else if (settings::ESP_BoxType == 1)
	{
		Menu::Slider("Box Thickness", &settings::ESP_3DBoxThickness, 0.5f, 5.0f);
	}
}
