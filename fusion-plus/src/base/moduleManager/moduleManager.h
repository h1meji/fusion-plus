#pragma once

#include <vector>
#include <memory>

#include "moduleBase.h"

class ModuleManager
{
public:
	void Init();

	void UpdateModules();
	void RenderOverlay();
	void RenderHud();

	void RenderMenu(int index);

	std::vector<std::string> GetCategories();
	std::vector<std::unique_ptr<ModuleBase>>& GetModules() { return modules; }
	int GetFirstModuleIndexByCategory(const std::string& category);

private:
	std::vector<std::unique_ptr<ModuleBase>> modules;
};

inline std::unique_ptr<ModuleManager> g_ModuleManager;