#pragma once

#include "sdk/java/IClass.h"
#include "entity/EntityPlayerSP.h"
#include "multiplayer/WorldClient.h"
#include "renderer/ActiveRenderInfo.h"
#include "renderer/entity/RenderManager.h"
#include "sdk/net/minecraft/util/Timer.h"
#include "settings/GameSettings.h"
#include "sdk/net/minecraft/util/MovingObjectPosition.h"

struct CMinecraft : IClass
{
	CMinecraft();

	jclass GetClass();
	jobject GetInstance();

	CEntity GetRenderViewEntity();
	bool IsInGuiState();
	void ClickMouse();
	CMovingObjectPosition GetMouseOver();

	CEntityPlayerSP* thePlayer;
	CWorldClient* theWorld;
	CActiveRenderInfo* activeRenderInfo;
	CRenderManager* renderManager;
	CTimer* timer;
	CGameSettings* gameSettings;
};

