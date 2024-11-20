#pragma once

#include "window/window.h"

#define INJECTOR_VERSION "0.0.1"

class Base
{
public:
	Base();
	void Run();
	void Cleanup();

private:
	Window window;
};

namespace BaseUtils
{
	bool IsDllUpdated();
	bool IsInjectorUpdated();
	bool UpdateDll();
	bool UpdateInjector();
}