#pragma once

#include "sdk/net/minecraft/inventory/IInventory.h"
#include "sdk/net/minecraft/client/gui/inventory/GuiContainer.h"

struct CGuiChest : CGuiContainer
{
	CGuiChest(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	IInventory* GetLowerChestInventory();
	IInventory* GetUpperChestInventory();

	int GetInventoryRows();
};