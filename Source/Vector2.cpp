/******************************************************************
\file   Vector2.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Vector2 for math
******************************************************************/
#include "vector2.h"
#include "DebugTool.h"
#include <cmath>

Vector2::Vector2() :x(0.0f), y(0.0f)
{

}
Vector2::Vector2(float xV, float yV) : x(xV), y(yV)
{

}

void Vector2::Set(float xV, float yV)
{
	x = xV;
	y = yV;
}
void Vector2::Set(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

void Vector2::SetZero()
{
	x = 0.f;
	y = 0.f;
}

bool Vector2::IsZero() const
{
	return (x == 0.f) && (y == 0.f);
}
bool Vector2::IsOne() const
{
	return (x == 1.f) && (y == 1.f);
}

float Vector2::DotProduct(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::DotProduct(const Vector2& l, const Vector2& r)
{
	return l.x * r.x + l.y * r.y;
}


float Vector2::LengthSq()
{
	return x*x + y*y;
}
float Vector2::Length()
{
	return sqrt(LengthSq());
}

float Vector2::DistanceSq(const Vector2& v) const
{
	return (*this - v).LengthSq();
}
float Vector2::Distance(const Vector2& v) const
{
	return (*this - v).Length();
}

Vector2& Vector2::Normalize()
{
	float n = Length();
	if (n == 1.f || n == 0.f)
		return *this;
	n = 1.f / n;

	x *= n;
	y *= n;

	return *this;
}


Vector2& Vector2::NormalVector()
{
	float temp = x;
	x = -y;
	y = temp;

	return *this;
}







/************************* operator ***********************/
Vector2 Vector2::operator+(const Vector2& v)
{
	return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator-(const Vector2& v)
{
	return Vector2(x - v.x, y - v.y);
}
Vector2 &Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}
Vector2 &Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}


Vector2 Vector2::operator*(float s) const
{
	return Vector2(x * s, y * s);
}
Vector2 &Vector2::operator*=(float s)
{
	x *= s;
	y *= s;

	return *this;
}

Vector2 Vector2::operator/(float s) const
{
	s = 1.f / s;
	return Vector2(x * s, y * s);
}
Vector2 &Vector2::operator/=(float s)
{
	s = 1.f / s;
	x *= s;
	y *= s;

	return *this;
}

Vector2 Vector2::operator-()const
{
	return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& v) const
{
	return (x == v.x) && (y == v.y);
}
bool Vector2::operator!=(const Vector2& v) const
{
	return (x != v.x) || (y != v.y);
}

