/******************************************************************
\file   Mtx44.h
\title  GreenLight
\author Jinseob Park
\par    GAM200
\brief  matrix 4 by 4 for math
******************************************************************/
#pragma once
#ifndef HB_MTX44_H
#define HB_MTX44_H

#include "Vector3.h"

/*! The number of rows in the matrix*/
const int HB_ROWS = 4;
/*! The number of columns in the matrix*/
const int HB_COLS = 4;

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
class Mtx44
{
public:

	float m[HB_ROWS][HB_COLS];/*!< Array of 16 floats to represent a 4x4 matrix*/

							  //C++ Additions				
	Mtx44(void);
	Mtx44(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	Mtx44(const Mtx44& rhs);
	Mtx44(const float* m);

	//Member functions
	void Set(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	void Set(const float* m);
	void Set(const Mtx44& copy);
	//Sets all of the matrix values to 0
	void SetZero(void);
	//Sets the matrix to the Identity Matrix
	void SetIdentity(void);

	bool IsZero() const;
	bool IsIdentity() const;

	bool Inverse();
	Mtx44 GetInversed() const;

	void Transpose();
	Mtx44 GetTransposed()const;

	void Transform(const Vector3& rhs); //????
										//Sets this matrix to a tranlsation matrix with the given values
	void Translate(float x_, float y_, float z_);
	//Sets this matrix to a tranlsation matrix with the given values
	void Translate(const Vector3& rhs);
	//Sets the matrix to a scale matrix with the given values
	void Scale(float x_, float y_, float z_);
	//Sets this matrix to a scale matrix with the given values
	void Scale(const Vector3& scale);
	void Scale(float scale_);
	//Sets this matrix to a Rotation matrix around the Z axix
	void RotateZ(float radians);
	void RotateX(float radians);
	void RotateY(float radians);
	void Rotate(const Vector3& axis, float radians);//??

													/*//Operators
													//Lets the user mulitply two matricies together
													Mtx44 operator*(const Mtx44& rhs) const;
													//Lets the user mulitply two matricies together
													Mtx44& operator*=(const Mtx44& rhs);
													Mtx44 & operator=(const Mtx44 & rhs);
													//Tests if two matricies are the same
													bool operator==(const Mtx44& rhs) const;
													//Tests if two matrices are not the same
													bool operator!=(const Mtx44& rhs) const;*/
	Mtx44 operator+(const Mtx44& mat) const;
	Mtx44& operator+=(const Mtx44& mat);
	Mtx44 operator-(const Mtx44& mat) const;
	Mtx44& operator-=(const Mtx44& mat);
	Mtx44 operator*(const Mtx44& mat) const;
	Mtx44& operator*=(const Mtx44& mat);

	// ?????
	Mtx44 operator*(float s) const;
	Mtx44& operator*=(float s);
	Mtx44 operator/ (float s) const;
	Mtx44& operator/=(float s);

	Vector3 Mtx44::operator*(const Vector3& v) const;
	friend Vector3& operator*=(Vector3&v, const Mtx44& mat);

	bool operator==(const Mtx44& mat) const;
	bool operator!=(const Mtx44& mat) const;



	//Non member functions
	//Makes all matrix values 0
	static void MakeZero(Mtx44& result);
	//Sets the given matrix to the Identity matrix
	static void MakeIdentity(Mtx44& result);
	//Multiplies two matricies together
	static void Multiply(Mtx44& result, const Mtx44& first, const Mtx44& second);

	//Sets the given matrix to a translate matrix
	static void MakeTranslate(Mtx44& result,
		float transX, float transY, float zOrder);

	//Sets the given matrix to a translate matrix
	static void MakeTranslate(Mtx44& result,
		const Vector3& rhs);

	//Sets the given matrix to a scale matrix
	static void MakeScale(Mtx44& result, float scaleX, float scaleY, float scaleZ);
	static void MakeScale(Mtx44& result, const Vector3& rhs);
	//Sets the given matrix to a Rotation around the Z axis matrix
	static void MakeRotateZ(Mtx44& result, float radians);
	static void MakeRotateX(Mtx44& result, float radians);
	static void MakeRotateY(Mtx44& result, float radians);

	/*	//Sets the given matrix to a scale rotate and translate matrix
	static void MakeTransform(Mtx44& result, float scaleX, float scaleY,
	float scaleZ,
	float radians,
	float transX, float transY,
	float transZ);

	static	void MakeTransform(Mtx44& result, const Vector3& scale, float radians,
	const Vector3& trans);*/


	static Mtx44 GetTranslation(const Vector3& translation);
	static Mtx44 GetTranslation(float xTranslation, float yTranslation,
		float zTranslation);

	static Mtx44 GetScaling(const Vector3& scale);
	static Mtx44 GetScaling(float scale);
	static Mtx44 GetScaling(float xScale, float yScale, float zScale);

	//??
	static Mtx44 GetRotation(const Vector3& axis, float angle);

	static Mtx44 GetRotationX(float angle);
	static Mtx44 GetRotationY(float angle);
	static Mtx44 GetRotationZ(float angle);

	//Tests if two matricies are the same
	static bool IsEqual(const Mtx44& mtx1, const Mtx44& mtx2);


};




#endif
