#include "chestStealer.h"

#include <imgui/imgui_internal.h>

#include "menu/menu.h"
#include "moduleManager/commonData.h"
#include "util/minecraft/minecraft.h"
#include "util/keys.h"
#include "util/string.h"

void ChestStealer::Update()
{
	if (!settings::CS_Enabled) { ResetSteal(); return; }
	if (!CommonData::SanityCheck()) {ResetSteal(); return; }

	if (!SDK::minecraft->IsInChest()) { ResetSteal(); return; }

	if (!m_isStealing)
	{
		IInventory* inventory = SDK::minecraft->GetGuiChest()->GetLowerChestInventory();

		m_chestSlots.clear();
		for (int i = 0; i < inventory->GetSizeInventory(); i++)
		{
			CItemStack item = inventory->GetStackInSlot(i);
			if (item.GetInstance() == nullptr) continue;

			for (std::pair<int, int> id : settings::CS_Items)
			{
				if (item.GetItem().GetID() != id.first || (item.GetMetadata() != id.second && id.second != -1)) continue;
				m_chestSlots.push_back(i);
				break;
			}
		}

		m_isStealing = true;
		m_chestSlotIndex = 0;
		m_lastStealTime = std::chrono::steady_clock::now();
		m_activated = std::chrono::steady_clock::now();
	}

	if (m_isStealing)
	{
		if (m_chestSlotIndex >= m_chestSlots.size())
		{
			ResetSteal();
			return;
		}

		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_lastStealTime).count() < settings::CS_Delay) return;

		int windowId = SDK::minecraft->GetGuiChest()->GetContainer()->GetWindowId();

		if (windowId == -1) return;

		SDK::minecraft->playerController->WindowClick(windowId, m_chestSlots[m_chestSlotIndex], 0, 1, SDK::minecraft->thePlayer);

		m_lastStealTime = std::chrono::steady_clock::now();
		m_chestSlotIndex++;
	}
}

void ChestStealer::RenderMenu()
{
	static bool isOpen = false;

	ImVec2 windowPos = ImGui::GetWindowPos();
	windowPos.x += ImGui::GetWindowWidth() + 33.f;
	windowPos.y -= 74.f;

	Menu::ToggleWithKeybind(&settings::CS_Enabled, settings::CS_Key);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);
	Menu::HorizontalSeparator("Sep1");
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.f);

	Menu::Slider("Delay", &settings::CS_Delay, 0, 1000, ImVec2(0, 0), "%d ms");

	RenderItems(windowPos);
}

void ChestStealer::ResetSteal()
{
	m_isStealing = false;
	m_chestSlotIndex = 0;

	settings::CS_Enabled = false;
}

void ChestStealer::RenderItems(ImVec2 pos)
{
	static char filterBuffer[128] = "";
	static bool showAddPopup = false;


	if (showAddPopup)
	{
		ImGui::OpenPopup("Add Item Popup");
		showAddPopup = false;
	}

	// Popup for adding a block
	if (ImGui::BeginPopup("Add Item Popup"))
	{
		// Filter input
		ImGui::SetNextItemWidth(538);
		if (ImGui::IsWindowAppearing())
		{
			ImGui::SetKeyboardFocusHere();
		}
		ImGui::InputTextWithHint("##filter", "Filter...", filterBuffer, IM_ARRAYSIZE(filterBuffer));

		std::string filterLower = StringUtils::ToLower(filterBuffer);

		// Filtered block list
		if (ImGui::BeginListBox("##blockList", ImVec2(300, 200)))
		{
			for (const auto& [blockName, blockData] : MinecraftItems::nameToBlock)
			{
				// Convert block name to lowercase for comparison
				std::string blockNameLower = StringUtils::ToLower(blockName);
				if (blockNameLower.find(filterLower) != std::string::npos)
				{
					if (ImGui::Selectable(blockName.c_str()))
					{
						// Add the selected block to userBlocks (ID, metadata pair)
						settings::CS_Items.push_back({ blockData.id, blockData.metadata });
						ImGui::CloseCurrentPopup();
					}
				}
			}
			ImGui::EndListBox();
		}

		// Close the popup
		if (Menu::Button("Close", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

	ImGui::SetNextWindowPos(ImVec2(10.f, 10.f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400.f, 650.f));
	ImGui::Begin("ChestStealer", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImVec2 titleSize = Menu::boldFont24->CalcTextSizeA(24, FLT_MAX, 0.0f, "Chest Stealer Items");
		float leftWidth = ImGui::GetWindowWidth() - 40.f;
		float topHeight = titleSize.y + 20.f;

		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10.f, ImGui::GetCursorPosY() + 10.f)); // Change padding from 10 to 20
		ImGui::BeginGroup();

		ImGui::BeginChild("##WindowTitleCS", ImVec2(leftWidth, topHeight), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			Menu::BoldText("Chest Stealer Items", FontSize::SIZE_24);
		}
		ImGui::EndChild();

		ImGui::BeginChild("##ItemsList", ImVec2(leftWidth, ImGui::GetWindowHeight() - topHeight - 92.f), true);
		{
			bool scrollbar = ImGui::GetCurrentWindow()->ScrollMax.y > 0.0f;

			for (int i = 0; i < settings::CS_Items.size(); ++i)
			{
				const auto& item = settings::CS_Items[i];
				std::string itemName = MinecraftItems::GetNameByData(item.first, item.second);

				ImVec2 size = ImGui::GetWindowSize();
				ImVec2 deleteBtnSize = Menu::font18->CalcTextSizeA(18, FLT_MAX, 0.0f, "Delete");
				deleteBtnSize.x += ImGui::GetStyle().FramePadding.x * 8;

				static int length = 30;
				if (itemName.length() > length)
				{
					itemName = itemName.substr(0, length) + "...";
				}

				Menu::Button(itemName.c_str(), ImVec2(ImGui::GetWindowSize().x - deleteBtnSize.x - (scrollbar ? ImGui::GetStyle().ScrollbarSize : 0.f) - 28.f, 0.f));

				ImGui::SameLine();

				if (Menu::Button(("Delete###" + std::to_string(i)).c_str(), ImVec2(deleteBtnSize.x, 0.f)))
				{
					settings::CS_Items.erase(settings::CS_Items.begin() + i);
					break;
				}
			}
		}
		ImGui::EndChild();

		if (Menu::MenuButton("Add Item", ImVec2(ImGui::GetContentRegionAvail().x - 10.f, 32.f), FontSize::SIZE_18))
		{
			showAddPopup = true;
		}

		ImGui::EndGroup();
	}
	ImGui::End();
}
