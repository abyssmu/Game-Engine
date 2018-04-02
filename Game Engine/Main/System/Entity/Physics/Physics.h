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
	//Default onstructor
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
	void UpdatePosRot(MathLib::Vectors::Vector3D force,
		MathLib::Vectors::Vector3D torque);

private:
	////////Math Functions
	//Rotate vector V by Euler matrices
	//Order of rotation x, y, z
	void RotateEulers(MathLib::Vectors::Vector3D& V);

	////////Main Variables
	MathLib::Vectors::Vector3D m_position, m_rotation;
};

#endif