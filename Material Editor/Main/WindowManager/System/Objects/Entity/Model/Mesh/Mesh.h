/*
Mesh class is used to store all mesh data. It stores all vertex information in VertexType as well as the
vertex buffer, vertex count, index buffer, index count, and index array.
*/

#pragma once

//Includes
#include <d3d11.h>
#include <vector>

//Class Includes
#include "..\ModelInfo.h"

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
	void SetVertices(std::vector<VertexColor*> verts);

	////////Struct Functions
	//Get model information
	SubModelInfo* GetModelInfo();

	//Get vertices
	std::vector<VertexColor*>& GetVertices();

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
	std::vector<VertexColor*> m_vertices;
	SubModelInfo* m_modelInfo;
};