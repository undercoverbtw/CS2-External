#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class Vector3
{
public:
	float x, y, z;
public:
	Vector3() :x(0.f), y(0.f), z(0.f) {}
	Vector3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
	Vector3 operator+(Vector3 Vector3_)
	{
		return { x + Vector3_.x,y + Vector3_.y,z + Vector3_.z };
	}
	Vector3 operator-(Vector3 Vector3_)
	{
		return { x - Vector3_.x,y - Vector3_.y,z - Vector3_.z };
	}
	Vector3 operator*(Vector3 Vector3_)
	{
		return { x * Vector3_.x,y * Vector3_.y,z * Vector3_.z };
	}
	Vector3 operator/(Vector3 Vector3_)
	{
		return { x / Vector3_.x,y / Vector3_.y,z / Vector3_.z };
	}
	Vector3 operator*(float n)
	{
		return { x * n,y * n,z * n };
	}
	Vector3 operator/(float n)
	{
		return { x / n,y / n,z / n };
	}
	bool operator==(Vector3 Vector3_)
	{
		return x == Vector3_.x && y == Vector3_.y && z == Vector3_.z;
	}
	bool operator!=(Vector3 Vector3_)
	{
		return x != Vector3_.x || y != Vector3_.y || z != Vector3_.z;
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}
	float DistanceTo(const Vector3& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2) + powf(Pos.z - z, 2));
	}
};


