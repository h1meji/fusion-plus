#include "inventorySorter.h"
#include <imgui/imgui.h>
#include <menu/menu.h>
#include <moduleManager/commonData.h>
#include "util/minecraft/inventory.h"
#include "util/keys.h"
#include <util/minecraft/minecraft.h>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>

void InventorySorter::Update()
{
	if (!settings::IS_Enabled) { ResetSort(false); return; }
	if (!CommonData::SanityCheck()) { ResetSort(false); return; }

	if (!SDK::Minecraft->IsInInventory()) { ResetSort(false); return; }

	if (!isDroppingUselessItems && !isDoingArmor && !isDoingSwords && !isCombiningStacks && !isSorting)
	{
		Logger::Log("Started Sorting");
		isDroppingUselessItems = true;
		DropUselessItems();
	}

	if (isDroppingUselessItems || isDoingArmor || isDoingSwords || isCombiningStacks || isSorting)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastSortTime).count() < settings::IS_Delay) return;

		if (pathIndex >= inventoryPath.size())
		{
			if (isDroppingUselessItems)
			{
				ResetSort(true);
				isDoingArmor = true;
				Logger::Log("Dropped Useless Items");
				DoArmor();
			}
			else if (isDoingArmor)
			{
				ResetSort(true);
				isCombiningStacks = true;
				Logger::Log("Did Armor");
				CombineStacks();
			}
			else if (isCombiningStacks)
			{
				ResetSort(true);
				isDoingSwords = true;
				Logger::Log("Combined Stacks");
				DoSwords();
			}
			else if (isDoingSwords)
			{
				ResetSort(true);
				isSorting = true;
				Logger::Log("Did Swords");
				GeneratePath();
			}
			else if (isSorting)
			{
				Logger::Log("Finished Sorting");
				ResetSort(false);
			}
			return;
		}

		PathNode node = inventoryPath[pathIndex];
		//Logger::Log("Slot: %d, Mode: %d, Button: %d", node.slotIndex, node.mode, node.button);
		int windowId = SDK::Minecraft->GetGuiChest()->GetContainer()->GetWindowId();
		SDK::Minecraft->playerController->WindowClick(windowId, node.slotIndex, node.button, node.mode, SDK::Minecraft->thePlayer);
		pathIndex++;
		lastSortTime = std::chrono::steady_clock::now();
	}
}

static float CalculateBestArmorValue(CItemStack& armorPiece, InventorySystem::ArmorType armorType) {
	if (armorPiece.GetInstance() == nullptr)
		return 0;

	InventorySystem::Material material = InventorySystem::GetMaterialFromName(armorPiece.GetItem().GetUnlocalizedName());
	for (const auto& enchantment : SDK::Minecraft->enchantmentHelper->GetEnchantments(armorPiece)) {
		if (enchantment.first == 0) { // Check if enchantment ID is 0
			return InventorySystem::CalculateDamageReduction(material, armorType, enchantment.second);
		}
	}
	return InventorySystem::CalculateDamageReduction(material, armorType, 0);
}

static float CalculateSwordDamage(CItemStack& swordPiece)
{
	if (swordPiece.GetInstance() == nullptr)
		return 0;

	InventorySystem::Material material = InventorySystem::GetMaterialFromName(swordPiece.GetItem().GetUnlocalizedName());
	for (const auto& enchantment : SDK::Minecraft->enchantmentHelper->GetEnchantments(swordPiece)) {
		if (enchantment.first == 16) { // Check if enchantment ID is 16
			return InventorySystem::CalculateDamage(material, enchantment.second);
		}
	}
	return InventorySystem::CalculateDamage(material, 0);
}

static int MainInventoryToWindowClick(int index)
{
	if (index < 9) return index + 36;
	return index;
}

