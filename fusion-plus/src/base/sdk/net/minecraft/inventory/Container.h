#pragma once
#include <vector>
#include "sdk/java/IClass.h"

#include "sdk/net/minecraft/entity/player/EntityPlayer.h"

struct CContainer : IClass
{
	CContainer(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	int GetWindowId();
};