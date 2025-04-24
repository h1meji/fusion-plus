#pragma once

#include "geometry.h"

struct CameraUtils
{
	static Vector3 GetCameraPosition(const Matrix& modelView);
	static bool WorldToScreen(Vector3 point, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2& screenPos);
};

