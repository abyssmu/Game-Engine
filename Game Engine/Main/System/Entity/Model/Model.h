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
	Model();
	Model(const Model&);
	~Model();

	//Main Functions
	bool Initialize(ID3D11Device*, char*);
	void Shutdown();

	//Utility Functions
	int GetNumMeshes();

	//Class Functions
	ModelInfo* GetModelInfo(int);

private:
	//Utility Functions
	bool LoadModel(ID3D11Device*, char*);
	void ReleaseModel(int);

	//Utility Variables
	int m_numMeshes;

	//Class Variables
	std::vector<Mesh*> m_meshes;
};

#endif