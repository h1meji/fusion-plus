#pragma once
#include "sdk/java/IClass.h"

struct CItem : IClass
{
	CItem();

	CItem(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	std::string GetUnlocalizedName();

	int GetID();

	int GetStackLimit();
};