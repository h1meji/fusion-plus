#pragma once

#include "util/math/geometry.h"
#include "sdk/sdk.h"
#include "util/logger/logger.h"

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
	
	struct PlayerData{
		CEntityPlayer obj = nullptr;
		Vector3 pos = Vector3();
		Vector3 lastPos = Vector3();
		BoundingBox boundingBox = BoundingBox();
		std::string name = "";
		float height = FLT_MAX;
		float width = FLT_MAX;
		float health = FLT_MAX;
		float maxHealth = FLT_MAX;

		// Tag-Back head item
		CItem headItem;
	};

	inline static std::vector<PlayerData> nativePlayerList;

	static void UpdateData()
	{
		if (!SanityCheck()) return;
		modelView = SDK::Minecraft->activeRenderInfo->ModelViewMatrix();
		projection = SDK::Minecraft->activeRenderInfo->ProjectionMatrix();
		fov = SDK::Minecraft->gameSettings->GetFOV();
		thirdPersonView = SDK::Minecraft->gameSettings->GetThirdPersonView();

		float ySubtractValue = 0.f;
		if (Java::Version == MinecraftVersion::LUNAR_1_8_9 || Java::Version == MinecraftVersion::VANILLA_1_8_9 || Java::Version == MinecraftVersion::FORGE_1_8_9)
		{
			ySubtractValue = 3.4f;
			if (SDK::Minecraft->thePlayer->IsSneaking())
				ySubtractValue -= .175f;
		}
		else
		{
			ySubtractValue = .25f;
		}

		renderPos = SDK::Minecraft->renderManager->RenderPos() + Vector3{ 0, ySubtractValue, 0 };
		renderPartialTicks = SDK::Minecraft->timer->GetRenderPartialTicks();

		// Storing all the required data that will be used within modules here just to have one for loop for gathering data
		// the rest of the for loops inside modules will be for actually doing what they need to do
		std::vector<PlayerData> newData;
		std::vector<CEntityPlayer> playerList = SDK::Minecraft->theWorld->GetPlayerList();
		for (CEntityPlayer player : playerList) {
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
					player.GetInventory().GetArmorInventory()[3].GetItem()
				});
		}
		nativePlayerList = newData;

		fps = SDK::Minecraft->GetFps();
		ping = SDK::Minecraft->thePlayer->GetPing();

		dataUpdated = true; // This entire function is stopped, and this is flipped once the world and or player object appears to be null
							// Mainly for sanity checks for rendering functions, it prevents crashing whenever the user is not in a game because some data
							// might be needed from within the render functions.
	}

	// Return false if sanity check failed
	static bool SanityCheck() {
		if (!SDK::Minecraft->thePlayer->GetInstance() || !SDK::Minecraft->theWorld->GetInstance())
		{
			CommonData::dataUpdated = false;

			// Reset some statistics
			fps = -1;

			return false;
		}
		return true;
	}
};