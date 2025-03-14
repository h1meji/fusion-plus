#include "EntityPlayer.h"

#include "java/java.h"
#include <sdk/sdk.h>
#include <sdk/java/util/List.h>
#include <sdk/java/lang/String.h>

CEntityPlayer::CEntityPlayer()
{
	this->Class = StrayCache::entityPlayer_class;
	this->FieldIDs["inventory"] = StrayCache::entityPlayer_inventory;
}

CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
{
	this->Instance = instance;
}


jclass CEntityPlayer::GetClass()
{
	return this->Class;
}

jobject CEntityPlayer::GetInstance()
{
	return this->Instance;
}

CInventoryPlayer CEntityPlayer::GetInventory()
{
	return CInventoryPlayer(Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["inventory"]));
}

int CEntityPlayer::GetPing()
{
	jobject netHandlerPlayClient = Java::Env->CallObjectMethod(SDK::Minecraft->GetInstance(), StrayCache::minecraft_getNetHandler);
	if (netHandlerPlayClient == nullptr) return -1;

	if (Java::Version == MinecraftVersion::LUNAR_1_8_9 || Java::Version == MinecraftVersion::VANILLA_1_8_9 || Java::Version == MinecraftVersion::FORGE_1_8_9)
	{
		// Get player info
		jstring playerName = Java::Env->NewStringUTF(this->GetName().c_str());
		jobject networkPlayerInfo = Java::Env->CallObjectMethod(netHandlerPlayClient, StrayCache::netHandlerPlayClient_getPlayerInfo, playerName);

		if (networkPlayerInfo != nullptr)
		{
			// Get "responseTime"
			int ping = Java::Env->CallIntMethod(networkPlayerInfo, StrayCache::networkPlayerInfo_getResponseTime);
			return ping;
		}
	}
	else
	{
		// Get player info list
		jobject playerInfoList = Java::Env->GetObjectField(netHandlerPlayClient, StrayCache::netHandlerPlayClient_playerInfoList);
		jobjectArray playerInfoVector = List(jobject(playerInfoList)).toArray();

		// Loop through player info list
		for (int i = 0; i < Java::Env->GetArrayLength(playerInfoVector); i++)
		{
			jobject guiPlayerInfo = Java::Env->GetObjectArrayElement(playerInfoVector, i);

			// Get player name
			jobject playerNameObj = Java::Env->GetObjectField(guiPlayerInfo, StrayCache::guiPlayerInfo_name);
			std::string playerName = String(playerNameObj).ToString();

			// Check if player name matches
			if (playerName == this->GetName())
			{
				// Get "responseTime"
				int ping = Java::Env->GetIntField(guiPlayerInfo, StrayCache::guiPlayerInfo_responseTime);
				return ping;
			}
		}
	}

	return -1;
}
