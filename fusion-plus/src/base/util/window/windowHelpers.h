#pragma once
#include <cfloat>
#include <imgui/imgui.h>

struct AspectRatioData
{
    float ratio;
    ImVec2 lastStableSize;
    bool isFirstUpdate;

    AspectRatioData(float x, float y) : ratio(x / y), isFirstUpdate(true) {}
};

struct WindowHelpers
{
	static void SetFixedAspectRatio(AspectRatioData* aspectData);
};