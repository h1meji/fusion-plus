#include "EntityPlayer.h"

#include "java/java.h"
#include <sdk/sdk.h>
#include <sdk/java/util/List.h>
#include <sdk/java/lang/String.h>

CEntityPlayer::CEntityPlayer()
{
	this->clazz = StrayCache::entityPlayer_class;
}

CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
{
	this->instance = instance;
}


jclass CEntityPlayer::GetClass()
{
	return this->clazz;
}

jobject CEntityPlayer::GetInstance()
{
	return this->instance;
}

CInventoryPlayer CEntityPlayer::GetInventory()
{
	return CInventoryPlayer(Java::env->GetObjectField(this->GetInstance(), StrayCache::entityPlayer_inventory));
}

int CEntityPlayer::GetPing()
{
	jobject netHandlerPlayClient = Java::env->CallObjectMethod(SDK::minecraft->GetInstance(), StrayCache::minecraft_getNetHandler);
	if (netHandlerPlayClient == nullptr) return -1;

	if (Java::version == MinecraftVersion::LUNAR_1_8_9 || Java::version == MinecraftVersion::VANILLA_1_8_9 || Java::version == MinecraftVersion::FORGE_1_8_9)
	{
		// Get player info
		jstring playerName = Java::env->NewStringUTF(this->GetName().c_str());
		jobject networkPlayerInfo = Java::env->CallObjectMethod(netHandlerPlayClient, StrayCache::netHandlerPlayClient_getPlayerInfo, playerName);

		if (networkPlayerInfo != nullptr)
		{
			// Get "responseTime"
			int ping = Java::env->CallIntMethod(networkPlayerInfo, StrayCache::networkPlayerInfo_getResponseTime);
			return ping;
		}
	}
	else
	{
		// Get player info list
		jobject playerInfoList = Java::env->GetObjectField(netHandlerPlayClient, StrayCache::netHandlerPlayClient_playerInfoList);
		jobjectArray playerInfoVector = List(jobject(playerInfoList)).toArray();

		// Loop through player info list
		for (int i = 0; i < Java::env->GetArrayLength(playerInfoVector); i++)
		{
			jobject guiPlayerInfo = Java::env->GetObjectArrayElement(playerInfoVector, i);

			// Get player name
			jobject playerNameObj = Java::env->GetObjectField(guiPlayerInfo, StrayCache::guiPlayerInfo_name);
			std::string playerName = String(playerNameObj).ToString();

			// Check if player name matches
			if (playerName == this->GetName())
			{
				// Get "responseTime"
				int ping = Java::env->GetIntField(guiPlayerInfo, StrayCache::guiPlayerInfo_responseTime);
				return ping;
			}
		}
	}

	return -1;
}
