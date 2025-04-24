#include "IBlockState.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CIBlockState::CIBlockState()
{
	if (!StrayCache::initialized) StrayCache::Init();
	this->clazz = StrayCache::iBlockState_class;
}

CIBlockState::CIBlockState(jobject instance) : CIBlockState()
{
	this->instance = instance;
}

jclass CIBlockState::GetClass()
{
	return this->clazz;
}

jobject CIBlockState::GetInstance()
{
	return this->instance;
}

CBlock CIBlockState::GetBlock()
{
	return CBlock(Java::env->CallObjectMethod(this->GetInstance(), StrayCache::iBlockState_getBlock));
}
