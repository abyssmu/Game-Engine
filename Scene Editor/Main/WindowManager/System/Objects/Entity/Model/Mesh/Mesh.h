/*
Mesh class is used to store all mesh data. It stores all vertex information in VertexType as well as the
vertex buffer, vertex count, index buffer, index count, and index array.
*/

#pragma once

#include "../ModelInfo.h"

#include <d3d11.h>
#include <vector>

class Mesh
{
public:
	bool Initialize(
		ID3D11Device* device);
	void Shutdown();

	void SetIndexCount(
		unsigned int numindices);
	void SetIndices(
		std::vector<unsigned long> inds);
	void SetVertexCount(
		unsigned int numVerts);
	void SetVertices(
		std::vector<VertexColor*> verts);

	SubModelInfo* GetModelInfo();
	std::vector<VertexColor*>& GetVertices();

private:
	bool InitializeBuffers(
		ID3D11Device* device);
	void SetModelInfo();
	void ShutdownBuffers();
	bool CreateIndexBuffer(
		ID3D11Device* device);
	bool CreateVertexBuffer(
		ID3D11Device* device);
		void ReleaseMesh();

	int m_vertexCount = 0, m_indexCount = 0;
	unsigned long* m_indices = 0;

	ID3D11Buffer* m_vertexBuffer = 0, * m_indexBuffer = 0;
	std::vector<VertexColor*> m_vertices = { 0 };
	SubModelInfo* m_modelInfo = 0;
};