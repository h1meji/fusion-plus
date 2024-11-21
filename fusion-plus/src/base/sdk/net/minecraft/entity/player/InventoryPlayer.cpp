#include "InventoryPlayer.h"

#include "sdk/strayCache.h"

CInventoryPlayer::CInventoryPlayer()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::inventoryPlayer_class;
}

CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
{
	this->Instance = instance;
}

jclass CInventoryPlayer::GetClass()
{
	return this->Class;
}

jobject CInventoryPlayer::GetInstance()
{
	return this->Instance;
}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}

std::vector<CItemStack> CInventoryPlayer::GetMainInventory()
{
	jobject mainInventory = Java::Env->GetObjectField(this->GetInstance(), StrayCache::inventoryPlayer_mainInventory);
	jobjectArray mainInventoryArray = (jobjectArray)mainInventory;

	std::vector<CItemStack> mainInventoryVector;

	for (int i = 0; i < Java::Env->GetArrayLength(mainInventoryArray); i++)
	{
		jobject mainItemStack = Java::Env->GetObjectArrayElement(mainInventoryArray, i);
		mainInventoryVector.push_back(CItemStack(mainItemStack));
	}

	return mainInventoryVector;
}

std::vector<CItemStack> CInventoryPlayer::GetArmorInventory()
{
	jobject armorInventory = Java::Env->GetObjectField(this->GetInstance(), StrayCache::inventoryPlayer_armorInventory);
	jobjectArray armorInventoryArray = (jobjectArray)armorInventory;

	std::vector<CItemStack> armorInventoryVector;

	for (int i = 0; i < Java::Env->GetArrayLength(armorInventoryArray); i++)
	{
		jobject armorItemStack = Java::Env->GetObjectArrayElement(armorInventoryArray, i);
		armorInventoryVector.push_back(CItemStack(armorItemStack));
	}

	return armorInventoryVector;
}
