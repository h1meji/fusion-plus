#include "ItemStack.h"

#include "sdk/strayCache.h"

CItemStack::CItemStack()
{
	this->clazz = StrayCache::itemStack_class;
}

CItemStack::CItemStack(jobject instance) : CItemStack()
{
	this->instance = instance;
}

jclass CItemStack::GetClass()
{
	return this->clazz;
}

jobject CItemStack::GetInstance()
{
	return this->instance;
}

CItem CItemStack::GetItem()
{
	return CItem(Java::env->CallObjectMethod(this->GetInstance(), StrayCache::itemStack_getItem));
}

int CItemStack::GetMetadata()
{
	int meta = Java::env->CallIntMethod(this->GetInstance(), StrayCache::itemStack_getMetadata);
	int max_damage = Java::env->CallIntMethod(this->GetInstance(), StrayCache::itemStack_getMaxDamage);

	if (max_damage > 0 && meta > 0) return 0; // fix for items with durability (e.g. tools)
	return meta;
}

int CItemStack::GetStackSize()
{
	return Java::env->GetIntField(this->GetInstance(), StrayCache::itemStack_stackSize);
}
