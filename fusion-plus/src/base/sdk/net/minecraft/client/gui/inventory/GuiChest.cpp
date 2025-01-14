#include "GuiChest.h"

#include "java/java.h"
#include "sdk/strayCache.h"

#include "util/logger.h"

CGuiChest::CGuiChest(jobject instance) : CGuiContainer(instance)
{
	this->Instance = instance;
	this->Class = StrayCache::guiChest_class;
}

jclass CGuiChest::GetClass()
{
	return this->Class;
}

jobject CGuiChest::GetInstance()
{
	return this->Instance;
}

IInventory* CGuiChest::GetLowerChestInventory()
{
	jobject lowerChestInventory = Java::Env->GetObjectField(this->GetInstance(), StrayCache::guiChest_lowerChestInventory);
	return new IInventory(lowerChestInventory);
}

IInventory* CGuiChest::GetUpperChestInventory()
{
	jobject upperChestInventory = Java::Env->GetObjectField(this->GetInstance(), StrayCache::guiChest_upperChestInventory);
	return new IInventory(upperChestInventory);
}

int CGuiChest::GetInventoryRows()
{
	return Java::Env->GetIntField(this->GetInstance(), StrayCache::guiChest_inventoryRows);
}