#include "chestStealer.h"
#include <imgui/imgui.h>
#include <menu/menu.h>
#include <moduleManager/commonData.h>

#include "util/minecraft.h"

void ChestStealer::Update()
{
	if (!settings::CS_Enabled) { ResetSteal(); return; }
	if (!CommonData::SanityCheck()) { ResetSteal(); return; }

	if (!SDK::Minecraft->IsInChest()) { ResetSteal(); return; }

	if (GetAsyncKeyState(settings::CS_Key) && 1)
	{
		if (isStealing && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - activated).count() > 100)
		{
			ResetSteal();
			Logger::Log("Stopped Stealing");
			activated = std::chrono::steady_clock::now();
			return;
		}
		else if (!isStealing && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - activated).count() > 100)
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
					//Logger::Log("Item Matches Id: %d", id);
					chestSlots.push_back(i);
					break;
				}
			}

			isStealing = true;
			chestSlotIndex = 0;
			lastStealTime = std::chrono::steady_clock::now();
			activated = std::chrono::steady_clock::now();
		}
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
		SDK::Minecraft->playerController->WindowClick(windowId, chestSlots[chestSlotIndex], 0, 1, SDK::Minecraft->thePlayer);

		lastStealTime = std::chrono::steady_clock::now();
		chestSlotIndex++;
	}
}

void ChestStealer::RenderUpdate()
{
}

void ChestStealer::RenderMenu()
{
	static bool renderSettings = false;

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("cheststealer", ImVec2(425, renderSettings ? 190 : 35)))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		ImGui::BeginGroup();
		Menu::DoToggleButtonStuff(230044, "Toggle Chest Stealer", &settings::CS_Enabled);
		ImGui::EndGroup();
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			renderSettings = !renderSettings;
		}

		if (renderSettings)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
			ImGui::Separator();

			Menu::DoSliderStuff(36456, "Delay (ms)", &settings::CS_Delay, 0, 1000);

			Menu::DoKeybindStuff(456745, "Keybind", settings::CS_Key);

			RenderItems();

			ImGui::Spacing();
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void ChestStealer::ResetSteal()
{
	isStealing = false;
	chestSlotIndex = 0;
}

std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

void ChestStealer::RenderItems()
{
	static char filterBuffer[128] = "";
	static bool showAddPopup = false;


	if (showAddPopup) {
		ImGui::OpenPopup("Add Item Popup");
		showAddPopup = false;
	}

	// Popup for adding a block
	if (ImGui::BeginPopup("Add Item Popup")) {
		ImGui::Text("Select a Item to Add");
		ImGui::Separator();

		// Filter input
		ImGui::SetNextItemWidth(400);
		ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

		std::string filterLower = toLower(filterBuffer);

		// Filtered block list
		if (ImGui::BeginListBox("##blockList", ImVec2(300, 200)))
		{
			for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock) {
				// Convert block name to lowercase for comparison
				std::string blockNameLower = toLower(blockName);
				if (blockNameLower.find(filterLower) != std::string::npos) {
					if (ImGui::Selectable(blockName.c_str())) {
						// Add the selected block to userBlocks (ID, metadata pair)
						settings::CS_Items.push_back({ blockData.id, blockData.metadata });
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndListBox();
		}


		// Close the popup
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	// Tree node to display all blocks
	if (ImGui::TreeNode("Items")) {
		// Button to add a block
		if (ImGui::Button("Add Item")) {
			ImGui::OpenPopup("Add Item Popup");
			showAddPopup = true;
		}

		for (int i = 0; i < settings::CS_Items.size(); i++)
		{
			const auto& block = settings::CS_Items[i];

			ImGui::Text("%s", MinecraftItems::GetNameByData(block.first, block.second).c_str());

			// Right-click to show delete tooltip
			if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
				ImGui::OpenPopup(("Delete Item " + std::to_string(block.first)).c_str());
			}

			if (ImGui::BeginPopup(("Delete Item " + std::to_string(block.first)).c_str())) {
				if (ImGui::Button("Delete")) {
					settings::CS_Items.erase(settings::CS_Items.begin() + i);
					i--;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}
		ImGui::TreePop();
	}
}
