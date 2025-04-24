#include "IInventory.h"

#include "java/java.h"
#include "sdk/strayCache.h"
#include "util/logger/logger.h"
#include "Container.h"

IInventory::IInventory(jobject instance)
{
	this->instance = instance;
	this->clazz = nullptr;
}

jclass IInventory::GetClass()
{
	return this->clazz;
}

jobject IInventory::GetInstance()
{
	return this->instance;
}

int IInventory::GetSizeInventory()
{
	return Java::env->CallIntMethod(this->GetInstance(), StrayCache::iInventory_getSizeInventory);
}

CItemStack IInventory::GetStackInSlot(int slot)
{
	jobject stackInSlot = Java::env->CallObjectMethod(this->GetInstance(), StrayCache::iInventory_getStackInSlot, slot);
	return CItemStack(stackInSlot);
}
