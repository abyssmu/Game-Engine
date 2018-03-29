//Model class
//Container for model components

#include "Model.h"

//Default constructor
Model::Model()
{}

//Default copy constructor
Model::Model(const Model& other)
{}

//Default destructor
Model::~Model()
{}

//Initialize model components
bool Model::Initialize(ID3D11Device* device, char* filename)
{
	bool result;

	//Load model data
	result = LoadModel(device, filename);
	if (!result)
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
ModelInfo* Model::GetModelInfo(int i)
{
	return m_meshes[i]->GetModelInfo();
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