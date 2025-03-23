#include "nametag.h"
#include <moduleManager/commonData.h>
#include <util/math/math.h>
#include <util/math/worldToScreen.h>
#include <imgui/imgui.h>
#include <configManager/configManager.h>
#include <menu/menu.h>
#include <util/render/renderqolf.h>

static std::string floatToString(float value, int precision) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(precision) << value;
	return out.str();
}

void Nametag::Update()
{
	if (!settings::NT_Enabled) return;
	if (!CommonData::SanityCheck()) return;

	CEntityPlayerSP* player = SDK::Minecraft->thePlayer;
	CWorld* world = SDK::Minecraft->theWorld;
	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	Vector3 renderPos = CommonData::renderPos;
	Vector3 pos = player->GetPos();

	if (CommonData::thirdPersonView != 0) {
		Vector3 cameraPos = CWorldToScreen::GetCameraPosition(CommonData::modelView);
		Vector2 angles = player->GetAngles();
		float eyeHeight = player->IsSneaking() ? 1.54f : 1.62f;

		Vector3 relativeEyePosToPlayer = { 0, eyeHeight, 0 };
		cameraPos = cameraPos - relativeEyePosToPlayer;

		float distance = sqrt(cameraPos.x * cameraPos.x + cameraPos.y * cameraPos.y + cameraPos.z * cameraPos.z) * 2;

		if (CommonData::thirdPersonView == 2) {
			distance = -distance;
		}

		float cos = std::cos(Math::degToRadiants(angles.x + 90.0f));
		float sin = std::sin(Math::degToRadiants(angles.x + 90.0f));
		float cosPitch = std::cos(Math::degToRadiants(angles.y));
		float sinPitch = std::sin(Math::degToRadiants(angles.y));

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

		float entityWidth = 0.7f;
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
		Vector3 origin{ renderPos - entityLastPos + (entityLastPos - entityPos) * renderPartialTicks }; // At the feet

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

		float fadeFactor = 1.0f;
		if ((dist - 1) <= settings::NT_FadeDistance)
			fadeFactor = ((dist - 1) / settings::NT_FadeDistance);

		char distC[32];
		std::snprintf(distC, sizeof(distC), "%.1f", dist);
		std::string distS(distC);

		std::string health = floatToString(entity.health, 1) + "/" + floatToString(entity.maxHealth, 1) + "hp";
		std::string invisble = entity.obj.IsInvisibleToPlayer(player->GetInstance()) ? "Invisible" : "";

		newData.push_back(Data{
			boxVerticies, // Box data
			boundingBoxVerticies,
			entity.name, // Entity name
			distS + "m", // Distance
			health, // Health
			invisble, // Invisible
			dist, // Real distance value (for fade)
			fadeFactor, // Fade factor
			});
	}
	nametagData = newData;
}

