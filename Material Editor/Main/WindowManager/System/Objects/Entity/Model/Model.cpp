#include "Model.h"

bool Model::Initialize(
	ID3D11Device* device,
	char* filename)
{
	if (!LoadModel(device, filename))
	{
		return false;
	}

	if (!LoadTexture(device, filename))
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

	if (m_texture)
	{
		delete m_texture;
		m_texture = 0;
	}
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

int Model::GetNumMeshes()
{
	return m_numMeshes;
}

ID3D11ShaderResourceView* Model::GetTexture()
{
	return m_texture->GetTexture();
}

bool Model::LoadModel(
	ID3D11Device* device,
	char* filename)
{
	auto assimpLoader = new AssimpLoader;

	if (!assimpLoader->LoadModel(device, filename, m_meshes, m_numMeshes))
	{
		return false;
	}

	delete assimpLoader;

	return true;
}

bool Model::LoadTexture(
	ID3D11Device* device,
	char* filename)
{
	size_t newsize = strlen("./Models/Textures/Wood.tga") + 1;

	wchar_t* file = new wchar_t[newsize];

	size_t convertedChar = 0;
	mbstowcs_s(&convertedChar, file, newsize, "./Models/Textures/Wood.tga", _TRUNCATE);

	m_texture = new Texture();

	if (!m_texture->Initialize(device, file))
	{
		return false;
	}

	return true;
}

void Model::ReleaseModel(
	int i)
{
	m_meshes[i]->Shutdown();
}