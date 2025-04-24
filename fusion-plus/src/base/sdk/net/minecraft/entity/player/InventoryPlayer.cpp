#include "InventoryPlayer.h"

#include "sdk/strayCache.h"

CInventoryPlayer::CInventoryPlayer()
{
	this->clazz = StrayCache::inventoryPlayer_class;
}

CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
{
	this->instance = instance;
}

jclass CInventoryPlayer::GetClass()
{
	return this->clazz;
}

jobject CInventoryPlayer::GetInstance()
{
	return this->instance;
}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::env->CallObjectMethod(this->GetInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}

int CInventoryPlayer::GetCurrentItemIndex()
{
	return Java::env->GetIntField(this->GetInstance(), StrayCache::inventoryPlayer_currentItem);
}

void CInventoryPlayer::SetCurrentItemIndex(int index)
{
	Java::env->SetIntField(this->GetInstance(), StrayCache::inventoryPlayer_currentItem, index);
}

std::vector<CItemStack> CInventoryPlayer::GetMainInventory()
{
	jobject mainInventory = Java::env->GetObjectField(this->GetInstance(), StrayCache::inventoryPlayer_mainInventory);
	jobjectArray mainInventoryArray = (jobjectArray)mainInventory;

	std::vector<CItemStack> mainInventoryVector;

	for (int i = 0; i < Java::env->GetArrayLength(mainInventoryArray); i++)
	{
		jobject mainItemStack = Java::env->GetObjectArrayElement(mainInventoryArray, i);
		mainInventoryVector.push_back(CItemStack(mainItemStack));
	}

	return mainInventoryVector;
}

std::vector<CItemStack> CInventoryPlayer::GetArmorInventory()
{
	jobject armorInventory = Java::env->GetObjectField(this->GetInstance(), StrayCache::inventoryPlayer_armorInventory);
	jobjectArray armorInventoryArray = (jobjectArray)armorInventory;

	std::vector<CItemStack> armorInventoryVector;

	for (int i = 0; i < Java::env->GetArrayLength(armorInventoryArray); i++)
	{
		jobject armorItemStack = Java::env->GetObjectArrayElement(armorInventoryArray, i);
		armorInventoryVector.push_back(CItemStack(armorItemStack));
	}

	return armorInventoryVector;
}
