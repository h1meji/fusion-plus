#pragma once

#include "window/window.h"

#define INJECTOR_VERSION "0.0.1"

class Base
{
public:
	Base();
	void Run();
	void Cleanup();

	bool IsDllUpdated();
	bool IsInjectorUpdated();
	bool UpdateDll();
	bool UpdateInjector();

private:
	Window window;
};