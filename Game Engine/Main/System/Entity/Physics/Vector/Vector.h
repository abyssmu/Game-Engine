#pragma once

//Includes
#include <math.h>

//Class Includes

#ifndef _VECTOR2DCLASS_H_
#define _VECTOR2DCLASS_H_

class Vector2D
{
public:
	Vector2D();
	Vector2D(float, float);
	Vector2D(const Vector2D&);
	~Vector2D();

	//Operator Functions
	Vector2D operator+(const Vector2D&);
	Vector2D operator+=(const Vector2D&);
	Vector2D operator-(const Vector2D&);
	Vector2D operator-=(const Vector2D&);
	Vector2D operator=(const Vector2D&);

	//Unit Functions
	Vector2D UnitX();
	Vector2D UnitY();

	//Utility Functions
	float Dot(Vector2D*, Vector2D*);
	float Length();
	void Normalize();
	void Scale(float);

	//Utility Variables
	float x, y;
};

#endif

#ifndef _VECTOR3DCLASS_H_
#define _VECTOR3DCLASS_H_

class Vector3D
{
public:
	Vector3D();
	Vector3D(float, float, float);
	Vector3D(const Vector3D&);
	~Vector3D();

	//Operator Functions
	Vector3D operator+(const Vector3D&);
	Vector3D operator+=(const Vector3D&);
	Vector3D operator-(const Vector3D&);
	Vector3D operator-=(const Vector3D&);
	Vector3D operator=(const Vector3D&);

	//Unit Functions
	Vector3D UnitX();
	Vector3D UnitY();
	Vector3D UnitZ();

	//Utility Functions
	Vector3D Cross(Vector3D, Vector3D);
	float Dot(Vector3D, Vector3D);
	float Length();
	void Normalize();
	void Scale(float);

	//Utility Variables
	float x, y, z;
};

#endif

#ifndef _VECTOR4DCLASS_H_
#define _VECTOR4DCLASS_H_

class Vector4D
{
public:
	Vector4D();
	Vector4D(float, float, float, float);
	Vector4D(const Vector4D&);
	~Vector4D();

	//Math Functions
	Vector3D rotateEulerX(Vector3D, float);
	Vector3D rotateEulerY(Vector3D, float);
	Vector3D rotateEulerZ(Vector3D, float);
	Vector3D rotateVbyQ(Vector4D, Vector3D);

	//Operator Functions
	Vector4D operator*(const Vector4D&);

	//Utility Functions
	float Length();
	void Normalize();

	//Utility Variables
	float x, y, z, w;
};

#endif