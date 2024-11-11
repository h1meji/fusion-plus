#pragma once
#include "sdk/java/IClass.h"

struct CItemStack : IClass
{
	CItemStack();

	CItemStack(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	jobject GetItem();
};