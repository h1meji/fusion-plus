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

int CItemStack::GetMetadata()
{
	int meta = Java::Env->CallIntMethod(this->GetInstance(), StrayCache::itemStack_getMetadata);
	int max_damage = Java::Env->CallIntMethod(this->GetInstance(), StrayCache::itemStack_getMaxDamage);

	if (max_damage > 0 && meta > 0) return 0; // fix for items with durability (e.g. tools)
	return meta;
}