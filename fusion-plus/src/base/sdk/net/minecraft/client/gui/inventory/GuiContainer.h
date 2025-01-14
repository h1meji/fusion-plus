#pragma once
#include "sdk/net/minecraft/inventory/Container.h"

struct CGuiContainer : IClass
{
	CGuiContainer(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CContainer* GetContainer();
};