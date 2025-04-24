#include "EntityPlayerSP.h"

#include "sdk/sdk.h"
#include "java/java.h"
#include "util/logger.h"

CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
	this->clazz = StrayCache::entityPlayerSP_class;
}

jclass CEntityPlayerSP::GetClass()
{
	return this->clazz;
}

jobject CEntityPlayerSP::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_thePlayer);
}
