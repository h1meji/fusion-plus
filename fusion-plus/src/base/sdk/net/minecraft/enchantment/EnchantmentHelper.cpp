#include "EnchantmentHelper.h"

#include "java/java.h"
#include "sdk/strayCache.h"
#include "sdk/java/util/Map.h"

CEnchantmentHelper::CEnchantmentHelper()
{
	this->clazz = StrayCache::enchantmentHelper_class;
}

jclass CEnchantmentHelper::GetClass()
{
	return this->clazz;
}

jobject CEnchantmentHelper::GetInstance()
{
	return nullptr;
}

std::map<int, int> CEnchantmentHelper::GetEnchantments(CItemStack itemStack)
{
	std::map<int, int> enchantments;

	jobject enchantmentsMap = Java::env->CallStaticObjectMethod(this->GetClass(), StrayCache::enchantmentHelper_getEnchantments, itemStack.GetInstance());
	if (enchantmentsMap == nullptr)
	{
		LOG_ERROR("Failed to get enchantments map");
		return enchantments;
	}

	Map<int, int> map(enchantmentsMap);
	enchantments = map.ToMap();

	return enchantments;
}