void Nametag::RenderOverlay()
{
	if (!settings::NT_Enabled || !CommonData::dataUpdated) return;

	for (Data data : nametagData)
	{
		if (data.dist < settings::NT_TextUnrenderDistance) continue;

		ImVec2 screenSize = ImGui::GetWindowSize();
		bool skip = false;

		float left = FLT_MAX;
		float top = FLT_MAX;
		float right = FLT_MIN;
		std::vector<Vector3> bv = data.boxVerticies;

		for (Vector3 position : bv)
		{
			Vector2 p;

			if (!CWorldToScreen::WorldToScreen(position, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, p))
			{
				skip = true;
				break;
			}

			left = fmin(p.x, left);
			top = fmin(p.y, top);
			right = fmax(p.x, right);
		}

		if (skip)
			continue;

		if (ConfigManager::IsFriend(data.name) && settings::NT_IgnoreFriends)
			continue;

		if (settings::NT_MultiLine)
		{
			std::vector<std::string> texts;
			if (!data.name.empty()) texts.push_back(data.name);
			if (settings::NT_DisplayHealth && !data.healthText.empty()) texts.push_back(data.healthText);
			if (settings::NT_DisplayDistance && !data.distText.empty()) texts.push_back(data.distText);
			if (settings::NT_DisplayInvisible && !data.invisbleText.empty()) texts.push_back(data.invisbleText);

			// Render Background with one big box
			if (settings::NT_Background)
			{
				std::string finalText = "";
				for (std::string text : texts)
				{
					finalText += text + "\n";
				}

				ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::NT_TextSize, FLT_MAX, 0.0f, finalText.c_str());
				float posX = left + ((right - left) / 2) - (textSize.x / 2);
				float posY = top - textSize.y - 1;

				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posX - 5, posY - 5), ImVec2(posX + textSize.x + 5, posY + textSize.y + 5), ImColor(settings::NT_BackgroundColor[0], settings::NT_BackgroundColor[1], settings::NT_BackgroundColor[2], settings::NT_BackgroundColor[3] * data.opacityFadeFactor));

				if (settings::NT_BackgroundOutline)
				{
					ImGui::GetWindowDrawList()->AddRect(ImVec2(posX - 5, posY - 5), ImVec2(posX + textSize.x + 5, posY + textSize.y + 5), ImColor(settings::NT_BackgroundOutlineColor[0], settings::NT_BackgroundOutlineColor[1], settings::NT_BackgroundOutlineColor[2], settings::NT_BackgroundOutlineColor[3] * data.opacityFadeFactor));
				}
			}

			float totalHeight = 0.0f;
			std::vector<ImVec2> textSizes;

			for (const std::string& text : texts)
			{
				ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::NT_TextSize, FLT_MAX, 0.0f, text.c_str());
				textSizes.push_back(textSize);
				totalHeight += textSize.y;
			}

			float startY = top - totalHeight - 1;

			for (size_t i = 0; i < texts.size(); ++i)
			{
				ImVec2 textSize = textSizes[i];
				float posX = left + ((right - left) / 2) - (textSize.x / 2);
				float posY = startY;
				startY += textSize.y;

				if (settings::NT_TextOutline)
				{
					RenderQOLF::DrawOutlinedText(Menu::Font, settings::NT_TextSize, ImVec2(posX, posY), ImColor(settings::NT_TextColor[0], settings::NT_TextColor[1], settings::NT_TextColor[2], settings::NT_TextColor[3] * data.opacityFadeFactor), ImColor(settings::NT_TextOutlineColor[0], settings::NT_TextOutlineColor[1], settings::NT_TextOutlineColor[2], settings::NT_TextOutlineColor[3] * data.opacityFadeFactor), texts[i].c_str());
				}
				else
				{
					ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::NT_TextSize, ImVec2(posX, posY), ImColor(settings::NT_TextColor[0], settings::NT_TextColor[1], settings::NT_TextColor[2], settings::NT_TextColor[3] * data.opacityFadeFactor), texts[i].c_str());
				}
			}
		}
		else
		{
			std::string finalText = data.name;
			if (settings::NT_DisplayHealth && !data.healthText.empty()) finalText += " | " + data.healthText;
			if (settings::NT_DisplayDistance && !data.distText.empty()) finalText += " | " + data.distText;
			if (settings::NT_DisplayInvisible && !data.invisbleText.empty()) finalText += " | " + data.invisbleText;

			ImVec2 textSize = Menu::Font->CalcTextSizeA(settings::NT_TextSize, FLT_MAX, 0.0f, finalText.c_str());
			if (settings::NT_Background)
			{
				float posX = left + ((right - left) / 2) - (textSize.x / 2);
				float posY = top - textSize.y - 1;

				ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(posX - 5, posY - 5), ImVec2(posX + textSize.x + 5, posY + textSize.y + 5), ImColor(settings::NT_BackgroundColor[0], settings::NT_BackgroundColor[1], settings::NT_BackgroundColor[2], settings::NT_BackgroundColor[3] * data.opacityFadeFactor));

				if (settings::NT_BackgroundOutline)
				{
					ImGui::GetWindowDrawList()->AddRect(ImVec2(posX - 5, posY - 5), ImVec2(posX + textSize.x + 5, posY + textSize.y + 5), ImColor(settings::NT_BackgroundOutlineColor[0], settings::NT_BackgroundOutlineColor[1], settings::NT_BackgroundOutlineColor[2], settings::NT_BackgroundOutlineColor[3] * data.opacityFadeFactor));
				}
			}

			float posX = left + ((right - left) / 2) - (textSize.x / 2);
			float posY = top - textSize.y - 1;
			if (settings::NT_TextOutline)
			{
				RenderQOLF::DrawOutlinedText(Menu::Font, settings::NT_TextSize, ImVec2(posX, posY), ImColor(settings::NT_TextColor[0], settings::NT_TextColor[1], settings::NT_TextColor[2], settings::NT_TextColor[3] * data.opacityFadeFactor), ImColor(settings::NT_TextOutlineColor[0], settings::NT_TextOutlineColor[1], settings::NT_TextOutlineColor[2], settings::NT_TextOutlineColor[3] * data.opacityFadeFactor), finalText.c_str());
			}
			else
			{
				ImGui::GetWindowDrawList()->AddText(Menu::Font, settings::NT_TextSize, ImVec2(posX, posY), ImColor(settings::NT_TextColor[0], settings::NT_TextColor[1], settings::NT_TextColor[2], settings::NT_TextColor[3] * data.opacityFadeFactor), finalText.c_str());
			}
		}
	}
}


