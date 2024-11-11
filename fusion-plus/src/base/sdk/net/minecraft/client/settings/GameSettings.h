#pragma once
#include "sdk/java/IClass.h"

struct CGameSettings : IClass
{
	CGameSettings();

	jclass GetClass();
	jobject GetInstance();

	int GetThirdPersonView();
	float GetFOV();
	void SetFullscreenKeyToNull();
	void RestoreFullscreenKey();
};

