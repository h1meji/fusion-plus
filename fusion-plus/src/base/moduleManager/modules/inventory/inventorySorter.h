#pragma once

#include <string>
#include <vector>
#include <chrono>

#include "moduleManager/moduleBase.h"

struct PathNode
{
	int slotIndex;
	int mode;
	int button;
};

class InventorySorter : public ModuleBase
{
public:
	void Update() override;

	void RenderOverlay() override {};
	void RenderHud() override {};
	void RenderMenu() override;

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::IS_Key; }

	bool IsEnabled() override { return settings::IS_Enabled; }
	void SetEnabled(bool enabled) override { settings::IS_Enabled = enabled; }
	void Toggle() override { settings::IS_Enabled = !settings::IS_Enabled; }

private:
	std::string m_name = "Inventory Sorter";
	std::string m_category = "Inventory";

	bool m_isSorting;
	std::chrono::time_point<std::chrono::steady_clock> m_lastSortTime;
	std::chrono::time_point<std::chrono::steady_clock> m_activated;
	std::vector<PathNode> m_inventoryPath;
	int m_pathIndex = 0;

	bool m_isDroppingUselessItems;
	bool m_isDoingArmor;
	bool m_isDoingSwords;
	bool m_isCombiningStacks;

	void DropUselessItems();
	void DoArmor();
	void CombineStacks();
	void DoSwords();

	void GeneratePath();
	void ResetSort(bool enabled);
	void RenderInventoryEditor(bool& isOpen);
	void RenderCreateCategory(bool& isOpen, int categoryIndex);
};