#include "Entity.h"

bool Entity::Initialize(
	ID3D11Device* device,
	MathLib::Vectors::Vector3D position,
	MathLib::Vectors::Vector3D rotation,
	char* filename)
{
	m_model = new Model;
	if (!m_model)
	{
		return false;
	}

	if (!m_model->Initialize(device, filename))
	{
		return false;
	}

	SetPosition(position);
	SetRotation(rotation);

	return true;
}

void Entity::Shutdown()
{
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}
}

int Entity::GetNumMeshes()
{
	return m_model->GetNumMeshes();
}

AllModelInfo* Entity::GetModelInfo(
	int i)
{
	return m_model->GetModelInfo(GetPosition(), i);
}