void InventorySorter::DropUselessItems()
{
	CInventoryPlayer inventory = SDK::Minecraft->thePlayer->GetInventory();
	std::vector<CItemStack> mainInventory = inventory.GetMainInventory();
	std::vector<InventorySystem::Slot> slotInfo = InventorySystem::GetInventorySlots();

	std::vector<int> usefulItemIds = {
		298, // Leather Helmet
		299, // Leather Chestplate
		300, // Leather Leggings
		301, // Leather Boots
		302, // Chainmail Helmet
		303, // Chainmail Chestplate
		304, // Chainmail Leggings
		305, // Chainmail Boots
		306, // Iron Helmet
		307, // Iron Chestplate
		308, // Iron Leggings
		309, // Iron Boots
		310, // Diamond Helmet
		311, // Diamond Chestplate
		312, // Diamond Leggings
		313, // Diamond Boots
		314, // Gold Helmet
		315, // Gold Chestplate
		316, // Gold Leggings
		317, // Gold Boots
	};
	std::vector<int> usefulItemMetadatas = {
		-1, // Leather Helmet
		-1, // Leather Chestplate
		-1, // Leather Leggings
		-1, // Leather Boots
		-1, // Chainmail Helmet
		-1, // Chainmail Chestplate
		-1, // Chainmail Leggings
		-1, // Chainmail Boots
		-1, // Iron Helmet
		-1, // Iron Chestplate
		-1, // Iron Leggings
		-1, // Iron Boots
		-1, // Diamond Helmet
		-1, // Diamond Chestplate
		-1, // Diamond Leggings
		-1, // Diamond Boots
		-1, // Gold Helmet
		-1, // Gold Chestplate
		-1, // Gold Leggings
		-1, // Gold Boots
	};

	for (int i = 0; i < slotInfo.size(); i++)
	{
		if (slotInfo[i].item.id != -1)
		{
			usefulItemIds.push_back(slotInfo[i].item.id);
			usefulItemMetadatas.push_back(slotInfo[i].item.metadata);
		}

		for (int j = 0; j < slotInfo[i].category.items.size(); j++)
		{
			usefulItemIds.push_back(slotInfo[i].category.items[j].id);
			usefulItemMetadatas.push_back(slotInfo[i].category.items[j].metadata);
		}

		if (slotInfo[i].category.category == InventorySystem::ItemCategory::Sword)
		{
			usefulItemIds.push_back(267); // Iron Sword
			usefulItemMetadatas.push_back(-1);
			usefulItemIds.push_back(268); // Wooden Sword
			usefulItemMetadatas.push_back(-1);
			usefulItemIds.push_back(272); // Stone Sword
			usefulItemMetadatas.push_back(-1);
			usefulItemIds.push_back(276); // Diamond Sword
			usefulItemMetadatas.push_back(-1);
			usefulItemIds.push_back(283); // Gold Sword
			usefulItemMetadatas.push_back(-1);
		}
	}

	for (int i = 0; i < mainInventory.size(); i++)
	{
		CItemStack itemStack = mainInventory[i];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		bool isUseful = false;
		for (int j = 0; j < usefulItemIds.size(); j++)
		{
			if (usefulItemIds[j] == itemStack.GetItem().GetID() && (usefulItemMetadatas[j] == itemStack.GetMetadata() || usefulItemMetadatas[j] == -1))
			{
				isUseful = true;
				break;
			}
		}

		if (!isUseful)
		{
			inventoryPath.push_back({ MainInventoryToWindowClick(i), 4, 1 });
		}
	}
}

void InventorySorter::DoArmor()
{
	CInventoryPlayer inventory = SDK::Minecraft->thePlayer->GetInventory();
	std::vector<CItemStack> mainInventory = inventory.GetMainInventory();
	std::vector<CItemStack> armorInventory = inventory.GetArmorInventory();
	std::vector<InventorySystem::Slot> slotInfo = InventorySystem::GetInventorySlots();

	struct ArmorInfo {
		InventorySystem::ArmorType type;
		int armorSlot;
		int windowClickSlot;
		int bestSlot = -1;
		float bestValue = 0.0f;
	};

	std::vector<ArmorInfo> armorTypes = {
		{InventorySystem::ArmorType::HELMET,     3, 5},
		{InventorySystem::ArmorType::CHESTPLATE, 2, 6},
		{InventorySystem::ArmorType::LEGGINGS,   1, 7},
		{InventorySystem::ArmorType::BOOTS,      0, 8}
	};

	for (auto& armor : armorTypes)
	{
		CItemStack currentArmor = armorInventory[armor.armorSlot];
		armor.bestValue = CalculateBestArmorValue(currentArmor, armor.type);
	}

	std::vector<int> dropSlots;
	for (int i = 0; i < mainInventory.size(); i++)
	{
		CItemStack itemStack = mainInventory[i];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		std::map<int, int> enchantments = SDK::Minecraft->enchantmentHelper->GetEnchantments(itemStack);

		for (auto& armor : armorTypes)
		{
			if (itemStack.GetItem().GetUnlocalizedName().find(InventorySystem::ArmorTypeToString(armor.type)) != std::string::npos)
			{
				float itemValue = CalculateBestArmorValue(itemStack, armor.type);

				if (itemValue > armor.bestValue)
				{
					if (armor.bestSlot != -1)
					{
						dropSlots.push_back(armor.bestSlot);
					}
					armor.bestSlot = i;
					armor.bestValue = itemValue;
				}
				else
				{
					dropSlots.push_back(i);
				}
				break;
			}
		}
	}

	for (const ArmorInfo& armor : armorTypes)
	{
		if (armor.bestSlot != -1)
		{
			inventoryPath.push_back({ armor.windowClickSlot, 4, 0 });
			inventoryPath.push_back({ MainInventoryToWindowClick(armor.bestSlot), 1, 0 });
		}
	}

	for (int slot : dropSlots)
	{
		inventoryPath.push_back({ MainInventoryToWindowClick(slot), 4, 1 });
	}
}

