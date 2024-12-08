#include "EntityPlayer.h"

#include "java/java.h"

CEntityPlayer::CEntityPlayer()
{
	this->Class = StrayCache::entityPlayer_class;
	this->FieldIDs["inventory"] = StrayCache::entityPlayer_inventory;
}

CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
{
	this->Instance = instance;
}


jclass CEntityPlayer::GetClass()
{
	return this->Class;
}

jobject CEntityPlayer::GetInstance()
{
	return this->Instance;
}

CInventoryPlayer CEntityPlayer::GetInventory()
{
	return CInventoryPlayer(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["inventory"]));
}
