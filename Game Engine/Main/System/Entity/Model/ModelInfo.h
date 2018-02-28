#pragma once

//Used to transfer buffers entity model to graphics
struct ModelInfo
{
	ID3D11Buffer* vertexBuffer, *indexBuffer;
	unsigned int stride, offset;
	int indexCount;
};