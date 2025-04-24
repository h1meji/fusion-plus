#include "Block.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CBlock::CBlock()
{
	if (!StrayCache::initialized) StrayCache::Init();
	this->clazz = StrayCache::block_class;
}

CBlock::CBlock(jobject instance) : CBlock()
{
	this->instance = instance;
}

jclass CBlock::GetClass()
{
	return this->clazz;
}

jobject CBlock::GetInstance()
{
	return this->instance;
}

int CBlock::GetBlockId()
{
	return Java::env->CallStaticIntMethod(this->GetClass(), StrayCache::block_getIdFromBlock, this->GetInstance());
}
