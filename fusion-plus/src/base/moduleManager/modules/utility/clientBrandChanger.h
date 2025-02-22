#pragma once
#include <jni/jni.h>

#include "moduleManager/moduleBase.h"
#include "java/javahook.h"
#include "sdk/strayCache.h"

#include "util/logger.h"

class ClientBrandChanger : public ModuleBase
{
public:
	void Update() override;
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return settings::CBC_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	static void onGetClientModName(JNIEnv* env, bool* cancel);
	static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

private:
	std::string Name = "Client Brand Changer";
	std::string Category = "Utility";
};