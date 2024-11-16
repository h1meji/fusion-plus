#pragma once
#include "sdk/java/IClass.h"
#include "Vec3.h"
#include <sdk/net/minecraft/entity/Entity.h>

struct CMovingObjectPosition : IClass
{
	CMovingObjectPosition();
	CMovingObjectPosition(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CVec3 GetBlockPosition();
	bool IsTypeOfBlock();
	CEntity GetEntityHit();
};

