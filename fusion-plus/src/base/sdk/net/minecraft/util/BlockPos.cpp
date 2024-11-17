#include "BlockPos.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CBlockPos::CBlockPos(int x, int y, int z)
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::blockPos_class;
	this->Instance = Java::Env->NewObject(this->Class, StrayCache::blockPos_constructorInt, x, y, z);
}

CBlockPos::CBlockPos(float x, float y, float z)
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::blockPos_class;
	this->Instance = Java::Env->NewObject(this->Class, StrayCache::blockPos_constructorFloat, x, y, z);
}

jclass CBlockPos::GetClass()
{
	return this->Class;
}

jobject CBlockPos::GetInstance()
{
	return this->Instance;
}