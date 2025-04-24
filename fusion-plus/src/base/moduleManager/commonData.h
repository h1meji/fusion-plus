#pragma once

#include "util/math/geometry.h"
#include "util/logger/logger.h"
#include "sdk/sdk.h"

/*
This file is mainly for optimization purposes, instead of loading the data inside each module, we just load them here and then pass the data onto
the modules that will eventually use them.

The modules that write data will still need to access required java objects to do so.
*/
struct CommonData
{
	inline static bool dataUpdated = false;
	inline static Matrix modelView;
	inline static Matrix projection;
	inline static Vector3 renderPos;
	inline static float renderPartialTicks;
	inline static float fov;
	inline static int thirdPersonView;

	inline static int fps;
	inline static int ping;
	inline static std::string playerName;
	inline static Vector3 playerPos;
	inline static Vector3 playerLastPos;
	inline static Vector3 playerEyePos;
	inline static Vector2 playerAngles;
	inline static float playerYaw;
	inline static float playerPitch;

	struct PlayerData
	{
		CEntityPlayer obj = nullptr;
		Vector3 pos = Vector3();
		Vector3 lastPos = Vector3();
		BoundingBox boundingBox = BoundingBox();
		std::string name = "";
		float height = FLT_MAX;
		float width = FLT_MAX;
		float health = FLT_MAX;
		float maxHealth = FLT_MAX;
	};

	inline static std::vector<PlayerData> nativePlayerList;

	static void UpdateData()
	{
		if (!SanityCheck()) return;
		modelView = SDK::minecraft->activeRenderInfo->ModelViewMatrix();
		projection = SDK::minecraft->activeRenderInfo->ProjectionMatrix();
		fov = SDK::minecraft->gameSettings->GetFOV();
		thirdPersonView = SDK::minecraft->gameSettings->GetThirdPersonView();

		float ySubtractValue = 0.f;
		if (Java::version == MinecraftVersion::LUNAR_1_8_9 || Java::version == MinecraftVersion::VANILLA_1_8_9 || Java::version == MinecraftVersion::FORGE_1_8_9)
		{
			ySubtractValue = 3.4f;
			if (SDK::minecraft->thePlayer->IsSneaking())
				ySubtractValue -= .175f;
		}
		else
		{
			ySubtractValue = .25f;
		}

		renderPos = SDK::minecraft->renderManager->RenderPos() + Vector3{ 0, ySubtractValue, 0 };
		renderPartialTicks = SDK::minecraft->timer->GetRenderPartialTicks();

		// Storing all the required data that will be used within modules here just to have one for loop for gathering data
		// the rest of the for loops inside modules will be for actually doing what they need to do
		std::vector<PlayerData> newData;
		std::vector<CEntityPlayer> playerList = SDK::minecraft->theWorld->GetPlayerList();
		for (CEntityPlayer player : playerList)
		{
			newData.push_back(PlayerData{
					player,
					player.GetPos(),
					player.GetLastTickPos(),
					player.GetBB().GetNativeBoundingBox(),
					player.GetName(),
					player.GetHeight(),
					player.GetWidth(),
					player.GetHealth(),
					player.GetMaxHealth(),
				});
		}
		nativePlayerList = newData;

		fps = SDK::minecraft->GetFps();
		ping = SDK::minecraft->thePlayer->GetPing();
		playerName = SDK::minecraft->thePlayer->GetName();
		playerPos = SDK::minecraft->thePlayer->GetPos();
		playerLastPos = SDK::minecraft->thePlayer->GetLastTickPos();
		playerEyePos = SDK::minecraft->thePlayer->GetEyePos();
		playerAngles = SDK::minecraft->thePlayer->GetAngles();
		playerYaw = playerAngles.x;
		playerPitch = playerAngles.y;

		dataUpdated = true; // This entire function is stopped, and this is flipped once the world and or player object appears to be null
							// Mainly for sanity checks for rendering functions, it prevents crashing whenever the user is not in a game because some data
							// might be needed from within the render functions.
	}

	static bool SanityCheck()
	{
		if (!SDK::minecraft->thePlayer->GetInstance() || !SDK::minecraft->theWorld->GetInstance())
		{
			CommonData::dataUpdated = false;

			// Reset some statistics
			fps = -1;
			ping = -1;
			playerPos = Vector3();
			playerLastPos = Vector3();
			playerEyePos = Vector3();
			playerAngles = Vector2();
			playerYaw = 0.f;
			playerPitch = 0.f;

			return false;
		}
		return true;
	}
};