#include "camera.h"

#include "base.h"
#include "util/logger.h"
#include "util/math/math.h"

Vector3 CameraUtils::GetCameraPosition(const Matrix& modelView) {
	Matrix inversed = modelView.Inverse();

	// Position is relative to the position of the player.
	// inversed.m30 = x
	// inversed.m31 = y
	// inversed.m32 = z

	return Vector3{ inversed.m30, inversed.m31, inversed.m32 };
}

bool CameraUtils::WorldToScreen(Vector3 point, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2 &screenPos) {
	// csp = Clip Space Position
	Vector4 csp = Math::Multiply(
		Math::Multiply(
			Vector4 {point.x, point.y, point.z, 1.0f},
			modelView
		),
		projection
	);

	// ndc = Native Device Coordinate
	Vector3 ndc{
		csp.x / csp.w,
		csp.y / csp.w,
		csp.z / csp.w
	};

	if (ndc.z > 1 && ndc.z < 1.15) {
		screenPos = Vector2{
			((ndc.x + 1.0f) / 2.0f) * screenWidth,
			((1.0f - ndc.y) / 2.0f) * screenHeight,
		};
		return true;
	}

	return false;
}