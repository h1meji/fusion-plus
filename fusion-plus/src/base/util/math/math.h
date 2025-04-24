#pragma once

#include "geometry.h"

constexpr double PI = 3.141592653589793238462643383279502884197;

struct Math
{
	static float WrapAngleTo180(float angle);
	static Vector2 WrapAngleTo180(Vector2 angle);

	static float Coterminal(float angle);

	static float Magnitude(Vector3 vector);
	static Vector3 CrossProduct(Vector3 p1, Vector3 p2);
	static float ShortestDistance(Vector3 p, Vector3 a, Vector3 b);
	static Vector2 GetAngles(Vector3 pos1, Vector3 pos2);
	static float RadiantsToDeg(double x);
	static float DegToRadiants(float x);
};

