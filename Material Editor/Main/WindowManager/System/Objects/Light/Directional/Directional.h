/*
Directional light that operates as ambient outdoor lighting.
*/

#pragma once

//Class Includes
#include "../Light.h"

class Directional : public Light, public Entity
{
public:
	MathLib::Vectors::Vector3D GetDirection();

	void SetDirection(
		MathLib::Vectors::Vector3D d);

private:
	MathLib::Vectors::Vector3D m_direction = MathLib::Vectors::Zero_3D();
};