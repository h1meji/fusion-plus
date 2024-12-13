#pragma once

#include "sdk/java/IClass.h"

struct CBlockPos : IClass
{
	CBlockPos(int x, int y, int z);
	CBlockPos(double x, double y, double z);

	jclass GetClass();
	jobject GetInstance();
};
