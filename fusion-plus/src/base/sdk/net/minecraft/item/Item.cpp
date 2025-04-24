#include "Item.h"

#include "sdk/strayCache.h"

CItem::CItem()
{
	this->clazz = StrayCache::item_class;
}

CItem::CItem(jobject instance) : CItem()
{
	this->instance = instance;
}

jclass CItem::GetClass()
{
	return this->clazz;
}

jobject CItem::GetInstance()
{
	return this->instance;
}

std::string CItem::GetUnlocalizedName()
{
	jstring jstr = (jstring)Java::env->CallObjectMethod(this->GetInstance(), StrayCache::item_getUnlocalizedName);
	return Java::env->GetStringUTFChars(jstr, 0);
}

int CItem::GetID()
{
	return Java::env->CallStaticIntMethod(StrayCache::item_class, StrayCache::item_getIdFromItem, this->GetInstance());
}

int CItem::GetStackLimit()
{
	return Java::env->CallIntMethod(this->GetInstance(), StrayCache::item_getItemStackLimit);
}
