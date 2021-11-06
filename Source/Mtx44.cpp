/******************************************************************
\file   Mtx44.cpp
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  matrix 4 by 4 for math
******************************************************************/
#include "mtx44.h"
#include <iostream>
#include <memory>
//C++ Additions

/*! A 4D Matrix for a 2D game, z is used for Z-order.  This matrix uses row
vectors.  This means the members of a vector are placed in each row of the
matrix.
\verbatim
|Xx Xy Xz 0 |
|Yx Yy Yz 0 |
|Zx Zy Zz 0 |
|Tx Ty Tz 1 |
\endverbatim
*/
Mtx44::Mtx44(void)
{
	SetIdentity();
}

Mtx44::Mtx44(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m10;
	m[0][2] = m20;
	m[0][3] = m30;
	m[1][0] = m01;
	m[1][1] = m11;
	m[1][2] = m21;
	m[1][3] = m31;
	m[2][0] = m02;
	m[2][1] = m12;
	m[2][2] = m22;
	m[2][3] = m32;
	m[3][0] = m03;
	m[3][1] = m13;
	m[3][2] = m23;
	m[3][3] = m33;

}
Mtx44::Mtx44(const Mtx44& rhs)
{
	Set(rhs);
}
Mtx44::Mtx44(const float * m_)
{
	Set(m_);
}
void Mtx44::Set(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m10;
	m[0][2] = m20;
	m[0][3] = m30;
	m[1][0] = m01;
	m[1][1] = m11;
	m[1][2] = m21;
	m[1][3] = m31;
	m[2][0] = m02;
	m[2][1] = m12;
	m[2][2] = m22;
	m[2][3] = m32;
	m[3][0] = m03;
	m[3][1] = m13;
	m[3][2] = m23;
	m[3][3] = m33;
}
void Mtx44::Set(const float * m_)
{
	std::memcpy(m, m_, sizeof(m));
}
void Mtx44::Set(const Mtx44 & copy)
{
	std::memcpy(m, copy.m, sizeof(m));
}
//Member functions
//Sets all of the matrix values to 0
void Mtx44::SetZero(void)
{
	std::memset(m, 0, sizeof(m));
}
//Sets the matrix to the Identity Matrix
void Mtx44::SetIdentity(void)
{
	SetZero();
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
}
bool Mtx44::IsZero() const
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m[j][i] != 0) {
				return false;
			}
		}
	}
	return true;
}
bool Mtx44::IsIdentity() const
{
	Mtx44 rhs;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (m[j][i] != rhs.m[j][i]) {
				return false;
			}
		}
	}
	return true;
}
//Sets this matrix to a tranlsation matrix with the given values
void Mtx44::Translate(float x_, float y_, float z_)
{
	SetIdentity();

	m[0][3] = x_;
	m[1][3] = y_;
	m[2][3] = z_;
}
//Sets this matrix to a tranlsation matrix with the given values
void Mtx44::Translate(const Vector3& trans)
{
	SetIdentity();

	m[0][3] = trans.x;
	m[1][3] = trans.y;
	m[2][3] = trans.z;

}
//Sets the matrix to a scale matrix with the given values
void Mtx44::Scale(float x_, float y_, float z_)
{
	SetIdentity();

	m[0][0] = x_;
	m[1][1] = y_;
	m[2][2] = z_;
}
//Sets this matrix to a scale matrix with the given values
void Mtx44::Scale(const Vector3& scale)
{
	SetIdentity();

	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
}
void Mtx44::Scale(float scale_)
{
	SetIdentity();
	m[0][0] = scale_;
	m[1][1] = scale_;
	m[2][2] = scale_;
}
//Sets this matrix to a Rotation matrix around the Z axix
void Mtx44::RotateZ(float radians)
{
	SetIdentity();

	m[0][0] = cosf(radians);
	m[0][1] = -sinf(radians);
	m[1][0] = sinf(radians);
	m[1][1] = cosf(radians);
}
void Mtx44::RotateX(float radians)
{
	SetIdentity();

	m[1][1] = cosf(radians);
	m[1][2] = -sinf(radians);
	m[2][1] = sinf(radians);
	m[2][2] = cosf(radians);

}
void Mtx44::RotateY(float radians)
{
	SetIdentity();

	m[0][0] = cosf(radians);
	m[0][2] = sinf(radians);
	m[2][0] = -sinf(radians);
	m[2][2] = cosf(radians);

}

Mtx44 Mtx44::operator+(const Mtx44 & mat) const
{
	Mtx44 result;
	result.SetZero();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[j][i] = this->m[j][i] + mat.m[j][i];
		}
	}
	return result;
}

Mtx44 & Mtx44::operator+=(const Mtx44 & mat)
{
	// TODO: insert return statement here
	this->Set((*this) + mat);
	return *this;
}

