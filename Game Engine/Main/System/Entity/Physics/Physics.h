#pragma once

#ifndef _PHYSICSCLASS_H_
#define _PHYSICSCLASS_H_

//Includes
#include <math.h>

//Class Includes
#include "Math\Math.h"
#include "Vector\Vector.h"

//Globals
const float gravity = 9.8;

class Physics
{
public:
	Physics();
	Physics(const Physics&);
	~Physics();

	//Main Functions
	void SetPosition(float*);
	void SetRotation(float*);

	//Utility Functions
	float* GetPosition();
	float* GetRotation();
	void UpdatePosRot(float, float, float, float*);

private:
	//Math Functions
	void CalculateLocals();
	void CalculateLocalX();
	void CalculateLocalY();
	void CalculateLocalZ();

	//Main Variables
	Vector3D m_localX;
	Vector3D m_localY;
	Vector3D m_localZ;
	Vector3D m_position;
	Vector3D m_rotation;
};

#endif