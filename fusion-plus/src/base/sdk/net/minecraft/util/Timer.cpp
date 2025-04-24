#include "Timer.h"

#include "java/java.h"
#include "sdk/sdk.h"

CTimer::CTimer()
{
	this->clazz = StrayCache::timer_class;
}

float CTimer::GetRenderPartialTicks()
{
	return Java::env->GetFloatField(this->GetInstance(), StrayCache::timer_renderPartialTicks);
}

jclass CTimer::GetClass()
{
	return this->clazz;
}

jobject CTimer::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_timer);
}