void InventorySorter::CombineStacks()
{
	struct ItemStackInfo {
		int slot;
		int stackSize;
		int stackLimit;

		int id;
		int metadata;
	};

	CInventoryPlayer inventory = SDK::Minecraft->thePlayer->GetInventory();
	std::vector<CItemStack> mainInventory = inventory.GetMainInventory();
	
	const int slotOrder[36] = { 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	//const int slotOrder[36] = { 8, 7, 6, 5, 4, 3, 2, 1, 0, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9 };

	std::vector<ItemStackInfo> itemStacks;
	for (int i = 0; i < mainInventory.size(); i++) // combine window click mode goes top to bottom, left to right
	{
		CItemStack itemStack = mainInventory[slotOrder[i]];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		if (itemStack.GetStackSize() < itemStack.GetItem().GetStackLimit())
		{
			bool found = false;
			int stackSize = itemStack.GetStackSize();
			for (auto& stack : itemStacks)
			{
				if (stack.id == itemStack.GetItem().GetID() && stack.metadata == itemStack.GetMetadata() && stack.stackSize != stack.stackLimit)
				{
					if (stack.stackSize + stackSize <= stack.stackLimit)
					{
						stack.stackSize += stackSize;
						found = true;
						break;
					}
					else
					{
						stackSize = (stack.stackSize + stackSize) - stack.stackLimit;
						stack.stackSize = stack.stackLimit;
					}
				}
			}

			if (!found)
			{
				itemStacks.push_back({ slotOrder[i], stackSize, itemStack.GetItem().GetStackLimit(), itemStack.GetItem().GetID(), itemStack.GetMetadata() });
			}
		}
	}

	// if the last stack for an item is less than the stack limit, take the remaining items from the first stack
	for (int i = 0; i < itemStacks.size(); i++)
	{
		if (itemStacks[i].stackSize < itemStacks[i].stackLimit)
		{
			for (int j = 0; j < itemStacks.size(); j++)
			{
				if (i == j)
				{
					break; // gone through all stacks before this one
				}

				if (itemStacks[j].id == itemStacks[i].id && itemStacks[j].metadata == itemStacks[i].metadata)
				{
					int remaining = itemStacks[i].stackLimit - itemStacks[i].stackSize;
					if (itemStacks[j].stackSize <= remaining)
					{
						break; // no need to combine
					}
					else
					{
						itemStacks[i].stackSize = itemStacks[i].stackLimit;
						itemStacks[j].stackSize -= remaining;
					}
				}
			}
		}
	}

	for (int i = 0; i < itemStacks.size(); i++)
	{
		inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].slot), 0, 0 });
		inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].slot), 6, 0 });
		inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].slot), 0, 0 });
	}
}

void InventorySorter::DoSwords()
{
	CInventoryPlayer inventory = SDK::Minecraft->thePlayer->GetInventory();
	std::vector<CItemStack> mainInventory = inventory.GetMainInventory();
	std::vector<InventorySystem::Slot> slotInfo = InventorySystem::GetInventorySlots();

	std::vector<int> swordSlots;
	std::vector<std::pair<int, int>> swordValues;
	const int slotOrder[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 27, 28, 29, 30, 31, 32, 33, 34, 35, 18, 19, 20, 21, 22, 23, 24, 25, 26, 9, 10, 11, 12, 13, 14, 15, 16, 17 };

	for (int i = 0; i < slotInfo.size(); i++)
	{
		if (slotInfo[slotOrder[i]].category.category == InventorySystem::ItemCategory::Sword)
		{
			swordSlots.push_back(slotOrder[i]);

			if (mainInventory[slotOrder[i]].GetInstance() == nullptr)
				swordValues.push_back({ -1, 0 });
			else
				swordValues.push_back({ slotOrder[i], CalculateSwordDamage(mainInventory[slotOrder[i]]) });
		}
	}

	std::vector<int> swordPositions;
	for (int i = 0; i < mainInventory.size(); i++)
	{
		CItemStack itemStack = mainInventory[slotOrder[i]];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		std::map<int, int> enchantments = SDK::Minecraft->enchantmentHelper->GetEnchantments(itemStack);

		if (itemStack.GetItem().GetUnlocalizedName().find("sword") != std::string::npos)
		{
			for (int j = 0; j < swordSlots.size(); j++)
			{
				if (swordSlots[j] == slotOrder[i])
				{
					break;
				}

				float itemValue = CalculateSwordDamage(itemStack);
				if (swordValues[j].second < itemValue)
				{
					std::pair<int, int> swordValue = { slotOrder[i], CalculateSwordDamage(itemStack) };
					swordValues.insert(swordValues.begin() + j, swordValue);
					swordValues.pop_back();
					break;
				}
			}

			swordPositions.push_back(slotOrder[i]);
		}
	}

	// drop useless swords
	for (int slot : swordPositions)
	{
		bool isUsed = false;
		for (std::pair<int, int> swordValue : swordValues)
		{
			if (slot == swordValue.first)
			{
				isUsed = true;
			}
		}

		if (!isUsed)
		{
			inventoryPath.push_back({ MainInventoryToWindowClick(slot), 4, 1 });
		}
	}

	// sword path
	for (int i = 0; i < swordSlots.size(); i++)
	{
		if (swordValues[i].first != -1 && swordSlots[i] != swordValues[i].first)
		{
			inventoryPath.push_back({ MainInventoryToWindowClick(swordSlots[i]), 0, 0 }); // pickup the wrong item
			inventoryPath.push_back({ MainInventoryToWindowClick(swordValues[i].first), 0, 0 }); // swap the items
			inventoryPath.push_back({ MainInventoryToWindowClick(swordSlots[i]), 0, 0 }); // drop at the correct slot

			for (int j = 0; j < swordSlots.size(); j++)
			{
				if (swordSlots[i] == swordValues[j].first)
				{
					swordValues[j].first = swordValues[i].first;
					break;
				}
			}
		}
	}
}

