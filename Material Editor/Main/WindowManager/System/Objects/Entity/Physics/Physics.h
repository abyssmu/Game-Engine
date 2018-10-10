/*
Physics class is used to hold and update the position and rotation of an entity.
*/

#pragma once

//Includes
#include <math.h>

//Class Includes
#include "..\..\..\Math\MathLib.h"

class Physics
{
public:
	//Default onstructor
	Physics();

	//Default copy constructor
	Physics(const Physics& other);
	
	//Default destructor
	~Physics();

	////////Utility Functions
	//Get object position
	MathLib::Vectors::Vector3D GetPosition();

	//Get object rotation
	MathLib::Vectors::Vector3D GetRotation();

	//Set object position
	void SetPosition(MathLib::Vectors::Vector3D position);

	//Set object rotation
	void SetRotation(MathLib::Vectors::Vector3D rotation);

	//Update object position and rotation
	void UpdatePosRot(MathLib::Vectors::Vector3D force,
		MathLib::Vectors::Vector3D torque);

	////////Globals
	static double gravity;

private:
	////////Math Functions
	//Rotate vector V by Euler matrices
	//Order of rotation x, y, z
	void RotateEulers(MathLib::Vectors::Vector3D& V);

	////////Main Variables
	MathLib::Vectors::Vector3D m_position, m_rotation;
};