#include "Physics.h"

double Physics::gravity = 9.8;

void Physics::SetPosition(
	MathLib::Vectors::Vector3D position)
{
	m_position = position;
}

void Physics::SetRotation(
	MathLib::Vectors::Vector3D rotation)
{
	m_rotation = rotation;
}

MathLib::Vectors::Vector3D Physics::GetPosition()
{
	return m_position;
}

MathLib::Vectors::Vector3D Physics::GetRotation()
{
	return m_rotation;
}

void Physics::UpdatePosRot(
	MathLib::Vectors::Vector3D force,
	MathLib::Vectors::Vector3D torque)
{
	if (MathLib::Vectors::Length(&torque) > 0)
	{
		MathLib::Vectors::Add(&m_rotation, &torque);
	}

	if (MathLib::Vectors::Length(&force) > 0)
	{
		RotateEulers(force);
		MathLib::Vectors::Add(&m_position, &force);
	}
}

void Physics::RotateEulers(
	MathLib::Vectors::Vector3D& V)
{
	V = MathLib::RotateEulerX(&V, -m_rotation.x * MathLib::RADIAN);
	V = MathLib::RotateEulerY(&V, -m_rotation.y * MathLib::RADIAN);
	V = MathLib::RotateEulerZ(&V, -m_rotation.z * MathLib::RADIAN);
}