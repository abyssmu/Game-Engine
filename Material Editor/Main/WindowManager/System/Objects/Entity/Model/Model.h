/*
Model class is used as a container for the mesh information. It initializes the meshes by interfacing with the
Assimp library via the assimp class. It also creates and returns the model info used by other cores.
*/

#pragma once

#include "AssimpLoader\AssimpLoader.h"
#include "Mesh\Mesh.h"
#include "Texture\Texture.h"

#include "ModelInfo.h"

#include <DirectXMath.h>
#include <d3d11.h>
#include <fstream>
#include <vector>

class Model
{
public:
	bool Initialize(
		ID3D11Device* device,
		char* filename);
	void Shutdown();

	AllModelInfo* GetModelInfo(
		MathLib::Vectors::Vector3D position,
		MathLib::Vectors::Vector3D rotation,
		int i);
	int GetNumMeshes();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadModel(
		ID3D11Device* device,
		char* filename);
	bool LoadTexture(
		ID3D11Device* device,
		char* filename);
	void ReleaseModel(
		int i);
	int m_numMeshes = 0;

	AllModelInfo* m_allModelInfo = 0;
	std::vector<Mesh*> m_meshes;
	Texture* m_texture = 0;
};