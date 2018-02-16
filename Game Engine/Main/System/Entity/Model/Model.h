#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

//Includes
#include <DirectXMath.h>
#include <d3d11.h>
#include <fstream>

//Class Includes

//Globals
#include "ModelInfo.h"

class Model
{
public:
	Model();
	Model(const Model&);
	~Model();

	//Main Functions
	bool Initialize(ID3D11Device*);
	void Shutdown();

	//Utility Functions

	//Class Functions
	ModelInfo* GetModelInfo();

private:
	//Main Functions
	bool InitializeBuffers(ID3D11Device*);
	void SetModelInfo();
	void ShutdownBuffers();

	//Utility Functions
	bool CreateIndexBuffer(ID3D11Device*);
	bool CreateVertexBuffer(ID3D11Device*);
	bool LoadModel();
	void ReleaseModel();

	//Main Variables
	int m_vertexCount, m_indexCount;
	unsigned long* m_indices;

	//Utility Variables
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;

	//Structs
	struct VertexTypeColor
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	struct ModelTypeColor
	{
		float position[3];
		float color[4];
	};

	//Struct Variables
	ModelTypeColor* m_modelColor;
	ModelInfo* m_modelInfo;	
};

#endif