#pragma once

#include "sdk/java/IClass.h"

struct CTimer : IClass
{
	CTimer();

	jclass GetClass();
	jobject GetInstance();

	float GetRenderPartialTicks();
};

