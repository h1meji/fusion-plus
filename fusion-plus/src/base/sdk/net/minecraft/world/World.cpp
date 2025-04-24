#include "World.h"

#include "java/java.h"
#include "sdk/sdk.h"
#include "sdk/java/util/List.h"
#include "sdk/net/minecraft/util/Vec3.h"
#include "sdk/net/minecraft/util/MovingObjectPosition.h"
#include "util/logger.h"

CWorld::CWorld() 
{
	this->clazz = StrayCache::world_class;
}

jclass CWorld::GetClass()
{
	return this->clazz;
}

jobject CWorld::GetInstance()
{
	return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_theWorld);
}

std::vector<CEntityPlayer> CWorld::GetPlayerList()
{
	std::vector<CEntityPlayer> finalList;
	jobject playerEntitiesList = Java::env->GetObjectField(this->GetInstance(), StrayCache::world_playerEntities);
	jobjectArray playerEntities = List::List(playerEntitiesList).toArray();
	int size = Java::env->GetArrayLength(playerEntities);
	
	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntityPlayer player =  CEntityPlayer::CEntityPlayer(obj_player);
		finalList.push_back(player);
	}

	Java::env->DeleteLocalRef(playerEntitiesList);
	Java::env->DeleteLocalRef(playerEntities);

	return finalList;
}

bool CWorld::RayTraceBlocks(Vector3 from, Vector3 to, Vector3& result, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock)
{
	// SPECIAL CASE
	jclass cls;
	Java::AssignClass(StrayCache::vec3_class_name, cls);

	jmethodID init = Java::env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = Java::env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = Java::env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	jobject movingObjPos_j = Java::env->CallObjectMethod(
		this->GetInstance(),
		StrayCache::world_rayTraceBlocks,
		j_from,
		j_to,
		stopOnLiquid,
		ignoreBlockWithoutBoundingBox,
		returnLastUncollidableBlock
	);

	if (movingObjPos_j == nullptr)
	{
		Java::env->DeleteLocalRef(j_to);
		Java::env->DeleteLocalRef(j_from);
		Java::env->DeleteLocalRef(cls);
		return false;
	}

	CMovingObjectPosition movingObjPos = CMovingObjectPosition(movingObjPos_j);
	CVec3 a = movingObjPos.GetBlockPosition();
	result = a.GetNativeVector3();
	Java::env->DeleteLocalRef(j_to);
	Java::env->DeleteLocalRef(j_from);
	Java::env->DeleteLocalRef(cls);
	return true;
}

CBlock CWorld::GetBlock(int x, int y, int z)
{
	if (Java::version == MinecraftVersion::LUNAR_1_8_9 || Java::version == MinecraftVersion::VANILLA_1_8_9 || Java::version == MinecraftVersion::FORGE_1_8_9)
	{
		CBlockPos pos = CBlockPos(x, y, z);
		CIBlockState state = CIBlockState(Java::env->CallObjectMethod(this->GetInstance(), StrayCache::world_getBlockState, pos.GetInstance()));
		return state.GetBlock();
	}
	else
	{
		return CBlock(Java::env->CallObjectMethod(this->GetInstance(), StrayCache::world_getBlock, x, y, z));
	}
}
