#include "Minecraft.h"
#include "java/java.h"
#include "util/logger.h"

#include "sdk/net/minecraft/entity/EntityLivingBase.h"

CMinecraft::CMinecraft()
{
	this->Class = StrayCache::minecraft_class;

	this->MethodIDs["getMinecraft"] = StrayCache::minecraft_getMinecraft;
	this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

	this->FieldIDs["thePlayer"] = StrayCache::minecraft_thePlayer;
	this->thePlayer = new CEntityPlayerSP();

	this->FieldIDs["theWorld"] = StrayCache::minecraft_theWorld;
	this->theWorld = new CWorldClient();

	this->activeRenderInfo = new CActiveRenderInfo();

	this->FieldIDs["renderManager"] = StrayCache::minecraft_renderManager;
	this->renderManager = new CRenderManager();

	this->FieldIDs["timer"] = StrayCache::minecraft_timer;
	this->timer = new CTimer();

	this->FieldIDs["gameSettings"] = StrayCache::minecraft_gameSettings;
	this->gameSettings = new CGameSettings();

	this->MethodIDs["getRenderViewEntity"] = StrayCache::minecraft_getRenderViewEntity;
	this->FieldIDs["currentScreen"] = StrayCache::minecraft_currentScreen;

	this->FieldIDs["objectMouseOver"] = StrayCache::minecraft_objectMouseOver;

	// not used lol
	this->MethodIDs["clickMouse"] = StrayCache::minecraft_clickMouse;
}

jclass CMinecraft::GetClass()
{
	return this->Class;
}

jobject CMinecraft::GetInstance()
{
	return this->Instance;
}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getRenderViewEntity"]));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL) return true;
	return false;
}

void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->GetInstance(), this->MethodIDs["clickMouse"]);
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->Instance, this->FieldIDs["objectMouseOver"]));
}
