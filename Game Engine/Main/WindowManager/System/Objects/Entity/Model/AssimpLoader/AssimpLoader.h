/*
Assimp loader class is used to interface with the assimp library. It loads the model and returns the
vector of submeshes and number of meshes.
*/

#pragma once

#include "../Mesh/Mesh.h"
#include "../ModelInfo.h"

#include <assimp\cimport.h>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <vector>

class AssimpLoader
{
public:
	bool LoadModel(
		ID3D11Device* device,
		char* filename,
		std::vector<Mesh*>& meshes,
		int& numMeshes);

private:
	bool LoadIndices(
		Mesh* meshes,
		aiMesh* mesh);
	bool LoadVertices(
		Mesh* meshes,
		aiMesh* mesh);
};