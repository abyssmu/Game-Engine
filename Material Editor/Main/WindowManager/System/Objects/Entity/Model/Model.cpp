#include "Model.h"

bool Model::Initialize(
	ID3D11Device* device,
	char* filename)
{
	if (!LoadModel(device, filename))
	{
		return false;
	}

	m_allModelInfo = new AllModelInfo;

	return true;
}

void Model::Shutdown()
{
	for (auto i = 0; i < m_numMeshes; ++i)
	{
		ReleaseModel(i);
	}

	if (m_allModelInfo)
	{
		delete m_allModelInfo;
		m_allModelInfo = 0;
	}
}

int Model::GetNumMeshes()
{
	return m_numMeshes;
}

AllModelInfo* Model::GetModelInfo(
	MathLib::Vectors::Vector3D position,
	MathLib::Vectors::Vector3D rotation,
	int i)
{
	m_allModelInfo->position = position;
	m_allModelInfo->rotation = rotation;
	m_allModelInfo->subModelInfo = m_meshes[i]->GetModelInfo();

	return m_allModelInfo;
}

bool Model::LoadModel(
	ID3D11Device* device,
	char* filename)
{
	auto assimpLoader = new AssimpLoader;

	assimpLoader->LoadModel(device, filename, m_meshes, m_numMeshes);

	delete assimpLoader;

	return true;
}

void Model::ReleaseModel(
	int i)
{
	m_meshes[i]->Shutdown();
}