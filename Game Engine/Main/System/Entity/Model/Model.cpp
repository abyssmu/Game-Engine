#include "Model.h"

Model::Model()
{
	m_indexBuffer = 0;
	m_vertexBuffer = 0;

	m_modelColor = 0;
	m_modelInfo = 0;
}

Model::Model(const Model& other)
{}

Model::~Model()
{}

bool Model::Initialize(ID3D11Device* device)
{
	bool result;

	//Load model data
	result = LoadModel();
	if (!result)
	{
		return false;
	}

	//Initialize buffers
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void Model::Shutdown()
{
	//Shutdown buffers
	ShutdownBuffers();

	//Shutdown model
	ReleaseModel();
}

ModelInfo* Model::GetModelInfo()
{
	return m_modelInfo;
}

bool Model::InitializeBuffers(ID3D11Device* device)
{
	//Setup vertex buffer
	if (!CreateVertexBuffer(device))
	{
		return false;
	}

	//Setup index buffer
	if (!CreateIndexBuffer(device))
	{
		return false;
	}

	SetModelInfo();

	return true;
}

void Model::SetModelInfo()
{
	m_modelInfo = new ModelInfo;

	m_modelInfo->indexBuffer = m_indexBuffer;
	m_modelInfo->vertexBuffer = m_vertexBuffer;
	m_modelInfo->stride = sizeof(VertexTypeColor);
	m_modelInfo->offset = 0;
	m_modelInfo->indexCount = m_indexCount;
}

void Model::ShutdownBuffers()
{
	//Shutdown index buffer
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	//Shutdown vertex buffer
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool Model::CreateIndexBuffer(ID3D11Device* device)
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
	indexData.pSysMem = m_indices;
	indexData.SysMemPitch = 0;
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
bool Model::CreateVertexBuffer(ID3D11Device* device)
{
	HRESULT result;

	VertexTypeColor* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	//Create vertex array
	vertices = new VertexTypeColor[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	//Load vertex array
	for (int i = 0; i < m_vertexCount; ++i)
	{
		vertices[i].position = DirectX::XMFLOAT3(m_modelColor[i].position[0],
			m_modelColor[i].position[1], m_modelColor[i].position[2]);
		vertices[i].color = DirectX::XMFLOAT4(m_modelColor[i].color[0],
			m_modelColor[i].color[1], m_modelColor[i].color[2],
			m_modelColor[i].color[3]);
	}

	//Setup desc of static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexTypeColor) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give subresource structure pointer to vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData,
		&m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Release arrays
	delete[] vertices;
	vertices = 0;

	return true;
}

bool Model::LoadModel()
{
	m_vertexCount = 4;

	m_modelColor = new ModelTypeColor[m_vertexCount];

	m_modelColor[0].position[0] = -1.0f;
	m_modelColor[0].position[1] = 1.0f;
	m_modelColor[0].position[2] = 0.0f;

	m_modelColor[1].position[0] = 1.0f;
	m_modelColor[1].position[1] = 1.0f;
	m_modelColor[1].position[2] = 0.0f;

	m_modelColor[2].position[0] = 1.0f;
	m_modelColor[2].position[1] = -1.0f;
	m_modelColor[2].position[2] = 0.0f;

	m_modelColor[3].position[0] = -1.0f;
	m_modelColor[3].position[1] = -1.0f;
	m_modelColor[3].position[2] = 0.0f;

	for (int i = 0; i < m_vertexCount; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_modelColor[i].color[j] = 0.5f;
		}
		m_modelColor[i].color[3] = 1.0f;
	}

	m_indexCount = 6;

	m_indices = new unsigned long[m_indexCount];
	m_indices[0] = 0;
	m_indices[1] = 2;
	m_indices[2] = 3;
	m_indices[3] = 0;
	m_indices[4] = 1;
	m_indices[5] = 2;

	return true;
}

void Model::ReleaseModel()
{
	//Shutdown model
	if (m_modelColor)
	{
		delete[] m_modelColor;
		m_modelColor = 0;
	}
}