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
	AssimpLoader();
	AssimpLoader(const AssimpLoader&);
	~AssimpLoader();

	//Utility Functions
	bool LoadModel(ID3D11Device*, char*, std::vector<Mesh*>&, int&);
};

#endif