#pragma once

#include "sdk/java/IClass.h"
#include "util/math/geometry.h"
#include "sdk/strayCache.h"

struct CAxisAlignedBB : IClass
{
	CAxisAlignedBB();
	CAxisAlignedBB(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	BoundingBox GetNativeBoundingBox();
	void SetBoundingBox(BoundingBox newBoundingBox);
};

