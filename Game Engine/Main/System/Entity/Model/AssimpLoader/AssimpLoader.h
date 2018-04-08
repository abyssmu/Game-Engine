/*
Assimp loader class is used to interface with the assimp library. It loads the model and returns the
vector of submeshes and number of meshes.
*/

#pragma once

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

private:
	////////Utility Functions
	//Load indices
	bool LoadIndices(std::vector<Mesh*>& meshes, aiMesh* mesh, std::uint32_t pos);

	//Load vertices
	bool LoadVertices(std::vector<Mesh*>& meshes, aiMesh* mesh, std::uint32_t pos);
};