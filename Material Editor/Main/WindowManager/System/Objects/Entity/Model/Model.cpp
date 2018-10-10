#include "Model.h"

//Default constructor
Model::Model()
{
	m_allModelInfo = new AllModelInfo;
}

//Default copy constructor
Model::Model(const Model& other)
{}

//Default destructor
Model::~Model()
{}

//Initialize model components
bool Model::Initialize(ID3D11Device* device, char* filename)
{
	//Load model data
	if (!LoadModel(device, filename))
	{
		return false;
	}

	return true;
}

//Shutdown model components
void Model::Shutdown()
{
	for (int i = 0; i < m_numMeshes; ++i)
	{
		//Shutdown model
		ReleaseModel(i);
	}
}

//Get number of meshes
int Model::GetNumMeshes()
{
	return m_numMeshes;
}

//Get model information
AllModelInfo* Model::GetModelInfo(MathLib::Vectors::Vector3D position,
									MathLib::Vectors::Vector3D rotation, int i)
{
	m_allModelInfo->position = position;
	m_allModelInfo->rotation = rotation;
	m_allModelInfo->subModelInfo = m_meshes[i]->GetModelInfo();

	return m_allModelInfo;
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Load model with assimp class
bool Model::LoadModel(ID3D11Device* device, char* filename)
{
	AssimpLoader* assimpLoader = new AssimpLoader;

	assimpLoader->LoadModel(device, filename, m_meshes, m_numMeshes);

	delete assimpLoader;

	return true;
}

//Release model meshes
void Model::ReleaseModel(int i)
{
	m_meshes[i]->Shutdown();
}