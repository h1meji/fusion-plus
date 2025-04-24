#pragma once

#include "sdk/java/IClass.h"
#include "sdk/net/minecraft/item/ItemStack.h"

struct IInventory : IClass
{
	IInventory(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	int GetSizeInventory();
	CItemStack GetStackInSlot(int slot);
};