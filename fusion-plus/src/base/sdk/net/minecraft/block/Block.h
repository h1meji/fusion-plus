#pragma once

#include "sdk/java/IClass.h"

struct CBlock : IClass
{
	CBlock();
	CBlock(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	int GetBlockId();
};