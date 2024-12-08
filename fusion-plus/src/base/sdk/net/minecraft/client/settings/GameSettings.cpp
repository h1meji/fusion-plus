#include "GameSettings.h"
#include "sdk/sdk.h"
#include "java/java.h"

CGameSettings::CGameSettings()
{
	this->Class = StrayCache::gameSettings_class;
	this->FieldIDs["thirdPersonView"] = StrayCache::gameSettings_thirdPersonView;
	this->FieldIDs["fovSetting"] = StrayCache::gameSettings_fovSetting;

	this->FieldIDs["keyBindFullscreen"] = StrayCache::gameSettings_keyBindFullscreen;
	this->MethodIDs["setOptionKeyBinding"] = StrayCache::gameSettings_setOptionKeyBinding;
}

jclass CGameSettings::GetClass()
{
	return this->Class;
}

jobject CGameSettings::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["gameSettings"]);
}

float CGameSettings::GetFOV()
{
	return Java::Env->GetFloatField(GetInstance(), this->FieldIDs["fovSetting"]);
}

void CGameSettings::SetFullscreenKeyToNull()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 87);
}


int CGameSettings::GetThirdPersonView()
{
	return Java::Env->GetIntField(GetInstance(), this->FieldIDs["thirdPersonView"]);
}

