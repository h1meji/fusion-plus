#pragma once
#include <algorithm>

class Vector3
{
public:

	float x{ NAN };
	float y{ NAN };
	float z{ NAN };

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator + (const float rhs) const { return Vector3(x + rhs, y + rhs, z + rhs); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator - (const float rhs) const { return Vector3(x - rhs, y - rhs, z - rhs); }
	Vector3 operator * (const Vector3& rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	bool operator == (const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }

	float Length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	Vector3 Invert() const { return Vector3{ -x, -y, -z }; }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
};

struct Vector2
{
	float x{ NAN };
	float y{ NAN };

	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 Invert() const { return Vector2{ -x, -y }; }
};

struct Vector2i
{
	unsigned int x{ 0 };
	unsigned int y{ 0 };
};

struct Vector4
{
	float x{ NAN };
	float y{ NAN };
	float z{ NAN };
	float w{ NAN };
};

// https://github.com/Marcelektro/MCP-919/blob/main/src/minecraft/net/minecraft/util/Matrix4f.java
// For readability & maybe security purposes.
struct Matrix
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;

	// Function to calculate the determinant of the 4x4 matrix
	float Determinant() const
	{
		return
			m00 * (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31)) -
			m01 * (m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30)) +
			m02 * (m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30)) -
			m03 * (m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30));
	}

	// Function to calculate the inverse of the 4x4 matrix
	Matrix Inverse() const
	{
		float det = Determinant();
		if (det == 0.0f)
		{
			return *this;
		}

		float invDet = 1.0f / det;

		Matrix inv{};

		inv.m00 = invDet * (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31));
		inv.m01 = invDet * -(m01 * (m22 * m33 - m23 * m32) - m02 * (m21 * m33 - m23 * m31) + m03 * (m21 * m32 - m22 * m31));
		inv.m02 = invDet * (m01 * (m12 * m33 - m13 * m32) - m02 * (m11 * m33 - m13 * m31) + m03 * (m11 * m32 - m12 * m31));
		inv.m03 = invDet * -(m01 * (m12 * m23 - m13 * m22) - m02 * (m11 * m23 - m13 * m21) + m03 * (m11 * m22 - m12 * m21));

		inv.m10 = invDet * -(m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30));
		inv.m11 = invDet * (m00 * (m22 * m33 - m23 * m32) - m02 * (m20 * m33 - m23 * m30) + m03 * (m20 * m32 - m22 * m30));
		inv.m12 = invDet * -(m00 * (m12 * m33 - m13 * m32) - m02 * (m10 * m33 - m13 * m30) + m03 * (m10 * m32 - m12 * m30));
		inv.m13 = invDet * (m00 * (m12 * m23 - m13 * m22) - m02 * (m10 * m23 - m13 * m20) + m03 * (m10 * m22 - m12 * m20));

		inv.m20 = invDet * (m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30));
		inv.m21 = invDet * -(m00 * (m21 * m33 - m23 * m31) - m01 * (m20 * m33 - m23 * m30) + m03 * (m20 * m31 - m21 * m30));
		inv.m22 = invDet * (m00 * (m11 * m33 - m13 * m31) - m01 * (m10 * m33 - m13 * m30) + m03 * (m10 * m31 - m11 * m30));
		inv.m23 = invDet * -(m00 * (m11 * m23 - m13 * m21) - m01 * (m10 * m23 - m13 * m20) + m03 * (m10 * m21 - m11 * m20));

		inv.m30 = invDet * -(m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30));
		inv.m31 = invDet * (m00 * (m21 * m32 - m22 * m31) - m01 * (m20 * m32 - m22 * m30) + m02 * (m20 * m31 - m21 * m30));
		inv.m32 = invDet * -(m00 * (m11 * m32 - m12 * m31) - m01 * (m10 * m32 - m12 * m30) + m02 * (m10 * m31 - m11 * m30));
		inv.m33 = invDet * (m00 * (m11 * m22 - m12 * m21) - m01 * (m10 * m22 - m12 * m20) + m02 * (m10 * m21 - m11 * m20));

		return inv;
	}
};

struct BoundingBox
{
	double minX;
	double minY;
	double minZ;
	double maxX;
	double maxY;
	double maxZ;
};