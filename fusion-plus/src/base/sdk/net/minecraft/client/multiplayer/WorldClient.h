#pragma once

#include "sdk/net/minecraft/world/World.h"

struct CWorldClient : CWorld
{
	CWorldClient();

	jclass GetClass();
	jobject GetInstance();

	std::vector<CEntity> GetEntityList();
};

