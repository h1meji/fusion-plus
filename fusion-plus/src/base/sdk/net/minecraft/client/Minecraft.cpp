#include "Minecraft.h"

#include "util/logger.h"
#include "java/java.h"
#include "sdk/net/minecraft/entity/EntityLivingBase.h"
#include "ClientBrandRetriever.h"

CMinecraft::CMinecraft()
{
	this->clazz = StrayCache::minecraft_class;

	this->instance = Java::env->CallStaticObjectMethod(this->GetClass(), StrayCache::minecraft_getMinecraft);
	LOG_INFO("Created Minecraft instance");

	this->thePlayer = std::make_unique<CEntityPlayerSP>();
	LOG_INFO("Created Player instance");

	this->playerController = std::make_unique<CPlayerControllerMP>();
	LOG_INFO("Created PlayerController instance");

	this->theWorld = std::make_unique<CWorldClient>();
	LOG_INFO("Created World instance");

	this->activeRenderInfo = std::make_unique<CActiveRenderInfo>();
	LOG_INFO("Created ActiveRenderInfo instance");

	this->renderManager = std::make_unique<CRenderManager>();
	LOG_INFO("Created RenderManager instance");

	this->timer = std::make_unique<CTimer>();
	LOG_INFO("Created Timer instance");

	this->gameSettings = std::make_unique<CGameSettings>();
	LOG_INFO("Created GameSettings instance");

	this->enchantmentHelper = std::make_unique<CEnchantmentHelper>();
	LOG_INFO("Created EnchantmentHelper");

	this->originalClientBrand = CClientBrandRetriever::GetClientModName();
	LOG_INFO("Created Original Client Brand: %s", this->originalClientBrand.c_str());
}

jclass CMinecraft::GetClass()
{
	return this->clazz;
}

jobject CMinecraft::GetInstance()
{
	return this->instance;
}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_renderViewEntity));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen) != NULL)
	{
		return true;
	}
	return false;
}

bool CMinecraft::IsInInventory()
{
	if (Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen) != NULL)
	{
		if (Java::GetClazzName(Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen)) == StrayCache::inventory_class_name)
			return true;
	}
	return false;
}

bool CMinecraft::IsInChest()
{
	if (Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen) != NULL)
	{
		if (Java::GetClazzName(Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen)) == StrayCache::chest_gui_class_name)
			return true;
	}
	return false;
}

void CMinecraft::ClickMouse()
{
	Java::env->CallVoidMethod(this->GetInstance(), StrayCache::minecraft_clickMouse);
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::env->GetObjectField(this->instance, StrayCache::minecraft_objectMouseOver));
}

int CMinecraft::GetFps()
{
	return Java::env->GetStaticIntField(this->GetClass(), StrayCache::minecraft_debugFPS);
}


CGuiChest* CMinecraft::GetGuiChest()
{
	return new CGuiChest(Java::env->GetObjectField(this->GetInstance(), StrayCache::minecraft_currentScreen));
}