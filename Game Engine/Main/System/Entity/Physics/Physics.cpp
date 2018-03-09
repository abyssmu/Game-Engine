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
void Physics::UpdatePosRot(float forw, float lR, float uD, float* rotation)
{
	Vector3D move(0.0f, 0.0f, 0.0f);
	Vector3D rot(rotation[0], rotation[1], rotation[2]);

	//Capture local axis
	Vector3D moveX(m_localX);
	Vector3D moveY(m_localY);
	Vector3D moveZ(m_localZ);

	//Scale movement
	moveX.Scale(lR);
	moveY.Scale(uD);
	moveZ.Scale(forw);

	//Add all axial movement
	move += moveX + moveY + moveZ;

	//Update position if move length > 0
	if (move.Length() > 0)
	{
		m_position += move;
	}

	//Update rotation if rot length > 0
	if (rot.Length() > 0)
	{
		m_rotation += rot;
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

//Calculate local X axis
void Physics::CalculateLocalX()
{
	//Calculate local X with Eulerian rotation
	Vector3D unit = unit.UnitX();
	Vector4D rot;

	unit = rot.rotateEulerY(unit, (m_rotation.y * M_PI_OVER_180));

	m_localX = unit;
}

//Calculate local Y axis
void Physics::CalculateLocalY()
{
	//Calculate local Y with Eulerian rotation
	Vector3D unit = unit.UnitY();
	Vector4D rot;

	unit = rot.rotateEulerY(unit, (m_rotation.y * M_PI_OVER_180));

	m_localY = unit;
}

//Calculate local Z axis
void Physics::CalculateLocalZ()
{
	//Calculate local Z with Eulerian rotation
	Vector3D unit = unit.UnitZ();
	Vector4D rot;

	unit = rot.rotateEulerY(unit, (m_rotation.y * M_PI_OVER_180));

	m_localZ = unit;
}