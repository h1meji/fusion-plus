#pragma once

#include "sdk/net/minecraft/entity/player/EntityPlayer.h"

struct CEntityPlayerSP : CEntityPlayer
{
	CEntityPlayerSP();

	jclass GetClass();
	jobject GetInstance();
};