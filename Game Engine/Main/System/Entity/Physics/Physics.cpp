//Physics class
//Calculates position and rotation of object

#include "Physics.h"

//Default constructor
Physics::Physics()
{}

//Default copy constructor
Physics::Physics(const Physics& other)
{}

//Default destructor
Physics::~Physics()
{}

//Set object position
void Physics::SetPosition(float* position)
{
	m_position.x = position[0];
	m_position.y = position[1];
	m_position.z = position[2];
}

//Set object rotation
void Physics::SetRotation(float* rotation)
{
	m_rotation.x = rotation[0];
	m_rotation.y = rotation[1];
	m_rotation.z = rotation[2];
}

//Get object position
float* Physics::GetPosition()
{
	float pos[3] = { m_position.x,
					m_position.y,
					m_position.z };

	return pos;
}

//Get object rotation
float* Physics::GetRotation()
{
	float rot[3] = { m_rotation.x,
		m_rotation.y,
		m_rotation.z };

	return rot;
}

//Update object position and rotation
void Physics::UpdatePosRot(MathLib::Vectors::Vector3D force,
	MathLib::Vectors::Vector3D torque)
{
	//Update rotation if rot length > 0
	if (MathLib::Vectors::Length(&torque) > 0)
	{
		MathLib::Vectors::Add(&m_rotation, &torque);
	}

	//Update position if move length > 0
	if (MathLib::Vectors::Length(&force) > 0)
	{
		RotateEulers(force);
		MathLib::Vectors::Add(&m_position, &force);
	}
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Rotate vector V by Euler matrices
//Order of rotation x, y, z
void Physics::RotateEulers(MathLib::Vectors::Vector3D& V)
{
	V = MathLib::RotateEulerX(&V, -m_rotation.x * MathLib::RADIAN);
	V = MathLib::RotateEulerY(&V, -m_rotation.y * MathLib::RADIAN);
	V = MathLib::RotateEulerZ(&V, -m_rotation.z * MathLib::RADIAN);
}