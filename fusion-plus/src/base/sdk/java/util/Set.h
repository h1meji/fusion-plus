#pragma once

#include "sdk/java/IClass.h"

struct Set : IClass
{
	Set(jobject jlist);

	jclass GetClass();
	jobject GetInstance();

	jobjectArray toArray();

private:
	jmethodID toArrayId;
};

