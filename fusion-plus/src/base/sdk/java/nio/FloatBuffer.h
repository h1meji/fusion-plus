#pragma once

#include "sdk/java/IClass.h"
#include "util/math/geometry.h"

struct FloatBuffer : IClass
{
	FloatBuffer(jobject obj);

	jclass GetClass();
	jobject GetInstance();

	Matrix GetMatrix();

private:
	jmethodID getId;
};

