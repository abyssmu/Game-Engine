#include "Directional.h"

MathLib::Vectors::Vector3D Directional::GetDirection()
{
	return m_direction;
}

void Directional::SetDirection(
	MathLib::Vectors::Vector3D d)
{
	m_direction = d;
}