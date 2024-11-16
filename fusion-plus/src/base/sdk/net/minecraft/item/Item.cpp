#include "Item.h"
#include "sdk/strayCache.h"

CItem::CItem()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::item_class;
}

CItem::CItem(jobject instance) : CItem()
{
	this->Instance = instance;
}

jclass CItem::GetClass()
{
	return this->Class;
}

jobject CItem::GetInstance()
{
	return this->Instance;
}

std::string CItem::GetUnlocalizedName()
{
	jstring jstr = (jstring)Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::item_getUnlocalizedName);
	return Java::Env->GetStringUTFChars(jstr, 0);
}