struct ItemStackInfo
{
	int targetSlot;
	int sourceSlot;

	int stackSize;
	int priority;

	int id;
	int metadata;
};

void InventorySorter::GeneratePath()
{
	CInventoryPlayer inventory = SDK::Minecraft->thePlayer->GetInventory();
	std::vector<CItemStack> mainInventory = inventory.GetMainInventory();
	std::vector<InventorySystem::Slot> slotInfo = InventorySystem::GetInventorySlots();

	const int slotOrder[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 27, 28, 29, 30, 31, 32, 33, 34, 35, 18, 19, 20, 21, 22, 23, 24, 25, 26, 9, 10, 11, 12, 13, 14, 15, 16, 17 };

	std::vector<ItemStackInfo> itemStacks(slotInfo.size(), { -1, -1, -1, 999, -1, -1 });

	// Recursive function to place an item and handle displacement
	std::function<bool(CItemStack&, const int, int)> placeItem = [&](CItemStack& itemStack, const int sourceSlot, int depth) -> bool {
		if (depth > 50) {  // Prevent excessive recursion
			Logger::Log("Recursion depth exceeded for item placement.");
			return false;
		}

		for (int j = 0; j < itemStacks.size(); j++)
		{
			if (slotInfo[slotOrder[j]].category.category == InventorySystem::ItemCategory::Armor ||
				slotInfo[slotOrder[j]].category.category == InventorySystem::ItemCategory::Sword)
				continue;

			if (slotInfo[slotOrder[j]].item.id == itemStack.GetItem().GetID() && slotInfo[slotOrder[j]].item.metadata == itemStack.GetMetadata())
			{
				if (itemStacks[slotOrder[j]].stackSize < itemStack.GetStackSize())
				{
					if (itemStacks[slotOrder[j]].sourceSlot != -1) {
						Logger::Log("Slot %d is already occupied. Displacing item.", j);
						CItemStack displacedItem = mainInventory[itemStacks[slotOrder[j]].sourceSlot];
						int displacedSourceSlot = itemStacks[slotOrder[j]].sourceSlot;

						if (!placeItem(displacedItem, displacedSourceSlot, depth + 1)) {
							return false;  // If the displaced item cannot be placed, abort
						}
					}

					itemStacks[slotOrder[j]].stackSize = itemStack.GetStackSize();
					itemStacks[slotOrder[j]].sourceSlot = sourceSlot;
					itemStacks[slotOrder[j]].targetSlot = slotOrder[j];
					return true;
				}
			}

			// Check if the current slot can hold the item
			for (int k = 0; k < slotInfo[slotOrder[j]].category.items.size(); k++) {
				const auto& categoryItem = slotInfo[slotOrder[j]].category.items[k];

				// Match by ID and metadata
				if (categoryItem.id == itemStack.GetItem().GetID() && categoryItem.metadata == itemStack.GetMetadata())
				{
					bool replace = false;

					// Replace if priority is better or stack size is larger at same priority
					if (categoryItem.priority < itemStacks[slotOrder[j]].priority ||
						(categoryItem.priority == itemStacks[slotOrder[j]].priority && itemStack.GetStackSize() > itemStacks[slotOrder[j]].stackSize)) {
						replace = true;
					}

					if (replace) {
						// If there is already an item in this slot, try to move it elsewhere
						if (itemStacks[slotOrder[j]].sourceSlot != -1) {
							Logger::Log("Slot %d is already occupied. Displacing item.", j);
							CItemStack displacedItem = mainInventory[itemStacks[slotOrder[j]].sourceSlot];
							int displacedSourceSlot = itemStacks[slotOrder[j]].sourceSlot;

							if (!placeItem(displacedItem, displacedSourceSlot, depth + 1)) {
								return false;  // If the displaced item cannot be placed, abort
							}
						}

						// Place the new item in this slot
						itemStacks[slotOrder[j]].targetSlot = slotOrder[j];
						itemStacks[slotOrder[j]].sourceSlot = sourceSlot;
						itemStacks[slotOrder[j]].stackSize = itemStack.GetStackSize();
						itemStacks[slotOrder[j]].priority = categoryItem.priority;

						return true;
					}
				}
			}
		}

		return false;  // Could not place item in this slot
	};

	// Main logic
	for (int i = 0; i < mainInventory.size(); i++) {
		CItemStack itemStack = mainInventory[slotOrder[i]];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		placeItem(itemStack, slotOrder[i], 0);
	}

	// drop useless items (loop through the main inventory, find slots with still items in them, then check if they are a source slot somewhere)
	for (int i = 0; i < mainInventory.size(); i++)
	{
		CItemStack itemStack = mainInventory[slotOrder[i]];
		if (itemStack.GetInstance() == nullptr || itemStack.GetItem().GetInstance() == nullptr)
			continue;

		bool isUsed = false;
		for (int j = 0; j < itemStacks.size(); j++)
		{
			if (itemStacks[j].sourceSlot == slotOrder[i])
			{
				isUsed = true;
				break;
			}
		}

		if (itemStack.GetItem().GetUnlocalizedName().find("sword") != std::string::npos)
		{
			isUsed = true;
		}

		if (!isUsed)
		{
			inventoryPath.push_back({ MainInventoryToWindowClick(slotOrder[i]), 4, 1 });
		}
	}

	// generate the path
	for (int i = 0; i < itemStacks.size(); i++)
	{
		if (itemStacks[i].sourceSlot != itemStacks[i].targetSlot)
		{
			inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].targetSlot), 0, 0}); // pickup the wrong item
			inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].sourceSlot), 0, 0 }); // swap the items
			inventoryPath.push_back({ MainInventoryToWindowClick(itemStacks[i].targetSlot), 0, 0 }); // drop at the correct slot

			for (int j = 0; j < itemStacks.size(); j++)
			{
				if (itemStacks[i].targetSlot == itemStacks[j].sourceSlot)
				{
					itemStacks[j].sourceSlot = itemStacks[i].sourceSlot;
					break;
				}
			}
		}
	}

	// DEBUG: Log itemStacks
	for (int i = 0; i < itemStacks.size(); i++) {
		Logger::Log("Slot: %d, Source: %d, Target: %d, StackSize: %d, Priority: %d", i, itemStacks[i].sourceSlot, itemStacks[i].targetSlot, itemStacks[i].stackSize, itemStacks[i].priority);
	}
}

