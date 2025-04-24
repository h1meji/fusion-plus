#include "MovingObjectPosition.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CMovingObjectPosition::CMovingObjectPosition()
{
	this->clazz = StrayCache::movingObjectPosition_class;
}

CMovingObjectPosition::CMovingObjectPosition(jobject instance) : CMovingObjectPosition()
{
	this->instance = instance;
}

jclass CMovingObjectPosition::GetClass()
{
	return this->clazz;
}

jobject CMovingObjectPosition::GetInstance()
{
	return this->instance;
}

CVec3 CMovingObjectPosition::GetBlockPosition()
{
	return CVec3(Java::env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_hitVec));
}

bool CMovingObjectPosition::IsTypeOfBlock()
{
	jobject typeOfHit = Java::env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = Java::env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;
	jfieldID block = StrayCache::GetMovingBlockPositionBLOCK(movingObjectType);
	if (!block) return false;
	jobject object = Java::env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return Java::env->IsSameObject(object, typeOfHit);
}

CEntity CMovingObjectPosition::GetEntityHit()
{
	jobject typeOfHit = Java::env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return CEntity();

	return CEntity(Java::env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_entityHit));
}
