#pragma once
#include "sdk/java/IClass.h"

#include "Item.h"

struct CItemStack : IClass
{
	CItemStack();

	CItemStack(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CItem GetItem();

	int GetMetadata();
};