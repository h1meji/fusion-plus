#include "Minecraft.h"
#include "java/java.h"
#include "util/logger.h"

#include "sdk/net/minecraft/entity/EntityLivingBase.h"

CMinecraft::CMinecraft()
{
	this->Class = StrayCache::minecraft_class;

	this->MethodIDs["getMinecraft"] = StrayCache::minecraft_getMinecraft;
	this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);
	Logger::Log("Got Minecraft instance");

	this->FieldIDs["thePlayer"] = StrayCache::minecraft_thePlayer;
	this->thePlayer = new CEntityPlayerSP();
	Logger::Log("Got Player instance");

	this->FieldIDs["playerController"] = StrayCache::minecraft_playerController;
	this->playerController = new CPlayerControllerMP();
	Logger::Log("Got PlayerController instance");

	this->FieldIDs["theWorld"] = StrayCache::minecraft_theWorld;
	this->theWorld = new CWorldClient();
	Logger::Log("Got World instance");

	this->activeRenderInfo = new CActiveRenderInfo();
	Logger::Log("Got ActiveRenderInfo instance");

	this->FieldIDs["renderManager"] = StrayCache::minecraft_renderManager;
	this->renderManager = new CRenderManager();
	Logger::Log("Got RenderManager instance");

	this->FieldIDs["timer"] = StrayCache::minecraft_timer;
	this->timer = new CTimer();
	Logger::Log("Got Timer instance");

	this->FieldIDs["gameSettings"] = StrayCache::minecraft_gameSettings;
	this->gameSettings = new CGameSettings();
	Logger::Log("Got GameSettings instance");

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

std::string GetClassName(jobject obj)
{
	jclass objClass = Java::Env->GetObjectClass(obj);
	jmethodID objMethod = Java::Env->GetMethodID(objClass, "getClass", "()Ljava/lang/Class;");
	jobject objClassObj = Java::Env->CallObjectMethod(obj, objMethod);
	jmethodID objClassNameMethod = Java::Env->GetMethodID(Java::Env->GetObjectClass(objClassObj), "getName", "()Ljava/lang/String;");
	jstring objClassName = (jstring)Java::Env->CallObjectMethod(objClassObj, objClassNameMethod);
	const char* objClassNameChars = Java::Env->GetStringUTFChars(objClassName, NULL);
	std::string objClassNameStr = objClassNameChars;
	Java::Env->ReleaseStringUTFChars(objClassName, objClassNameChars);
	return objClassNameStr;
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL)
	{
		return true;
	}
	return false;
}

bool CMinecraft::IsInInventory()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL)
	{
		if (GetClassName(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"])) == StrayCache::inventory_class_name)
			return true;
	}
	return false;
}

bool CMinecraft::IsInChest()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL)
	{
		if (GetClassName(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"])) == StrayCache::chest_gui_class_name)
			return true;
	}
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

CGuiChest* CMinecraft::GetGuiChest()
{
	return new CGuiChest(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]));
}