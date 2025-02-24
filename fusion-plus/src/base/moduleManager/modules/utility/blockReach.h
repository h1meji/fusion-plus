#pragma once
#include <jni/jni.h>

#include "moduleManager/moduleBase.h"
#include "java/javahook.h"
#include "sdk/strayCache.h"

#include "util/logger.h"

class BlockReach : public ModuleBase
{
public:
	void Update() override {};
	void RenderUpdate() override {}

	void RenderMenu() override;

	bool IsEnabled() override { return settings::BR_Enabled; }
	std::string GetName() override { return Name; }
	std::string GetCategory() override { return Category; }

	static void onGetBlockReachDistance(JNIEnv* env, bool* cancel);
	static void getBlockReachDistance_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

private:
	std::string Name = "Block Reach";
	std::string Category = "Utility";
};