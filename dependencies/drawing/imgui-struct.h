#pragma once
#include "more/imgui.h"
#include "more/imgui_impl_win32.h"
#include "more/imgui_impl_dx11.h"
#include "more/imgui_internal.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d11.h>

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_Struct.h
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/9/17	11:30
****************************************************/

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Vector2
{
public:
	float x, y;
public:
	Vector2() :x(0.f), y(0.f) {}
	Vector2(float x_, float y_) :x(x_), y(y_) {}
	Vector2(ImVector2 ImVector2_) :x(ImVector2_.x), y(ImVector2_.y) {}
	Vector2 operator=(ImVector2 ImVector2_)
	{
		x = ImVector2_.x;
		y = ImVector2_.y;
		return *this;
	}
	Vector2 operator+(Vector2 Vector2_)
	{
		return { x + Vector2_.x,y + Vector2_.y };
	}
	Vector2 operator-(Vector2 Vector2_)
	{
		return { x - Vector2_.x,y - Vector2_.y };
	}
	Vector2 operator*(Vector2 Vector2_)
	{
		return { x * Vector2_.x,y * Vector2_.y };
	}
	Vector2 operator/(Vector2 Vector2_)
	{
		return { x / Vector2_.x,y / Vector2_.y };
	}
	Vector2 operator*(float n)
	{
		return { x / n,y / n };
	}
	Vector2 operator/(float n)
	{
		return { x / n,y / n };
	}
	bool operator==(Vector2 Vector2_)
	{
		return x == Vector2_.x && y == Vector2_.y;
	}
	bool operator!=(Vector2 Vector2_)
	{
		return x != Vector2_.x || y != Vector2_.y;
	}
	ImVector2 ToImVector2()
	{
		return ImVector2(x, y);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}
	float DistanceTo(const Vector2& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2));
	}

	Vector2 Scale(float factor)
	{
		return { x * factor, y * factor };
	}

};
class Vec3
{
public:
	float x, y, z;

	Vec3() : x(0.f), y(0.f), z(0.f) {}
	Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	// Non-member operator+ for addition.
	friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// Non-member operator- for subtraction.
	friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// Non-member operator* for element-wise multiplication.
	friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// Non-member operator/ for element-wise division.
	friend Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	bool operator==(const Vec3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vec3& other) const
	{
		return !(*this == other);
	}

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float DistanceTo(const Vec3& Pos) const
	{
		return (*this - Pos).Length();
	}
};

template <typename T>
class Singleton
{
public:
	static T& get()
	{
		static T instance;
		return instance;
	}
};