void InventorySorter::ResetSort(bool enabled)
{
	isDroppingUselessItems = false;
	isDoingArmor = false;
	isCombiningStacks = false;
	isDoingSwords = false;
	isSorting = false;
	inventoryPath.clear();
	pathIndex = 0;

	settings::IS_Enabled = enabled;
}

void InventorySorter::RenderOverlay()
{
}

void InventorySorter::RenderMenu()
{
	//static bool renderSettings = false;

	//ImGui::BeginGroup();

	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	//ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	//if (ImGui::BeginChild("is_header", ImVec2(425.f, renderSettings ? 130.f : 35.f), false))
	//{
	//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	//	ImGui::BeginGroup();
	//	Menu::ToggleButton(76, ("Toggle " + this->GetName()).c_str(), ImVec2(368, 0), &settings::IS_Enabled);
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
	//		if (ImGui::BeginChild("is_settings", ImVec2(425, 85), false))
	//		{
	//			Menu::Slider(77, "Delay (ms)", ImVec2(225, 0), &settings::IS_Delay, 0, 1000);
	//			Menu::KeybindButton(78, "Keybind", ImVec2(297, 0), settings::IS_Key);

	//			static bool renderInventoryEditor = false;
	//			if (Menu::Button(79, "Open Inventory Editor", ImVec2(384, 0)))
	//			{
	//				renderInventoryEditor = !renderInventoryEditor;
	//			}

	//			RenderInventoryEditor(renderInventoryEditor);
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

static std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

void InventorySorter::RenderInventoryEditor(bool& isOpen)
{
	//if (!isOpen) return;
 //   ImGui::SetNextWindowSize(ImVec2(534, 602));
	//std::vector<InventorySystem::Category> categories = InventorySystem::GetCategories();
	//if (ImGui::Begin("  Inventory Editor", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	//{
	//	ImGui::SeparatorText("Armor Slots");
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	ImGui::BeginGroup();
	//	std::vector<InventorySystem::Slot> armorSlots = InventorySystem::GetArmorSlots();
	//	for (int i = 0; i < 4; i++)
	//	{
	//		InventorySystem::Slot slot = armorSlots[i];
	//		ImGui::PushID(i);
	//		ImGui::BeginDisabled();
	//		if (ImGui::Button(slot.category.name.c_str(), ImVec2(50, 50)))
	//		{
	//		}
	//		ImGui::EndDisabled();

	//		ImGui::PopID();

	//		if (i < 3) ImGui::SameLine();
	//	}
	//	ImGui::EndGroup();

	//	ImGui::SeparatorText("Inventory Slots");
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	ImGui::BeginGroup();
	//	std::vector<InventorySystem::Slot> inventorySlots = InventorySystem::GetInventorySlots();
	//	for (int i = 0; i < 27; i++)
	//	{
	//		InventorySystem::Slot slot = inventorySlots[i + 9];
	//		ImGui::PushID(4 + i);

	//		std::string slotName = "";
	//		if (slot.item.id != -1)
	//		{
	//			slotName = MinecraftItems::GetNameByData(slot.item.id, slot.item.metadata);
	//		}
	//		else
	//		{
	//			slotName = slot.category.name;
	//		}

	//		if (ImGui::Button(slotName.c_str(), ImVec2(50, 50)))
	//		{
	//			ImGui::OpenPopup("CategorySelector");
	//		}
	//		if (ImGui::IsItemHovered())
	//		{
	//			ImGui::BeginTooltip();
	//			ImGui::Text(slotName.c_str());
	//			ImGui::EndTooltip();
	//		}

	//		if (ImGui::BeginPopup("CategorySelector"))
	//		{
	//			ImGui::Text("Select an Item Category");
	//			if (ImGui::BeginListBox("##listbox", ImVec2(300, 100)))
	//			{
	//				for (int j = 0; j < categories.size(); j++)
	//				{
	//					InventorySystem::Category category = categories[j];
	//					if (ImGui::Selectable(category.name.c_str()))
	//					{
	//						InventorySystem::AddCategoryToSlot(i + 9, j);
	//						ImGui::CloseCurrentPopup();
	//					}
	//				}
	//				ImGui::EndListBox();
	//			}

	//			ImGui::Text("Select an Item");
	//			static char filterBuffer[128] = "";
	//			static bool showAddPopup = false;

	//			ImGui::SetNextItemWidth(400);
	//			ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

	//			std::string filterLower = toLower(filterBuffer);

	//			if (ImGui::BeginListBox("##blockList", ImVec2(300, 100)))
	//			{
	//				for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock) {
	//					std::string blockNameLower = toLower(blockName);
	//					if (blockNameLower.find(filterLower) != std::string::npos) {
	//						if (ImGui::Selectable(blockName.c_str())) {
	//							// Add the selected block to userBlocks (ID, metadata pair)
	//							Logger::Log("Block Name: %s", blockName.c_str());
	//							InventorySystem::AddItemToSlot(i + 9, blockData.id, blockData.metadata);
	//							Logger::Log("Slot: %d", i + 9);
	//							ImGui::CloseCurrentPopup();
	//						}
	//					}
	//				}
	//				ImGui::EndListBox();
	//			}

	//			ImGui::EndPopup();
	//		}

	//		ImGui::PopID();

	//		// 3x9 grid
	//		if (i % 9 != 8)
	//		{
	//			ImGui::SameLine();
	//		}
	//	}
	//	ImGui::EndGroup();

	//	ImGui::SeparatorText("Hotbar Slots");
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	ImGui::BeginGroup();
	//	for (int i = 0; i < 9; i++)
	//	{
	//		InventorySystem::Slot slot = inventorySlots[i];
	//		ImGui::PushID(31 + i);

	//		std::string slotName = "";
	//		if (slot.item.id != -1)
	//		{
	//			slotName = MinecraftItems::GetNameByData(slot.item.id, slot.item.metadata);
	//		}
	//		else
	//		{
	//			slotName = slot.category.name;
	//		}

	//		if (ImGui::Button(slotName.c_str(), ImVec2(50, 50)))
	//		{
	//			ImGui::OpenPopup("CategorySelector");
	//		}
	//		if (ImGui::IsItemHovered())
	//		{
	//			ImGui::BeginTooltip();
	//			ImGui::Text(slotName.c_str());
	//			ImGui::EndTooltip();
	//		}

	//		if (ImGui::BeginPopup("CategorySelector"))
	//		{
	//			ImGui::Text("Select an Item Category");
	//			if (ImGui::BeginListBox("##listbox", ImVec2(300, 100)))
	//			{
	//				for (int j = 0; j < categories.size(); j++)
	//				{
	//					InventorySystem::Category category = categories[j];
	//					if (ImGui::Selectable(category.name.c_str()))
	//					{
	//						InventorySystem::AddCategoryToSlot(i, j);
	//						Logger::Log("Slot: %d", i);
	//						ImGui::CloseCurrentPopup();
	//					}
	//				}
	//				ImGui::EndListBox();
	//			}

	//			ImGui::Text("Select an Item");
	//			static char filterBuffer[128] = "";
	//			static bool showAddPopup = false;

	//			ImGui::SetNextItemWidth(400);
	//			ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

	//			std::string filterLower = toLower(filterBuffer);

	//			if (ImGui::BeginListBox("##blockList", ImVec2(300, 100)))
	//			{
	//				for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock) {
	//					std::string blockNameLower = toLower(blockName);
	//					if (blockNameLower.find(filterLower) != std::string::npos) {
	//						if (ImGui::Selectable(blockName.c_str())) {
	//							InventorySystem::AddItemToSlot(i, blockData.id, blockData.metadata);
	//							Logger::Log("Slot: %d", i);
	//							ImGui::CloseCurrentPopup();
	//						}
	//					}
	//				}
	//				ImGui::EndListBox();
	//			}

	//			ImGui::EndPopup();
	//		}
	//		ImGui::PopID();
	//		ImGui::SameLine();
	//	}
	//	ImGui::EndGroup();

	//	ImGui::SeparatorText("Custom Categories");
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	static bool renderCreateCategory = false;
	//	static int selectedCategory = -1;
	//	if (ImGui::BeginListBox("##customcategories", ImVec2(514, 150)))
	//	{
	//		for (int i = 0; i < categories.size(); i++)
	//		{
	//			if (categories[i].category != InventorySystem::ItemCategory::Custom) continue;
	//			ImGui::PushID(60 + i);
	//			if (ImGui::Selectable(categories[i].name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
	//			{
	//				if (ImGui::IsMouseDoubleClicked(0))
	//				{
	//					Logger::Log("Double Clicked Category %s", categories[i].name.c_str());
	//					selectedCategory = i;
	//					renderCreateCategory = true;
	//				}
	//			}
	//			if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
	//			{
	//				ImGui::OpenPopup(("Delete Category " + categories[i].name).c_str());
	//			}

	//			if (ImGui::BeginPopup(("Delete Category " + categories[i].name).c_str()))
	//			{
	//				if (ImGui::Button("Delete"))
	//				{
	//					InventorySystem::RemoveCategory(i);
	//					i--;
	//					ImGui::CloseCurrentPopup();
	//				}
	//				ImGui::EndPopup();
	//			}
	//			ImGui::PopID();
	//		}
	//		ImGui::EndListBox();
	//	}

	//	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
	//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	if (ImGui::Button("Create Category", ImVec2(450, 22)))
	//	{
	//		renderCreateCategory = !renderCreateCategory;
	//		selectedCategory = -1;
	//	}
	//	ImGui::SameLine();
	//	if (ImGui::Button("Help", ImVec2(54, 22)))
	//	{
	//		ImGui::OpenPopup("Help");
	//	}

	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 5));
	//	if (ImGui::BeginPopup("Help"))
	//	{
	//		ImGui::SeparatorText("How does the Inventory Editor work?");
	//		ImGui::Text("For each slot in the inventory, you can assign a category or a specific item.");
	//		ImGui::Text("To assign something to a slot, click on the slot and select a category or item.");
	//		ImGui::Separator();
	//		ImGui::SeparatorText("What are Categories?");
	//		ImGui::Text("Categories are groups of items that you can assign to slots.");
	//		ImGui::Separator();
	//		ImGui::SeparatorText("How does Priority work?");
	//		ImGui::Text("Items have priorities. Higher-priority items replace lower ones.");
	//		ImGui::Text("If a top-priority item is missing, the next priority is used.");
	//		ImGui::Separator();
	//		ImGui::SeparatorText("How do I create a Category?");
	//		ImGui::Text("Click on 'Create Category' and enter a name for the category.");
	//		ImGui::Text("Then, add items to the category and set their priorities.");
	//		ImGui::Separator();
	//		ImGui::SeparatorText("How do I edit a Category?");
	//		ImGui::Text("Double-click on a category to open the editor.");
	//		ImGui::Text("You can then add or remove items and change their priorities.");
	//		ImGui::Separator();
	//		ImGui::SeparatorText("Can I edit or delete default categories?");
	//		ImGui::Text("No, you can only edit or delete custom categories.");
	//		ImGui::Text("For the armor slots, the categories are fixed.");

	//		ImGui::EndPopup();
	//	}
	//	ImGui::PopStyleVar();


	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	//	if (ImGui::Button("Save & Close", ImVec2(514, 22)))
	//	{
	//		isOpen = false;
	//	}

	//	ImGui::PopStyleColor(3);
	//	ImGui::PopStyleVar();

	//	RenderCreateCategory(renderCreateCategory, selectedCategory);
	//	selectedCategory = -1;
 //   }
 //   ImGui::End();
}

