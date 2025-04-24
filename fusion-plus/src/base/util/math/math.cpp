#include "math.h"

#include <cmath>

float Math::WrapAngleTo180(float angle)
{
	angle = std::fmod(angle, 360.0f);
	if (angle >= 180.0f)
	{
		angle -= 360.0f;
	}

	if (angle < -180.0f)
	{
		angle += 360.0f;
	}

	return angle;
}

Vector2 Math::WrapAngleTo180(Vector2 angle)
{
	return Vector2{
		WrapAngleTo180(angle.x),
		WrapAngleTo180(angle.y),
	};
}

float Math::Coterminal(float angle) {
	return std::fmod(angle, 180) < 0 ? angle + 170 : angle;
}


float Math::Magnitude(Vector3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Math::CrossProduct(Vector3 v1, Vector3 v2)
{
	return Vector3{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

float Math::ShortestDistance(Vector3 p, Vector3 a, Vector3 b)
{

	Vector3 ab{ b.x - a.x, b.y - a.y, b.z - a.z };
	Vector3 cp = CrossProduct(
		Vector3{p.x - a.x, p.y - a.y, p.z - a.z},
		ab
	);

	return Magnitude(cp) / Magnitude(ab);
}

Vector2 Math::GetAngles(Vector3 pos, Vector3 pos1)
{
	double d_x = pos1.x - pos.x;
	double d_y = pos1.y - pos.y;
	double d_z = pos1.z - pos.z;

	double hypothenuse = sqrt(d_x * d_x + d_z * d_z);
	float yaw = RadiantsToDeg(atan2(d_z, d_x)) - 90.f;
	float pitch = RadiantsToDeg(-atan2(d_y, hypothenuse));

	return Vector2(yaw, pitch);
}

float Math::RadiantsToDeg(double x)
{
	return (float)x * 180.f / (float)PI;
}

float Math::DegToRadiants(float x)
{
	return x * (float)PI / 180.f;
}

Vector4 Math::Multiply(Vector4 v, Matrix m) {
	return Vector4{
		v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
		v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
		v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
		v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
	};
}