/*
Model info header is a header containing the structs used to transfer model information between cores.
It also contains the struct for the vertex shaders.
*/

#pragma once

//Includes
#include <d3d11.h>

//Class Includes
#include "../../Math/MathLib.h"

//Used to transfer buffers entity model to graphics
//Model information container
struct SubModelInfo
{
	ID3D11Buffer* vertexBuffer, *indexBuffer;
	unsigned int stride, offset;
	int indexCount;
};

struct AllModelInfo
{
	MathLib::Vectors::Vector3D position;
	SubModelInfo* subModelInfo;
};

//Vertex information container
struct VertexColor
{
	float position[3];
	float color[4];
};