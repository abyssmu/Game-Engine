/*
Physics class is used to hold and update the position and rotation of an entity.
*/

#pragma once

//Class Includes
#include "../../../Math/MathLib.h"

//Includes
#include <math.h>

class Physics
{
public:
	void SetPosition(
		MathLib::Vectors::Vector3D position);
	void SetRotation(
		MathLib::Vectors::Vector3D rotation);

	MathLib::Vectors::Vector3D GetPosition();
	MathLib::Vectors::Vector3D GetRotation();
	void UpdatePosRot(
		MathLib::Vectors::Vector3D force,
		MathLib::Vectors::Vector3D torque);

	static double gravity;

private:
	void RotateEulers(MathLib::Vectors::Vector3D& V);

	MathLib::Vectors::Vector3D m_position = { 0, 0, 0 };
	MathLib::Vectors::Vector3D m_rotation = { 0, 0, 0 };
};