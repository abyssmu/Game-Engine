#include "Physics.h"

//Initialize gravity
double Physics::gravity = 9.8;

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
void Physics::SetPosition(MathLib::Vectors::Vector3D position)
{
	m_position = position;
}

//Set object rotation
void Physics::SetRotation(MathLib::Vectors::Vector3D rotation)
{
	m_rotation = rotation;
}

//Get object position
MathLib::Vectors::Vector3D Physics::GetPosition()
{
	return m_position;
}

//Get object rotation
MathLib::Vectors::Vector3D Physics::GetRotation()
{
	return m_rotation;
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