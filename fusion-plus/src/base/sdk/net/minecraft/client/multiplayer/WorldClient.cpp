#include "WorldClient.h"

#include "sdk/sdk.h"
#include "sdk/java/util/Set.h"
#include "java/java.h"
#include "util/logger/logger.h"

CWorldClient::CWorldClient()
{
	this->clazz = StrayCache::worldClient_class;
}

jclass CWorldClient::GetClass()
{
	return this->clazz;
}

jobject CWorldClient::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_theWorld);
}

std::vector<CEntity> CWorldClient::GetEntityList()
{
	std::vector<CEntity> finalList;

	jobject playerEntitiesList = Java::env->GetObjectField(this->GetInstance(), StrayCache::worldClient_entityList);

	jobjectArray playerEntities = Set::Set(playerEntitiesList).toArray();
	int size = Java::env->GetArrayLength(playerEntities);

	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntity player = CEntity::CEntity(obj_player);
		if (player.GetName().compare(SDK::minecraft->thePlayer->GetName()))
			finalList.push_back(player);
	}

	return finalList;
}