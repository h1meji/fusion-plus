#pragma once

#include <string>
#include <map>

#include "jni/jni.h"

struct IClass
{
	virtual jobject GetInstance() = 0;
	virtual jclass GetClass() = 0;

protected:
	jobject instance = 0;
	jclass clazz = 0;
};

