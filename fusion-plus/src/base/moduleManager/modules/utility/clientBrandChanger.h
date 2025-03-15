#pragma once
#include <jni/jni.h>

#include "moduleManager/moduleBase.h"
#include "java/javahook.h"
#include "sdk/strayCache.h"

#include "util/logger/logger.h"

class ClientBrandChanger : public ModuleBase
{
public:
	void Update() override {};
	void RenderOverlay() override {};
	void RenderHud() override {};

	void RenderMenu() override;

	bool IsEnabled() override { return settings::CBC_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }
	int GetKey() override { return settings::CBC_Key; }

	void SetEnabled(bool enabled) override { settings::CBC_Enabled = enabled; }
	void Toggle() override { settings::CBC_Enabled = !settings::CBC_Enabled; }

	static void onGetClientModName(JNIEnv* env, bool* cancel);
	static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

private:
	std::string Name = "Client Brand Changer";
	std::string Category = "Utility";
};