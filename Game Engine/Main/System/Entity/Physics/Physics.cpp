//Physics class
//Calculates position and rotation of object

#include "Physics.h"

//Constructor
Physics::Physics()
{
	CalculateLocals();
}

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
void Physics::UpdatePosRot(float forw, float lR, float uD,
						float* rotation)
{
	MathLib::Vectors::Vector3D move(0.0f, 0.0f, 0.0f);
	MathLib::Vectors::Vector3D rot(rotation[0], rotation[1],
								rotation[2]);

	//Capture local axis
	MathLib::Vectors::Vector3D moveX(m_localX);
	MathLib::Vectors::Vector3D moveY(m_localY);
	MathLib::Vectors::Vector3D moveZ(m_localZ);

	//Scale movement
	MathLib::Vectors::Scale(&moveX, lR);
	MathLib::Vectors::Scale(&moveY, uD);
	MathLib::Vectors::Scale(&moveZ, forw);

	//Add all axial movement
	MathLib::Vectors::Add(moveY, moveZ);
	MathLib::Vectors::Add(moveX, moveY);
	MathLib::Vectors::Add(move, moveX);

	//Update position if move length > 0
	if (MathLib::Vectors::Length(&move) > 0)
	{
		MathLib::Vectors::Add(m_position, move);
	}

	//Update rotation if rot length > 0
	if (MathLib::Vectors::Length(&rot) > 0)
	{
		MathLib::Vectors::Add(m_rotation, rot);
		CalculateLocals();
	}
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Calculate local axes
void Physics::CalculateLocals()
{
	CalculateLocalX();
	CalculateLocalY();
	CalculateLocalZ();
}

//Calculate local x axis
void Physics::CalculateLocalX()
{
	//Calculate local x with Eulerian rotation
	MathLib::Vectors::Vector3D unitX = unitX.UnitX();

	unitX = MathLib::RotateEulerY(unitX, -m_rotation.y * MathLib::RADIAN);

	m_localX = unitX;
}

//Calculate local y axis
void Physics::CalculateLocalY()
{
	//Calculate local y with Eulerian rotation
	MathLib::Vectors::Vector3D unitY = unitY.UnitY();

	m_localY = unitY;
}

//Calculate local z axis
void Physics::CalculateLocalZ()
{
	//Calculate local z with Eulerian rotation
	MathLib::Vectors::Vector3D unitZ = unitZ.UnitZ();

	unitZ = MathLib::RotateEulerY(unitZ, -m_rotation.y * MathLib::RADIAN);

	m_localZ = unitZ;
}