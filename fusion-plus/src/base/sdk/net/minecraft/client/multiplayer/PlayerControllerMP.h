#pragma once

#include <memory>

#include "sdk/java/IClass.h"
#include "sdk/net/minecraft/item/ItemStack.h"
#include "sdk/net/minecraft/client/entity/EntityPlayerSP.h"

struct CPlayerControllerMP : IClass
{
	CPlayerControllerMP();
	CPlayerControllerMP(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CItemStack WindowClick(int windowId, int slotId, int mouseButton, int mode, std::unique_ptr<CEntityPlayerSP>& player);
};