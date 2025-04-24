#include "BlockPos.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CBlockPos::CBlockPos(int x, int y, int z)
{
	this->clazz = StrayCache::blockPos_class;
	this->instance = Java::env->NewObject(this->clazz, StrayCache::blockPos_constructorInt, x, y, z);
}

CBlockPos::CBlockPos(double x, double y, double z)
{
	this->clazz = StrayCache::blockPos_class;
	this->instance = Java::env->NewObject(this->clazz, StrayCache::blockPos_constructorDouble, x, y, z);
}

jclass CBlockPos::GetClass()
{
	return this->clazz;
}

jobject CBlockPos::GetInstance()
{
	return this->instance;
}