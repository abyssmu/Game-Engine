//Mesh class
//Container for mesh data

#include "Mesh.h"

//Constructor
Mesh::Mesh()
{
	m_indexBuffer = 0;
	m_vertexBuffer = 0;
}

//Default copy constructor
Mesh::Mesh(const Mesh&)
{}

//Default destructor
Mesh::~Mesh()
{}

//Initialize mesh
bool Mesh::Initialize(ID3D11Device* device)
{
	bool result = true;

	//Initialize buffers
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

//Shutdown mesh
void Mesh::Shutdown()
{
	ShutdownBuffers();
	ReleaseMesh();
}

//Set index count
void Mesh::SetIndexCount(unsigned int numIndices)
{
	m_indexCount = numIndices;
}

//Set indices
void Mesh::SetIndices(std::vector<unsigned long> inds)
{
	m_indices = new unsigned long[inds.size()];

	//Copy vector into indices array
	for (int i = 0; i < inds.size(); ++i)
	{
		m_indices[i] = inds[i];
	}
}

//Set vertex count
void Mesh::SetVertexCount(unsigned int numVerts)
{
	m_vertexCount = numVerts;
}

//Set vertices
void Mesh::SetVertices(std::vector<VertexTypeColor*> verts)
{
	m_vertices = verts;
}

//Get model info
ModelInfo* Mesh::GetModelInfo()
{
	return m_modelInfo;
}

//Get vertices
std::vector<VertexTypeColor*>& Mesh::GetVertices()
{
	return m_vertices;
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Initialize buffers
bool Mesh::InitializeBuffers(ID3D11Device* device)
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

//Set model info
void Mesh::SetModelInfo()
{
	m_modelInfo = new ModelInfo;

	m_modelInfo->indexBuffer = m_indexBuffer;
	m_modelInfo->vertexBuffer = m_vertexBuffer;
	m_modelInfo->stride = sizeof(VertexTypeColor);
	m_modelInfo->offset = 0;
	m_modelInfo->indexCount = m_indexCount;
}

//Shutdown buffers
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

//Create index buffer
bool Mesh::CreateIndexBuffer(ID3D11Device* device)
{
	HRESULT result;

	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

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

	//Create index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData,
		&m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] m_indices;
	m_indices = 0;
}

//Create vertex buffer
bool Mesh::CreateVertexBuffer(ID3D11Device* device)
{
	HRESULT result;

	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	VertexTypeColor* vertices = new VertexTypeColor[m_vertexCount];

	for (int i = 0; i < m_vertexCount; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			vertices[i].position[k] = m_vertices[i]->position[k];
		}
		for (int k = 0; k < 4; ++k)
		{
			vertices[i].color[k] = m_vertices[i]->color[k];
		}
	}

	//Setup desc of static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexTypeColor) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give subresource structure pointer to vertex data
	vertexData.SysMemPitch = 0;
	vertexData.pSysMem = vertices;
	vertexData.SysMemSlicePitch = 0;

	//Create vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData,
		&m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//Release mesh data
void Mesh::ReleaseMesh()
{
	for (int i = 0; i < m_vertexCount; ++i)
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