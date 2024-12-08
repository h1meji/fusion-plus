#include "Timer.h"

#include "java/java.h"
#include "sdk/sdk.h"

CTimer::CTimer()
{
	this->Class = StrayCache::timer_class;
	this->FieldIDs["renderPartialTicks"] = StrayCache::timer_renderPartialTicks;
}

float CTimer::GetRenderPartialTicks()
{
	return Java::Env->GetFloatField(this->GetInstance(), this->FieldIDs["renderPartialTicks"]);
}

jclass CTimer::GetClass()
{
	return this->Class;
}

jobject CTimer::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["timer"]);
}