#pragma once

#include "sdk/java/IClass.h"

struct List : IClass
{
	List(jobject jlist);
	~List();

	jclass GetClass();
	jobject GetInstance();

	jobjectArray toArray();

private:
	jmethodID toArrayId;
};

