#pragma once

#include <vector>
#include <memory>

#include "moduleBase.h"

class ModuleManager
{
public:
	void Init();

	void UpdateModules();
	void RenderUpdate();

	void RenderMenu(int index);

	std::vector<std::string> GetCategories();

private:
	std::vector<std::unique_ptr<ModuleBase>> modules;
};

inline std::unique_ptr<ModuleManager> g_ModuleManager;