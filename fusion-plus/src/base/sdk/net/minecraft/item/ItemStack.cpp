#include "ItemStack.h"
#include "sdk/strayCache.h"

CItemStack::CItemStack()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::itemStack_class;
}

CItemStack::CItemStack(jobject instance) : CItemStack()
{
	this->Instance = instance;
}

jclass CItemStack::GetClass()
{
	return this->Class;
}

jobject CItemStack::GetInstance()
{
	return this->Instance;
}

CItem CItemStack::GetItem()
{
	return CItem(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::itemStack_getItem));
}