void Nametag::RenderMenu()
{
	//static bool renderSettings = false;

	//ImGui::BeginGroup();
	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("nt_header", ImVec2(425.f, renderSettings ? 260.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(151, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::NT_Enabled);
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
	//		if (ImGui::BeginChild("nt_settings", ImVec2(425, 215), false))
	//		{
	//			Menu::KeybindButton(179, "Keybind", ImVec2(297, 0), settings::NT_Key);
	//			Menu::Slider(152, "Text Size", ImVec2(225, 0), &settings::NT_TextSize, 1.0f, 50.0f);
	//			Menu::ColorPicker(153, "Text Color", ImVec2(374, 0), settings::NT_TextColor);

	//			Menu::ToggleButton(154, "Text Outline", ImVec2(368, 0), &settings::NT_TextOutline);
	//			if (settings::NT_TextOutline)
	//			{
	//				Menu::ColorPicker(155, "Text Outline Color", ImVec2(374, 0), settings::NT_TextOutlineColor);
	//			}

	//			Menu::ToggleButton(158, "Background", ImVec2(368, 0), &settings::NT_Background);
	//			if (settings::NT_Background)
	//			{
	//				Menu::ColorPicker(159, "Background Color", ImVec2(374, 0), settings::NT_BackgroundColor);
	//			}

	//			Menu::ToggleButton(164, "Background Outline", ImVec2(368, 0), &settings::NT_BackgroundOutline);
	//			if (settings::NT_BackgroundOutline)
	//			{
	//				Menu::ColorPicker(165, "Background Outline Color", ImVec2(374, 0), settings::NT_BackgroundOutlineColor);
	//			}

	//			Menu::Slider(156, "Unrender Distance", ImVec2(225, 0), &settings::NT_TextUnrenderDistance, 0.0f, 300.0f);
	//			Menu::Slider(157, "Fade Distance", ImVec2(225, 0), &settings::NT_FadeDistance, 0.0f, 300.0f);

	//			Menu::ToggleButton(207, "Multi Line", ImVec2(368, 0), &settings::NT_MultiLine);
	//			Menu::ToggleButton(160, "Display Health", ImVec2(368, 0), &settings::NT_DisplayHealth);
	//			Menu::ToggleButton(161, "Display Distance", ImVec2(368, 0), &settings::NT_DisplayDistance);
	//			Menu::ToggleButton(162, "Display Invisible", ImVec2(368, 0), &settings::NT_DisplayInvisible);
	//			Menu::ToggleButton(163, "Ignore Friends", ImVec2(368, 0), &settings::NT_IgnoreFriends);
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
