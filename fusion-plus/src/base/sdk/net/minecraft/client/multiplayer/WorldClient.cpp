#include "WorldClient.h"

#include "sdk/sdk.h"
#include "java/java.h"
#include "util/logger/logger.h"
#include "sdk/java/util/Set.h"

CWorldClient::CWorldClient()
{
	this->Class = StrayCache::worldClient_class;
	this->EntityPlayer = StrayCache::entityPlayer_class;
	this->FieldIDs["entityList"] = StrayCache::worldClient_entityList;
}

jclass CWorldClient::GetClass()
{
	return this->Class;
}

jobject CWorldClient::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["theWorld"]);
}

std::vector<CEntity> CWorldClient::GetEntityList()
{
	std::vector<CEntity> finalList;
	jfieldID targetField = this->FieldIDs["entityList"];

	jobject playerEntitiesList = Java::Env->GetObjectField(this->GetInstance(), targetField);

	jobjectArray playerEntities = Set::Set(playerEntitiesList).toArray();
	int size = Java::Env->GetArrayLength(playerEntities);

	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::Env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntity player = CEntity::CEntity(obj_player);
		if (player.GetName().compare(SDK::Minecraft->thePlayer->GetName()))
			finalList.push_back(player);
	}
	return finalList;
}