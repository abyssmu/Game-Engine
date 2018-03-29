#pragma once

#ifndef _ASSIMPLOADERCLASS_H_
#define _ASSIMPLOADERCLASS_H_

//Includes
#include <assimp\cimport.h>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <vector>

//Globals
#include "../Mesh/Mesh.h"
#include "../ModelInfo.h"

class AssimpLoader
{
public:
	//Default constructor
	AssimpLoader();

	//Default copy constructor
	AssimpLoader(const AssimpLoader& other);

	//Default destructor
	~AssimpLoader();

	////////Utility Functions
	//Load model from file
	bool LoadModel(ID3D11Device* device, char* filename,
					std::vector<Mesh*>& meshes, int& numMeshes);
};

#endif