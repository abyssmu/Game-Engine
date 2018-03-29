#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

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
	ModelInfo* GetModelInfo(int i);

private:
	////////Utility Functions
	//Load model with assimp class
	bool LoadModel(ID3D11Device* device, char* filename);

	//Release model meshes
	void ReleaseModel(int i);

	////////Utility Variables
	int m_numMeshes;

	////////Class Variables
	std::vector<Mesh*> m_meshes;
};

#endif