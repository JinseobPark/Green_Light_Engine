/******************************************************************
\file   Vector2.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Vector2 for math
******************************************************************/
#pragma once
#include <math.h>
#include <float.h>
#include <assert.h>
#include <stdlib.h>

const float pi = 3.14159265358979323846264f;
class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	void Set(float x, float y);
	void Set(const Vector2& v);

	void SetZero();

	bool IsZero() const;
	bool IsOne() const;

	float DotProduct(const Vector2& v) const;
	float DotProduct(const Vector2& l, const Vector2& r);

	float Length();
	float LengthSq();

	float DistanceSq(const Vector2& v) const;
	float Distance(const Vector2& v) const;

	Vector2& Normalize();

	Vector2& NormalVector();

	/****************** operator ******************/
	Vector2 operator+(const Vector2& v) ;
	Vector2 operator-(const Vector2& v) ;
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);

	Vector2 operator*(float s) const;
	Vector2& operator*=(float s);

	Vector2 operator/(float s) const;
	Vector2& operator/=(float s);

	Vector2 operator-()const;

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

};

struct Mat22
{
	Mat22() {}
	Mat22(float angle)
	{
		float c = cosf(angle), s = sinf(angle);
		col1.x = c; col2.x = -s;
		col1.y = s; col2.y = c;
	}

	Mat22(const Vector2& col1, const Vector2& col2) : col1(col1), col2(col2) {}

	Mat22 Transpose() const
	{
		return Mat22(Vector2(col1.x, col2.x), Vector2(col1.y, col2.y));
	}

	Mat22 Invert() const
	{
		float a = col1.x, b = col2.x, c = col1.y, d = col2.y;
		Mat22 B;
		float det = a * d - b * c;
		assert(det != 0.0f);
		det = 1.0f / det;
		B.col1.x = det * d;	B.col2.x = -det * b;
		B.col1.y = -det * c;	B.col2.y = det * a;
		return B;
	}

	Vector2 col1, col2;
};


inline float DotProduct(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

inline float CrossProduct(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

inline Vector2 CrossProduct(const Vector2& a, float s)
{
	return Vector2(s * a.y, -s * a.x);
}

inline Vector2 CrossProduct(float s, const Vector2& a)
{
	return Vector2(-s * a.y, s * a.x);
}

inline Vector2 operator * (const Mat22& A, const Vector2& v)
{
	return Vector2(A.col1.x * v.x + A.col2.x * v.y, A.col1.y * v.x + A.col2.y * v.y);
}

inline Vector2 operator + (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

inline Vector2 operator - (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

inline Vector2 operator * (float s, const Vector2& v)
{
	return Vector2(s * v.x, s * v.y);
}

inline Mat22 operator + (const Mat22& A, const Mat22& B)
{
	return Mat22(A.col1 + B.col1, A.col2 + B.col2);
}

inline Mat22 operator * (const Mat22& A, const Mat22& B)
{
	return Mat22(A * B.col1, A * B.col2);
}

inline float Abs(float a)
{
	return a > 0.0f ? a : -a;
}

inline Vector2 Abs(const Vector2& a)
{
	return Vector2(fabsf(a.x), fabsf(a.y));
}

inline Mat22 Abs(const Mat22& A)
{
	return Mat22(Abs(A.col1), Abs(A.col2));
}

inline float Sign(float x)
{
	return x < 0.0f ? -1.0f : 1.0f;
}

inline float Min(float a, float b)
{
	return a < b ? a : b;
}

inline float Max(float a, float b)
{
	return a > b ? a : b;
}

inline float Clamp(float a, float low, float high)
{
	return Max(low, Min(a, high));
}

template<typename T> inline void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

// Random number in range [-1,1]
inline float Random()
{
	float r = (float)rand();
	r /= RAND_MAX;
	r = 2.0f * r - 1.0f;
	return r;
}

inline float Random_float(float lo, float hi)
{
	float r = (float)rand();
	r /= RAND_MAX;
	r = (hi - lo) * r + lo;
	return r;
}