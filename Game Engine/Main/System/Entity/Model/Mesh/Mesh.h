#pragma once

#ifndef _MESHCLASS_H_
#define _MESHCLASS_H_

//Includes
#include <d3d11.h>
#include <vector>

//Class Includes
#include "../ModelInfo.h"

class Mesh
{
public:
	//Constructor
	Mesh();

	//Default copy constructor
	Mesh(const Mesh& other);

	//Default destructor
	~Mesh();

	////////Main Functions
	//Initialize mesh
	bool Initialize(ID3D11Device* device);

	//Shutdown mesh
	void Shutdown();

	////////Utility Functions
	//Set index count
	void SetIndexCount(unsigned int numindices);

	//Set indices
	void SetIndices(std::vector<unsigned long> inds);

	//Set vertex count
	void SetVertexCount(unsigned int numVerts);

	//Set vertices
	void SetVertices(std::vector<VertexTypeColor*> verts);

	////////Struct Functions
	//Get model information
	ModelInfo* GetModelInfo();

	//Get vertices
	std::vector<VertexTypeColor*>& GetVertices();

private:
	////////Main Functions
	//Initialize buffers
	bool InitializeBuffers(ID3D11Device* device);

	//Set model information
	void SetModelInfo();

	//Shutdown buffers
	void ShutdownBuffers();

	////////Utility Functions
	//Create index buffer
	bool CreateIndexBuffer(ID3D11Device* device);

	//Create vertex buffer
	bool CreateVertexBuffer(ID3D11Device* device);
	
	//Release mesh information
	void ReleaseMesh();

	////////Main Variables
	int m_vertexCount, m_indexCount;
	unsigned long* m_indices;

	////////Class Variables
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;

	////////Struct Variables
	std::vector<VertexTypeColor*> m_vertices;
	ModelInfo* m_modelInfo;
};

#endif