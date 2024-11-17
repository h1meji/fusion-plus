#include "Block.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CBlock::CBlock()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::block_class;
}

CBlock::CBlock(jobject instance) : CBlock()
{
	this->Instance = instance;
}

jclass CBlock::GetClass()
{
	return this->Class;
}

jobject CBlock::GetInstance()
{
	return this->Instance;
}

int CBlock::GetBlockId()
{
	return Java::Env->CallStaticIntMethod(this->GetClass(), StrayCache::block_getIdFromBlock, this->GetInstance());
}
