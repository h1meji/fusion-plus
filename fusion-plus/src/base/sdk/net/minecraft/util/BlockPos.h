#pragma once

#include "sdk/java/IClass.h"

struct CBlockPos : IClass
{
	CBlockPos(int x, int y, int z);
	CBlockPos(float x, float y, float z);

	jclass GetClass();
	jobject GetInstance();
};
