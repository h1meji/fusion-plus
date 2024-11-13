#include "moduleManager.h"

#include "modules/visual/esp.h"
#include "modules/visual/arrayList.h"
#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/clicker/leftAutoClicker.h"
#include "modules/clicker/rightAutoClicker.h"
#include "commonData.h"

void ModuleManager::Init()
{
	modules.push_back(std::make_unique<Esp>());
	modules.push_back(std::make_unique<ArrayList>());
	modules.push_back(std::make_unique<AimAssist>());
	modules.push_back(std::make_unique<Reach>());
	modules.push_back(std::make_unique<LeftAutoClicker>());
	modules.push_back(std::make_unique<RightAutoClicker>());
}

void ModuleManager::UpdateModules()
{
	if (!CommonData::SanityCheck()) return;

	CommonData::UpdateData();

	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->Update();
	}
}

void ModuleManager::RenderUpdate()
{
	for (auto& module : modules)
	{
		if (module->IsEnabled())
			module->RenderUpdate();
	}
}

void ModuleManager::RenderMenu(int index)
{
	if (index < 0)
		return;

	std::vector<std::string> categories = GetCategories();
	for (auto& module : modules)
	{
		if (module->GetCategory() == categories[index])
			module->RenderMenu();
	}
}

std::vector<std::string> ModuleManager::GetCategories()
{
	std::vector<std::string> categories;

	for (auto& module : modules)
	{
		if (std::find(categories.begin(), categories.end(), module->GetCategory()) == categories.end())
			categories.push_back(module->GetCategory());
	}

	return categories;
}