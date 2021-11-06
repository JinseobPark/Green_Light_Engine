/******************************************************************
\file   Vector3.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  Vector3 for math
******************************************************************/
#pragma once
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);

	void Set(float x, float y, float z);
	void Set(const Vector3& v);

	void SetZero();

	bool IsZero() const;
	bool IsOne() const;

	float DotProduct(const Vector3& v) const;
	Vector3 CrossProduct(const Vector3& v) const;

	float Length();
	float LengthSq();

	float DistanceSq(const Vector3& v) const;
	float Distance(const Vector3& v) const;

	Vector3& Normalize();

	/****************** operator ******************/
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);

	Vector3 operator*(float s) const;
	Vector3& operator*=(float s);

	Vector3 operator/(float s) const;
	Vector3& operator/=(float s);

	Vector3 operator-()const;

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

};