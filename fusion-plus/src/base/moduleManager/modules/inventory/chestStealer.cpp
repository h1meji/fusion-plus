#include "chestStealer.h"
#include <imgui/imgui.h>
#include <menu/menu.h>
#include <moduleManager/commonData.h>

#include "util/minecraft/minecraft.h"
#include "util/keys.h"

void ChestStealer::Update()
{
	if (!settings::CS_Enabled) { ResetSteal(); return; }
	if (!CommonData::SanityCheck()) { ResetSteal(); return; }

	if (!SDK::Minecraft->IsInChest()) { ResetSteal(); return; }

	if (!isStealing)
	{
		IInventory* inventory = SDK::Minecraft->GetGuiChest()->GetLowerChestInventory();

		chestSlots.clear();
		for (int i = 0; i < inventory->GetSizeInventory(); i++)
		{
			CItemStack* item = inventory->GetStackInSlot(i);
			if (item->GetInstance() == nullptr) continue;

			for (std::pair<int, int> id : settings::CS_Items)
			{
				if (item->GetItem().GetID() != id.first || (item->GetMetadata() != id.second && id.second != -1)) continue;
				chestSlots.push_back(i);
				break;
			}
		}

		isStealing = true;
		chestSlotIndex = 0;
		lastStealTime = std::chrono::steady_clock::now();
		activated = std::chrono::steady_clock::now();
	}

	if (isStealing)
	{
		if (chestSlotIndex >= chestSlots.size())
		{
			ResetSteal();
			Logger::Log("Finished Stealing");
			return;
		}

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastStealTime).count() < settings::CS_Delay) return;

		int windowId = SDK::Minecraft->GetGuiChest()->GetContainer()->GetWindowId();

		if (windowId == -1) return;

		SDK::Minecraft->playerController->WindowClick(windowId, chestSlots[chestSlotIndex], 0, 1, SDK::Minecraft->thePlayer);

		lastStealTime = std::chrono::steady_clock::now();
		chestSlotIndex++;
	}
}

void ChestStealer::RenderOverlay()
{
}

void ChestStealer::RenderMenu()
{
	static bool renderSettings = false;
	static bool renderChestStealerItems = false;

	ImGui::BeginGroup();

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("cs_header", ImVec2(425.f, renderSettings ? 130.f : 35.f), false))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::BeginGroup();
		Menu::ToggleButton(72, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::CS_Enabled);
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
			if (ImGui::BeginChild("cs_settings", ImVec2(425, 85), false))
			{
				Menu::Slider(73, "Delay (ms)", ImVec2(225, 0), &settings::CS_Delay, 0, 1000);
				Menu::KeybindButton(74, "Keybind", ImVec2(297, 0), settings::CS_Key);
				if (Menu::Button(75, "Edit Items", ImVec2(384, 0)))
				{
					renderChestStealerItems = !renderChestStealerItems;
				}

				RenderItems(renderChestStealerItems);
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

void ChestStealer::ResetSteal()
{
	isStealing = false;
	chestSlotIndex = 0;

	settings::CS_Enabled = false;
}

static std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

void ChestStealer::RenderItems(bool& isOpen)
{
	//if (!isOpen) return;

	//static char filterBuffer[128] = "";
	//static bool showAddPopup = false;


	//if (showAddPopup)
	//{
	//	ImGui::OpenPopup("Add Item Popup");
	//	showAddPopup = false;
	//}

	//// Popup for adding a block
	//if (ImGui::BeginPopup("Add Item Popup"))
	//{
	//	ImGui::Text("Select a Item to Add");
	//	ImGui::Separator();

	//	// Filter input
	//	ImGui::SetNextItemWidth(400);
	//	ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

	//	std::string filterLower = toLower(filterBuffer);

	//	// Filtered block list
	//	if (ImGui::BeginListBox("##blockList", ImVec2(300, 200)))
	//	{
	//		for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock)
	//		{
	//			// Convert block name to lowercase for comparison
	//			std::string blockNameLower = toLower(blockName);
	//			if (blockNameLower.find(filterLower) != std::string::npos)
	//			{
	//				if (ImGui::Selectable(blockName.c_str()))
	//				{
	//					// Add the selected block to userBlocks (ID, metadata pair)
	//					settings::CS_Items.push_back({ blockData.id, blockData.metadata });
	//					ImGui::CloseCurrentPopup();
	//				}
	//			}
	//		}
	//		ImGui::EndListBox();
	//	}

	//	// Close the popup
	//	if (ImGui::Button("Close"))
	//	{
	//		ImGui::CloseCurrentPopup();
	//	}

	//	ImGui::EndPopup();
	//}

	//ImGui::SetNextWindowSize(ImVec2(534, 255));
	//if (ImGui::Begin("  Chest Stealer", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	//{
	//	ImGui::SeparatorText("Items");

	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	if (ImGui::BeginListBox("##items", ImVec2(514, 145)))
	//	{
	//		for (int i = 0; i < settings::CS_Items.size(); i++)
	//		{
	//			const auto& item = settings::CS_Items[i];

	//			ImGui::Text("%s", MinecraftItems::GetNameByData(item.first, item.second).c_str());

	//			if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
	//			{
	//				ImGui::OpenPopup(("Delete Item " + std::to_string(item.first)).c_str());
	//			}

	//			if (ImGui::BeginPopup(("Delete Item " + std::to_string(item.first)).c_str()))
	//			{
	//				if (ImGui::Button("Delete"))
	//				{
	//					settings::CS_Items.erase(settings::CS_Items.begin() + i);
	//					i--;
	//					ImGui::CloseCurrentPopup();
	//				}
	//				ImGui::EndPopup();
	//			}
	//		}
	//		ImGui::EndListBox();
	//	}

	//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
	//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	if (ImGui::Button("Add Item", ImVec2(514, 22)))
	//	{
	//		showAddPopup = true;
	//	}

	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	if (ImGui::Button("Save & Close", ImVec2(514, 22)))
	//	{
	//		isOpen = false;
	//	}

	//	ImGui::PopStyleColor(3);
	//	ImGui::PopStyleVar();
	//}
	//ImGui::End();
}
