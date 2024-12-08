#include "EntityPlayerSP.h"
#include "sdk/sdk.h"
#include "java/java.h"

#include "util/logger.h"

CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
	this->Class = StrayCache::entityPlayerSP_class;
}

jclass CEntityPlayerSP::GetClass()
{
	return this->Class;
}

jobject CEntityPlayerSP::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
}
