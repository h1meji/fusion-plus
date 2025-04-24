#pragma once

#include <iostream>

#include "sdk/java/IClass.h"
#include "sdk/net/minecraft/util/Timer.h"
#include "sdk/net/minecraft/util/MovingObjectPosition.h"
#include "sdk/net/minecraft/client/gui/inventory/GuiChest.h"
#include "sdk/net/minecraft/enchantment/EnchantmentHelper.h"
#include "entity/EntityPlayerSP.h"
#include "multiplayer/PlayerControllerMP.h"
#include "multiplayer/WorldClient.h"
#include "renderer/ActiveRenderInfo.h"
#include "renderer/entity/RenderManager.h"
#include "settings/GameSettings.h"

struct CMinecraft : IClass
{
	CMinecraft();

	jclass GetClass();
	jobject GetInstance();

	CEntity GetRenderViewEntity();
	bool IsInGuiState();
	bool IsInInventory();
	bool IsInChest();
	CGuiChest* GetGuiChest();
	void ClickMouse();
	CMovingObjectPosition GetMouseOver();
	int GetFps();

	std::unique_ptr<CEntityPlayerSP> thePlayer;
	std::unique_ptr<CPlayerControllerMP> playerController;
	std::unique_ptr<CWorldClient> theWorld;
	std::unique_ptr<CActiveRenderInfo> activeRenderInfo;
	std::unique_ptr<CRenderManager> renderManager;
	std::unique_ptr<CTimer> timer;
	std::unique_ptr<CGameSettings> gameSettings;
	std::unique_ptr<CEnchantmentHelper> enchantmentHelper;

	std::string originalClientBrand;
};

