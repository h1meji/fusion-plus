#pragma once

#include <string>

#include "configManager/settings.h"

class ModuleBase
{
public:
	virtual void Update() = 0;
	virtual void RenderOverlay() = 0;
	virtual void RenderHud() = 0;

	virtual void RenderMenu() = 0;

	virtual bool IsEnabled() = 0;
	virtual std::string GetName() = 0;
	virtual std::string GetCategory() = 0;
	virtual int GetKey() = 0;

private:
	std::string Name;
	std::string Category;
};