void InventorySorter::RenderCreateCategory(bool& isOpen, int categoryIndex = -1)
{
	/*static std::vector<InventorySystem::Item> itemsForCategory;
	static bool isEditing = false;
	if (!isOpen)
	{
		if (!itemsForCategory.empty())
		{
			itemsForCategory.clear();
		}
		if (isEditing)
			isEditing = false;
		return;
	}

	static bool showAddPopup = false;
	static char filterBuffer[128] = "";
	static std::pair<int, int> selectedBlock = { -1, -1 };

	if (showAddPopup) {
		ImGui::OpenPopup("Add Item Popup");
		showAddPopup = false;
	}

	if (ImGui::BeginPopup("Add Item Popup")) {
		ImGui::Text("Select an Item to Add");
		ImGui::Separator();

		ImGui::SetNextItemWidth(400);
		ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

		std::string filterLower = toLower(filterBuffer);

		if (ImGui::BeginListBox("##blockList", ImVec2(300, 200)))
		{
			for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock) {
				std::string blockNameLower = toLower(blockName);
				if (blockNameLower.find(filterLower) != std::string::npos) {
					if (ImGui::Selectable(blockName.c_str())) {
						selectedBlock = { blockData.id, blockData.metadata };
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndListBox();
		}

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	if (selectedBlock.first != -1) {
		itemsForCategory.push_back({ selectedBlock.first, selectedBlock.second, 0 });
		selectedBlock = { -1, -1 };
	}

	ImGui::SetNextWindowSize(ImVec2(534, 306));

	static char categoryName[128] = "";
	static int categoryIndexCopy = -1;
	if (categoryIndex != -1) {
		categoryIndexCopy = categoryIndex;
		InventorySystem::Category category = InventorySystem::GetCategories()[categoryIndex];
		itemsForCategory = category.items;
		strcpy_s(categoryName, category.name.c_str());
		categoryIndex = -1;
		isEditing = true;
	}

	if (ImGui::Begin("  Create Category", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		ImGui::SeparatorText("Category Name");
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		ImGui::SetNextItemWidth(514.0f);
		ImGui::InputText("##categoryName", categoryName, IM_ARRAYSIZE(categoryName));

		ImGui::SeparatorText("Items");
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		if (ImGui::BeginListBox("##items", ImVec2(514, 150))) {
			for (int i = 0; i < itemsForCategory.size(); i++)
			{
				InventorySystem::Item& item = itemsForCategory[i];

				ImGui::Text("%s", MinecraftItems::GetNameByData(item.id, item.metadata).c_str());

				if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
					ImGui::OpenPopup(("Delete Item " + MinecraftItems::GetNameByData(item.id, item.metadata)).c_str());
				}

				if (ImGui::BeginPopup(("Delete Item " + MinecraftItems::GetNameByData(item.id, item.metadata)).c_str())) {
					if (ImGui::Button("Delete")) {
						itemsForCategory.erase(itemsForCategory.begin() + i);
						i--;
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				ImGui::SameLine(ImGui::GetWindowWidth() - 100);
				ImGui::InputInt(("##priority" + std::to_string(i)).c_str(), &item.priority, 1, 1, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("Item Priority");
					ImGui::EndTooltip();
				}
			}
			ImGui::EndListBox();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(settings::Menu_AccentColor[0] * 0.82f, settings::Menu_AccentColor[1] * 0.82f, settings::Menu_AccentColor[2] * 0.82f, settings::Menu_AccentColor[3] * 0.82f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(settings::Menu_AccentColor[0], settings::Menu_AccentColor[1], settings::Menu_AccentColor[2], settings::Menu_AccentColor[3]));

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		if (ImGui::Button("Add Item", ImVec2(514, 22)))
		{
			showAddPopup = true;
		}

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
		if (ImGui::Button(isEditing ? "Edit" : "Create", ImVec2(400, 22)))
		{
			if (isEditing)
				InventorySystem::EditCustomCategory(categoryIndexCopy, itemsForCategory, categoryName);
			else
				InventorySystem::CreateCustomCategory(itemsForCategory, categoryName);

			isOpen = false;
			itemsForCategory.clear();
			categoryName[0] = '\0';
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Close", ImVec2(104, 22)))
		{
			isOpen = false;
			itemsForCategory.clear();
			categoryName[0] = '\0';
			ImGui::CloseCurrentPopup();
		}

		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();
	}
	ImGui::End();*/
}
