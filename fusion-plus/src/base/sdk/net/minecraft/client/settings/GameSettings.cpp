#include "GameSettings.h"

#include "sdk/sdk.h"
#include "java/java.h"

CGameSettings::CGameSettings()
{
	this->clazz = StrayCache::gameSettings_class;
}

jclass CGameSettings::GetClass()
{
	return this->clazz;
}

jobject CGameSettings::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_gameSettings);
}

float CGameSettings::GetFOV()
{
	return Java::env->GetFloatField(GetInstance(), StrayCache::gameSettings_fovSetting);
}

void CGameSettings::SetFullscreenKeyToNull()
{
	jobject instance = this->GetInstance();
	Java::env->CallVoidMethod(instance, StrayCache::gameSettings_setOptionKeyBinding, Java::env->GetObjectField(instance, StrayCache::gameSettings_keyBindFullscreen), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	jobject instance = this->GetInstance();
	Java::env->CallVoidMethod(instance, StrayCache::gameSettings_setOptionKeyBinding, Java::env->GetObjectField(instance, StrayCache::gameSettings_keyBindFullscreen), 87);
}


int CGameSettings::GetThirdPersonView()
{
	return Java::env->GetIntField(GetInstance(), StrayCache::gameSettings_thirdPersonView);
}

