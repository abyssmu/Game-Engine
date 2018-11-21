#include "Mesh.h"

bool Mesh::Initialize(
	ID3D11Device* device)
{
	if (!InitializeBuffers(device))
	{
		return false;
	}

	return true;
}

void Mesh::Shutdown()
{
	ShutdownBuffers();
	ReleaseMesh();
}

void Mesh::SetIndexCount(
	unsigned int numIndices)
{
	m_indexCount = numIndices;
}

void Mesh::SetIndices(
	std::vector<unsigned long> inds)
{
	m_indices = new unsigned long[inds.size()];

	for (auto i = 0; i < inds.size(); ++i)
	{
		m_indices[i] = inds[i];
	}
}

void Mesh::SetVertexCount(
	unsigned int numVerts)
{
	m_vertexCount = numVerts;
}

void Mesh::SetVertices(
	std::vector<Vertex*> verts)
{
	m_vertices = verts;
}

SubModelInfo* Mesh::GetModelInfo()
{
	return m_modelInfo;
}

std::vector<Vertex*>& Mesh::GetVertices()
{
	return m_vertices;
}

bool Mesh::InitializeBuffers(
	ID3D11Device* device)
{
	if (!CreateVertexBuffer(device))
	{
		return false;
	}

	if (!CreateIndexBuffer(device))
	{
		return false;
	}

	SetModelInfo();

	return true;
}

void Mesh::SetModelInfo()
{
	m_modelInfo = new SubModelInfo;

	m_modelInfo->indexBuffer = m_indexBuffer;
	m_modelInfo->vertexBuffer = m_vertexBuffer;
	m_modelInfo->stride = sizeof(Vertex);
	m_modelInfo->offset = 0;
	m_modelInfo->indexCount = m_indexCount;
}

void Mesh::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool Mesh::CreateIndexBuffer(
	ID3D11Device* device)
{
	auto indexBufferDesc = D3D11_BUFFER_DESC();
	auto indexData = D3D11_SUBRESOURCE_DATA();

	//Setup desc of static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give subresource structure pointer to index data
	indexData.SysMemPitch = 0;
	indexData.pSysMem = m_indices;
	indexData.SysMemSlicePitch = 0;

	auto result = device->CreateBuffer(&indexBufferDesc, &indexData,
		&m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] m_indices;
	m_indices = 0;

	return true;
}

bool Mesh::CreateVertexBuffer(
	ID3D11Device* device)
{
	auto vertices = new Vertex[m_vertexCount];

	for (auto i = 0; i < m_vertexCount; ++i)
	{
		for (auto k = 0; k < 3; ++k)
		{
			vertices[i].color[k] = m_vertices[i]->color[k];
			vertices[i].normal[k] = m_vertices[i]->normal[k];
			vertices[i].position[k] = m_vertices[i]->position[k];
		}
	}

	auto vertexBufferDesc = D3D11_BUFFER_DESC();
	auto vertexData = D3D11_SUBRESOURCE_DATA();
	
	//Setup desc of static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give subresource structure pointer to vertex data
	vertexData.SysMemPitch = 0;
	vertexData.pSysMem = vertices;
	vertexData.SysMemSlicePitch = 0;

	auto result = device->CreateBuffer(&vertexBufferDesc, &vertexData,
		&m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Mesh::ReleaseMesh()
{
	for (auto i = 0; i < m_vertexCount; ++i)
	{
		if (m_vertices[i])
		{
			delete[] m_vertices[i];
			m_vertices[i] = 0;
		}
	}

	if (m_modelInfo)
	{
		delete m_modelInfo;
		m_modelInfo = 0;
	}
}