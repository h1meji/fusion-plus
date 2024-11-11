#pragma once

#include "sdk/java/IClass.h"
#include "sdk/net/minecraft/item/ItemStack.h"

struct CInventoryPlayer : IClass
{
	CInventoryPlayer();
	CInventoryPlayer(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CItemStack GetCurrentItem();
};