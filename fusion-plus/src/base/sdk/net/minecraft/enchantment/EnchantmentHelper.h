#pragma once

#include <map>

#include "sdk/net/minecraft/item/ItemStack.h"

struct CEnchantmentHelper : IClass
{
	CEnchantmentHelper();

	jclass GetClass();
	jobject GetInstance();

	std::map<int, int> GetEnchantments(CItemStack itemStack);
};