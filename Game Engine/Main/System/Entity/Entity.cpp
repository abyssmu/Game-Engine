#include "Entity.h"

Entity::Entity()
{
	m_model = 0;
}

Entity::Entity(const Entity& other)
{}

Entity::~Entity()
{}

bool Entity::Initialize(ID3D11Device* device)
{
	bool result;

	//Create and initialize model
	m_model = new Model;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Initialize(device);
	if (!result)
	{
		return false;
	}

	return true;
}

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

ModelInfo* Entity::GetModelInfo()
{
	return m_model->GetModelInfo();
}