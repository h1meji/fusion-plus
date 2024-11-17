#include "IBlockState.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CIBlockState::CIBlockState()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::iBlockState_class;
}

CIBlockState::CIBlockState(jobject instance) : CIBlockState()
{
	this->Instance = instance;
}

jclass CIBlockState::GetClass()
{
	return this->Class;
}

jobject CIBlockState::GetInstance()
{
	return this->Instance;
}

CBlock CIBlockState::GetBlock()
{
	return CBlock(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::iBlockState_getBlock));
}
