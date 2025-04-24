#include "PlayerControllerMP.h"

#include "sdk/sdk.h"
#include "sdk/strayCache.h"

CPlayerControllerMP::CPlayerControllerMP()
{
	this->clazz = StrayCache::playerControllerMP_class;
}

CPlayerControllerMP::CPlayerControllerMP(jobject instance) : CPlayerControllerMP()
{
	this->instance = instance;
}

jobject CPlayerControllerMP::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_playerController);
}

jclass CPlayerControllerMP::GetClass()
{
	return this->clazz;
}

CItemStack CPlayerControllerMP::WindowClick(int windowId, int slotId, int mouseButton, int mode, std::unique_ptr<CEntityPlayerSP>& player)
{
	jobject itemStack = Java::env->CallObjectMethod(this->GetInstance(), StrayCache::playerControllerMP_windowClick, windowId, slotId, mouseButton, mode, player->GetInstance());

	if (!itemStack)
	{
		return CItemStack(nullptr);
	}

	return CItemStack(itemStack);
}
