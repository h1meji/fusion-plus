#pragma once

#include "sdk/java/IClass.h"

#include "sdk/net/minecraft/item/ItemStack.h"
#include "sdk/net/minecraft/entity/player/EntityPlayer.h"

struct CPlayerControllerMP : IClass
{
	CPlayerControllerMP();
	CPlayerControllerMP(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CItemStack WindowClick(int windowId, int slotId, int mouseButton, int mode, CEntityPlayer* player);
};