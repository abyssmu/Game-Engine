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
	Mesh();
	Mesh(const Mesh&);
	~Mesh();

	//Main Functions
	bool Initialize(ID3D11Device*);
	void Shutdown();

	//Utility Functions
	void SetIndexCount(unsigned int);
	void SetIndices(std::vector<unsigned long>);
	void SetVertexCount(unsigned int);
	void SetVertices(std::vector<VertexTypeColor*>);

	//Struct Functions
	ModelInfo* GetModelInfo();
	std::vector<VertexTypeColor*>& GetVertices();

private:
	//Main Functions
	bool InitializeBuffers(ID3D11Device*);
	void SetModelInfo();
	void ShutdownBuffers();

	//Utility Functions
	bool CreateIndexBuffer(ID3D11Device*);
	bool CreateVertexBuffer(ID3D11Device*);
	void ReleaseMesh();

	//Main Variables
	int m_vertexCount, m_indexCount;
	unsigned long* m_indices;

	//Class Variables
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;

	//Struct Variables
	std::vector<VertexTypeColor*> m_vertices;
	ModelInfo* m_modelInfo;
};

#endif