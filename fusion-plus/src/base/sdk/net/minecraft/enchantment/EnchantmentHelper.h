#pragma once

#include <map>

#include "sdk/net/minecraft/item/ItemStack.h"

struct CEnchantMentHelper : IClass
{
	CEnchantMentHelper();

	jclass GetClass();
	jobject GetInstance();

	std::map<int, int> GetEnchantments(CItemStack itemStack);
};