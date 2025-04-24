#pragma once

#include "InventoryPlayer.h"
#include "sdk/net/minecraft/entity/EntityLivingBase.h"

struct CEntityPlayer : CEntityLivingBase
{
	CEntityPlayer();
	CEntityPlayer(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CInventoryPlayer GetInventory();
	int GetPing();
};

