#pragma once

#include "window/window.h"
#include <string>

#define INJECTOR_VERSION "0.0.3"

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
	static inline std::string new_injetor_version;
	bool IsDllUpdated();
	bool IsInjectorUpdated();
	bool UpdateDll();
	bool UpdateInjector();
}