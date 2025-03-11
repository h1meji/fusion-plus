#include "sdk.h"
#include "util/logger/logger.h"
#include "java/java.h"
#include "strayCache.h"

void SDK::Init()
{
	StrayCache::Initialize();
	Logger::Log("Stray cache initialized");
	SDK::Minecraft = new CMinecraft();
	Logger::Log("Initialized Minecraft");
}
