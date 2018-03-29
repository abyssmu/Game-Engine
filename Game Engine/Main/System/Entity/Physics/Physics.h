#pragma once

#ifndef _PHYSICSCLASS_H_
#define _PHYSICSCLASS_H_

//Includes
#include <math.h>

//Class Includes
#include "../../Math/MathLib.h"

//Globals
const float gravity = 9.8;

class Physics
{
public:
	//Constructor
	Physics();

	//Default copy constructor
	Physics(const Physics& other);
	
	//Default destructor
	~Physics();

	////////Main Functions
	//Set object position
	void SetPosition(float* position);

	//Set object rotation
	void SetRotation(float* rotation);

	////////Utility Functions
	//Get object position
	float* GetPosition();

	//Get object rotation
	float* GetRotation();

	//Update object position and rotation
	void UpdatePosRot(float forw, float lR, float uD,
					float* rotation);

private:
	////////Math Functions
	//Calculate local axes
	void CalculateLocals();

	//Calculate local x axis
	void CalculateLocalX();

	//Calculate local y axis
	void CalculateLocalY();

	//Calculate local z axis
	void CalculateLocalZ();

	////////Main Variables
	MathLib::Vectors::Vector3D m_localX;
	MathLib::Vectors::Vector3D m_localY;
	MathLib::Vectors::Vector3D m_localZ;
	MathLib::Vectors::Vector3D m_position;
	MathLib::Vectors::Vector3D m_rotation;
};

#endif