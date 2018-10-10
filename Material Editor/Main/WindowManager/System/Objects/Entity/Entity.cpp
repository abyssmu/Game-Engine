#include "Entity.h"

//Constructor
Entity::Entity()
{
	//Initialize pointers
	m_model = 0;
}

//Default copy constructor
Entity::Entity(const Entity& other)
{}

//Default destructor
Entity::~Entity()
{}

//Initialize components
bool Entity::Initialize(ID3D11Device* device, MathLib::Vectors::Vector3D position,
						MathLib::Vectors::Vector3D rotation, char* filename)
{
	//Create and initialize model
	m_model = new Model;
	if (!m_model)
	{
		return false;
	}

	if (!m_model->Initialize(device, filename))
	{
		return false;
	}

	//Set physics variables
	SetPosition(position);
	SetRotation(rotation);

	return true;
}

//Shutdown components
void Entity::Shutdown()
{
	//Shutdown model
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}
}

//Get number of meshes
int Entity::GetNumMeshes()
{
	return m_model->GetNumMeshes();
}

//Set physics on or off
void Entity::SetPhysics(bool onOff)
{
	physicsOnOff = onOff;
}

//Get model information
AllModelInfo* Entity::GetModelInfo(int i)
{
	return m_model->GetModelInfo(GetPosition(), GetRotation(), i);
}