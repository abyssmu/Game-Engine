#pragma once

#include <d3d11.h>

//Used to transfer buffers entity model to graphics
//Model information container
struct ModelInfo
{
	ID3D11Buffer* vertexBuffer, *indexBuffer;
	unsigned int stride, offset;
	int indexCount;
};

//Vertex information container
struct VertexTypeColor
{
	float position[3];
	float color[4];
};