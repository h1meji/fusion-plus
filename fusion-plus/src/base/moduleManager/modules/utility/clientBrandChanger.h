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

	std::string GetName() override { return m_name; }
	std::string GetCategory() override { return m_category; }
	int GetKey() override { return settings::CBC_Key; }

	bool IsEnabled() override { return settings::CBC_Enabled; }
	void SetEnabled(bool enabled) override { settings::CBC_Enabled = enabled; }
	void Toggle() override { settings::CBC_Enabled = !settings::CBC_Enabled; }

	static void OnGetClientModName(JNIEnv* env, bool* cancel);
	static void GetClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

private:
	std::string m_name = "Client Brand Changer";
	std::string m_category = "Utility";

	std::once_flag m_setOriginalClientBrandFlag;
};