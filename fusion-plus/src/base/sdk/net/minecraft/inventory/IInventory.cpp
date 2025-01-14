#include "IInventory.h"

#include "java/java.h"
#include "sdk/strayCache.h"

#include "util/logger.h"
#include "Container.h"

IInventory::IInventory(jobject instance)
{
	this->Instance = instance;
	this->Class = nullptr;
}

jclass IInventory::GetClass()
{
	return this->Class;
}

jobject IInventory::GetInstance()
{
	return this->Instance;
}

int IInventory::GetSizeInventory()
{
	return Java::Env->CallIntMethod(this->GetInstance(), StrayCache::iInventory_getSizeInventory);
}

CItemStack* IInventory::GetStackInSlot(int slot)
{
	jobject stackInSlot = Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::iInventory_getStackInSlot, slot);
	return new CItemStack(stackInSlot);
}
