#pragma once

#include <iostream>

#include "sdk/java/IClass.h"
#include "entity/EntityPlayerSP.h"
#include "multiplayer/PlayerControllerMP.h"
#include "multiplayer/WorldClient.h"
#include "renderer/ActiveRenderInfo.h"
#include "renderer/entity/RenderManager.h"
#include "sdk/net/minecraft/util/Timer.h"
#include "settings/GameSettings.h"
#include "sdk/net/minecraft/util/MovingObjectPosition.h"
#include "sdk/net/minecraft/client/gui/inventory/GuiChest.h"
#include "sdk/net/minecraft/enchantment/EnchantmentHelper.h"

struct CMinecraft : IClass
{
	CMinecraft();

	jclass GetClass();
	jobject GetInstance();

	CEntity GetRenderViewEntity();
	bool IsInGuiState();
	bool IsInInventory();
	bool IsInChest();
	void ClickMouse();
	CMovingObjectPosition GetMouseOver();

	CEntityPlayerSP* thePlayer;
	CPlayerControllerMP* playerController;
	CWorldClient* theWorld;
	CActiveRenderInfo* activeRenderInfo;
	CRenderManager* renderManager;
	CTimer* timer;
	CGameSettings* gameSettings;
	CEnchantMentHelper* enchantmentHelper;

	CGuiChest* GetGuiChest();

	std::string OriginalClientBrand;
};

