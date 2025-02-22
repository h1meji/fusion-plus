#pragma once
#include "geometry.h"

constexpr double PI = 3.141592653589793238462643383279502884197;

class Math
{
public:
	static float wrapAngleTo180(float angle);
	static Vector2 vec_wrapAngleTo180(Vector2 angle);

	static float coterminal(float angle);

	static float magnitude(Vector3 vector);
	static Vector3 crossProduct(Vector3 p1, Vector3 p2);
	static float shortestDistance(Vector3 p, Vector3 a, Vector3 b);
	static Vector2 getAngles(Vector3 pos1, Vector3 pos2);
	static float radiantsToDeg(double x);
	static float degToRadiants(float x);
};

