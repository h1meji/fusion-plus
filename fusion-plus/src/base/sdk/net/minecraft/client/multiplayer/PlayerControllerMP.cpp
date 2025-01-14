#include "PlayerControllerMP.h"

#include "sdk/strayCache.h"
#include <sdk/sdk.h>

CPlayerControllerMP::CPlayerControllerMP()
{
	this->Class = StrayCache::playerControllerMP_class;
}

CPlayerControllerMP::CPlayerControllerMP(jobject instance) : CPlayerControllerMP()
{
	this->Instance = instance;
}

jobject CPlayerControllerMP::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["playerController"]);
}

jclass CPlayerControllerMP::GetClass()
{
	return this->Class;
}

CItemStack CPlayerControllerMP::WindowClick(int windowId, int slotId, int mouseButton, int mode, CEntityPlayer* player)
{
	jobject itemStack = Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::playerControllerMP_windowClick, windowId, slotId, mouseButton, mode, player->GetInstance());

	if (!itemStack) {
		return CItemStack(nullptr);
	}

	return CItemStack(itemStack);
}