Mtx44 Mtx44::operator-(const Mtx44 & mat) const
{
	Mtx44 result;
	result.SetZero();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[j][i] = this->m[j][i] - mat.m[j][i];
		}
	}
	return result;
}

Mtx44 & Mtx44::operator-=(const Mtx44 & mat)
{
	// TODO: insert return statement here
	this->Set((*this) - mat);
	return *this;
}

//Operators
//Lets the user mulitply two matricies together
Mtx44 Mtx44::operator*(const Mtx44& rhs) const
{
	Mtx44 multiple;
	multiple.SetZero();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				multiple.m[i][j] += m[i][k] * rhs.m[k][j];
			}
		}
	}
	return multiple;
}
//Lets the user mulitply two matricies together
Mtx44& Mtx44::operator*=(const Mtx44& rhs)
{
	this->Set((*this) * rhs);
	return *this;
}
//Tests if two matricies are the same
bool Mtx44::operator==(const Mtx44& rhs) const
{
	if (*this != rhs)
	{
		return false;
	}
	return true;
}
//Tests if two matrices are not the same
bool Mtx44::operator!=(const Mtx44& rhs) const
{
	for (int i = 0; i < HB_ROWS; ++i)
	{
		for (int j = 0; j < HB_COLS; ++j)
		{
			if (m[j][i] != rhs.m[j][i])
			{
				return true;
			}
		}
	}

	return false;

}


//Non member functions
//Makes all matrix values 0
void Mtx44::MakeZero(Mtx44& result)
{
	result.SetZero();
}
//Sets the given matrix to the Identity matrix
void Mtx44::MakeIdentity(Mtx44& result)
{
	result.SetIdentity();
}
//Multiplies two matricies together
void Mtx44::Multiply(Mtx44& result, const Mtx44& first, const Mtx44& second)
{
	result = first * second;
}

//Sets the given matrix to a translate matrix
void Mtx44::MakeTranslate(Mtx44& result,
	float transX, float transY, float zOrder)
{
	result.Translate(transX, transY, zOrder);
}
void Mtx44::MakeTranslate(Mtx44 & result, const Vector3 & rhs)
{
	result.Translate(rhs);
}
//Sets the given matrix to a scale matrix
void Mtx44::MakeScale(Mtx44& result, float scaleX, float scaleY, float scaleZ)
{
	result.Scale(scaleX, scaleY, scaleZ);
}
void Mtx44::MakeScale(Mtx44 & result, const Vector3 & rhs)
{
	result.Scale(rhs);
}
//Sets the given matrix to a Rotation around the Z axis matrix
void Mtx44::MakeRotateZ(Mtx44& result, float radians)
{
	result.RotateZ(radians);
}

void Mtx44::MakeRotateX(Mtx44 & result, float radians)
{
	result.RotateX(radians);
}

void Mtx44::MakeRotateY(Mtx44 & result, float radians)
{
	result.RotateY(radians);
}
/*
//Sets the given matrix to a scale rotate and translate matrix
void Mtx44::MakeTransform(Mtx44& result, float scaleX, float scaleY,
float radians,
float transX, float transY,
float zOrder)
{
result.MakeTransform(scaleX, scaleY, radians, transX, transY, zOrder);
}*/
//Tests if two matricies are the same
bool Mtx44::IsEqual(const Mtx44& mtx1, const Mtx44& mtx2)
{
	if (mtx1 == mtx2)
	{
		return true;
	}
	return false;
}


Mtx44 Mtx44::GetTranslation(const Vector3 & translation)
{
	Mtx44 result;
	result.Translate(translation);
	return result;
}

Mtx44 Mtx44::GetTranslation(float x, float y, float z)
{
	Mtx44 result;
	result.Translate(x, y, z);
	return result;
}

Mtx44 Mtx44::GetScaling(const Vector3 & scale)
{
	Mtx44 result;
	result.Scale(scale);
	return result;
}

Mtx44 Mtx44::GetScaling(float scale)
{
	Mtx44 result;
	result.Scale(scale);
	return result;
}

Mtx44 Mtx44::GetScaling(float xScale, float yScale, float zScale)
{
	Mtx44 result;
	result.Scale(xScale, yScale, zScale);
	return result;
}


Mtx44 Mtx44::GetRotationX(float angle)
{
	Mtx44 result;
	result.RotateX(angle);
	return result;
}

Mtx44 Mtx44::GetRotationY(float angle)
{
	Mtx44 result;
	result.RotateY(angle);
	return result;

}

Mtx44 Mtx44::GetRotationZ(float angle)
{
	Mtx44 result;
	result.RotateZ(angle);
	return result;

}
