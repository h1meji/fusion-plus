#include "GuiChest.h"

#include "java/java.h"
#include "sdk/strayCache.h"
#include "util/logger/logger.h"

CGuiChest::CGuiChest(jobject instance) : CGuiContainer(instance)
{
	this->instance = instance;
	this->clazz = StrayCache::guiChest_class;
}

jclass CGuiChest::GetClass()
{
	return this->clazz;
}

jobject CGuiChest::GetInstance()
{
	return this->instance;
}

IInventory* CGuiChest::GetLowerChestInventory()
{
	jobject lowerChestInventory = Java::env->GetObjectField(this->GetInstance(), StrayCache::guiChest_lowerChestInventory);
	return new IInventory(lowerChestInventory);
}

IInventory* CGuiChest::GetUpperChestInventory()
{
	jobject upperChestInventory = Java::env->GetObjectField(this->GetInstance(), StrayCache::guiChest_upperChestInventory);
	return new IInventory(upperChestInventory);
}

int CGuiChest::GetInventoryRows()
{
	return Java::env->GetIntField(this->GetInstance(), StrayCache::guiChest_inventoryRows);
}