//Entity class
//Acts as an interface for all components of
//world objects

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
bool Entity::Initialize(ID3D11Device* device, float* position,
						float* rotation, char* filename)
{
	bool result;

	//Create and initialize model
	m_model = new Model;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Initialize(device, filename);
	if (!result)
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

//Get model information
ModelInfo* Entity::GetModelInfo(int i)
{
	return m_model->GetModelInfo(i);
}