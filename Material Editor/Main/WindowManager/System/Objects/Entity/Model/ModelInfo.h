/*
Model info header is a header containing the structs used to transfer model information between cores.
It also contains the struct for the vertex shaders.
*/

#pragma once

#include "../../../Math/MathLib.h"

#include <d3d11.h>

//Used to transfer buffers entity model to graphics
struct SubModelInfo
{
	ID3D11Buffer* vertexBuffer = 0, * indexBuffer = 0;
	unsigned int stride = 0, offset = 0;
	int indexCount = 0;
};

struct AllModelInfo
{
	MathLib::Vectors::Vector3D position = { 0, 0, 0 };
	MathLib::Vectors::Vector3D rotation = { 0, 0, 0 };
	SubModelInfo* subModelInfo = 0;
};

//Vertex information container
struct Vertex
{
	float color[4] = { 0, 0, 0, 0 };
	float normal[3] = { 0, 0, 0 };
	float position[3] = { 0, 0, 0 };
};