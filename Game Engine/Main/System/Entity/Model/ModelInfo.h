#pragma once

struct ModelInfo
{
	ID3D11Buffer* vertexBuffer, *indexBuffer;
	unsigned int stride, offset;
	int indexCount;
};