#pragma once

#include "sdk/java/IClass.h"
#include "util/math/geometry.h"

struct CVec3 : IClass
{
	CVec3();
	CVec3(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	Vector3 GetNativeVector3();
};

