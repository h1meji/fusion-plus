#pragma once

#include "sdk/net/minecraft/block/Block.h"

struct CIBlockState : IClass
{
	CIBlockState();
	CIBlockState(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CBlock GetBlock();
};