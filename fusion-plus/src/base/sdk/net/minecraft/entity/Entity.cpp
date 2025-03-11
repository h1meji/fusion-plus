#include "Entity.h"
#include "java/java.h"
#include "sdk/java/lang/String.h"
#include "sdk/strayCache.h"

#include "util/logger/logger.h"
#include <sdk/sdk.h>

CEntity::CEntity()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::entity_class;
}

CEntity::CEntity(jobject instance) : CEntity()
{
	this->Instance = instance;
}

jclass CEntity::GetClass()
{
	return this->Class;
}

jobject CEntity::GetInstance()
{
	return this->Instance;
}

std::string CEntity::GetName()
{
	String str = String(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::entity_getName));
	return str.ToString();
}

Vector3 CEntity::GetPos()
{
	if ((Java::Version == MinecraftVersion::LUNAR_1_7_10 || Java::Version == MinecraftVersion::VANILLA_1_7_10 || Java::Version == MinecraftVersion::FORGE_1_7_10) && this->GetName() == SDK::Minecraft->thePlayer->GetName())
	{
		// In 1.7.10, the entity position is the "eye" position, so we need to subtract the eye height to get the actual position. But only for the main player entity
		return Vector3{
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posX),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posY) - (this->GetHeight() * 0.85f),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posZ)
		};
	}
	else
	{
		return Vector3{
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posX),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posY),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_posZ)
		};
	}
}

Vector3 CEntity::GetEyePos()
{
	Vector3 pos = GetPos();
	return Vector3{
		pos.x,
		(float)(double)(pos.y + (this->GetHeight() * 0.85f)),
		pos.z
	};
}

Vector3 CEntity::GetLastTickPos()
{
	if ((Java::Version == MinecraftVersion::LUNAR_1_7_10 || Java::Version == MinecraftVersion::VANILLA_1_7_10 || Java::Version == MinecraftVersion::FORGE_1_7_10) && this->GetName() == SDK::Minecraft->thePlayer->GetName())
	{
		// In 1.7.10, the entity position is the "eye" position, so we need to subtract the eye height to get the actual position. But only for the main player entity
		return Vector3{
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosX),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosY) - (this->GetHeight() * 0.85f),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosZ)
		};
	}
	else
	{
		return Vector3{
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosX),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosY),
			(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_lastTickPosZ)
		};
	}
}

Vector3 CEntity::GetMotion()
{
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_motionX),
		(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_motionY),
		(float)(double)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::entity_motionZ)
	};
}

bool CEntity::IsSneaking()
{
	return Java::Env->CallBooleanMethod(this->GetInstance(), StrayCache::entity_isSneaking);
}

bool CEntity::IsSprinting()
{
	return Java::Env->CallBooleanMethod(this->GetInstance(), StrayCache::entity_isSprinting);
}

void CEntity::SetSprinting(bool sprinting)
{
	Java::Env->CallVoidMethod(this->GetInstance(), StrayCache::entity_setSprinting, sprinting);
}

bool CEntity::IsInvisibleToPlayer(jobject player)
{
	return Java::Env->CallBooleanMethod(this->GetInstance(), StrayCache::entity_isInvisibleToPlayer, player);
}

float CEntity::GetHeight()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_height);
}

float CEntity::GetWidth()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_width);
}

float CEntity::GetDistanceWalkedModified()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_distanceWalkedModified);
}

float CEntity::GetPrevDistanceWalkedModified()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_prevDistanceWalkedModified);
}

float CEntity::GetRotationYaw()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_rotationYaw);
}

float CEntity::GetRotationPitch()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_rotationPitch);
}

float CEntity::GetPrevRotationYaw()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_prevRotationYaw);
}

float CEntity::GetPrevRotationPitch()
{
	return Java::Env->GetFloatField(this->GetInstance(), StrayCache::entity_prevRotationPitch);
}

Vector2 CEntity::GetAngles()
{
	return Vector2(CEntity::GetRotationYaw(), CEntity::GetRotationPitch());
}

Vector2 CEntity::GetPrevAngles()
{
	return Vector2(CEntity::GetPrevRotationYaw(), CEntity::GetPrevRotationPitch());
}

void CEntity::SetAngles(Vector2 angles) 
{
	Java::Env->SetFloatField(this->GetInstance(), StrayCache::entity_rotationYaw, angles.x);
	Java::Env->SetFloatField(this->GetInstance(), StrayCache::entity_rotationPitch, angles.y);
};

CAxisAlignedBB CEntity::GetBB()
{
	return CAxisAlignedBB(
		Java::Env->GetObjectField(this->GetInstance(), StrayCache::entity_boundingBox)
	);
}

void CEntity::SetBB(BoundingBox bb)
{
	this->GetBB().SetBoundingBox(bb);
}

int CEntity::GetHurtResistantTime()
{
	return Java::Env->GetIntField(this->GetInstance(), StrayCache::entity_hurtResistantTime);
}
