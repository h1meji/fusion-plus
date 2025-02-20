#pragma once

#include "sdk/java/IClass.h"
#include "util/math/geometry.h"
#include "sdk/net/minecraft/util/AxisAlignedBB.h"

struct CEntity : IClass
{
	CEntity();

	CEntity(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	std::string GetName();

	Vector3 GetPos();
	Vector3 GetEyePos();
	Vector3 GetLastTickPos();

	Vector3 GetMotion();

	bool IsSneaking();
	bool IsSprinting();

	void SetSprinting(bool sprinting);

	bool IsInvisibleToPlayer(jobject player);

	float GetHeight();
	float GetWidth();

	float GetDistanceWalkedModified();
	float GetPrevDistanceWalkedModified();

	float GetRotationYaw();
	float GetRotationPitch();

	float GetPrevRotationYaw();
	float GetPrevRotationPitch();

	Vector2 GetAngles();
	Vector2 GetPrevAngles();

	void SetAngles(Vector2 angles);

	CAxisAlignedBB GetBB();
	void SetBB(BoundingBox bb);

	int GetHurtResistantTime();
};