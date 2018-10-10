/*
Model class is used as a container for the mesh information. It initializes the meshes by interfacing with the
Assimp library via the assimp class. It also creates and returns the model info used by other cores.
*/

#pragma once

//Includes
#include <DirectXMath.h>
#include <d3d11.h>
#include <fstream>
#include <vector>

//Class Includes
#include "AssimpLoader\AssimpLoader.h"
#include "Mesh\Mesh.h"

//Globals
#include "ModelInfo.h"

class Model
{
public:
	//Default constructor
	Model();

	//Default copy constructor
	Model(const Model& other);

	//Default destructor
	~Model();

	////////Main Functions
	//Initialize model components
	bool Initialize(ID3D11Device* device, char* filename);

	//Shutdown model components
	void Shutdown();

	////////Utility Functions
	//Get number of meshes
	int GetNumMeshes();

	////////Class Functions
	//Get model information
	AllModelInfo* GetModelInfo(MathLib::Vectors::Vector3D position,
								MathLib::Vectors::Vector3D rotation, int i);

private:
	////////Utility Functions
	//Load model with assimp class
	bool LoadModel(ID3D11Device* device, char* filename);

	//Release model meshes
	void ReleaseModel(int i);

	////////Utility Variables
	int m_numMeshes;

	////////Class Variables
	AllModelInfo* m_allModelInfo;
	std::vector<Mesh*> m_meshes;
};