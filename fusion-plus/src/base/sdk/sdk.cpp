#include "sdk.h"

#include "util/logger.h"
#include "java/java.h"
#include "strayCache.h"

void SDK::Init()
{
	StrayCache::Init();
	LOG_INFO("Stray cache initialized");
	SDK::minecraft = new CMinecraft();
	LOG_INFO("Initialized Minecraft");
}

void SDK::Shutdown()
{
	StrayCache::DeleteRefs();
}
