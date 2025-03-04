#pragma once

#include "sdk/java/IClass.h"
#include "sdk/net/minecraft/entity/player/EntityPlayer.h"
#include "util/math/geometry.h"

#include "sdk/net/minecraft/block/state/IBlockState.h"
#include "sdk/net/minecraft/util/BlockPos.h"

#include <vector>

struct CWorld : IClass
{
	CWorld();

	jclass GetClass();
	jobject GetInstance();

	std::vector<CEntityPlayer> GetPlayerList();

	bool rayTraceBlocks(Vector3 from, Vector3 to, Vector3& result, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock);

	//CIBlockState GetBlockState(CBlockPos pos);

	CBlock GetBlock(int x, int y, int z);
};

