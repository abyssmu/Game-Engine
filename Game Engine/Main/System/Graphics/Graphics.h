#pragma once

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

//Includes
#include <Windows.h>

//Class Includes
#include "ColorShader\ColorShader.h"
#include "DirectX\DirectX11.h"

//Globals
#include "..\Entity\Model\ModelInfo.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	//Main Functions
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool XM_CALLCONV Frame(float*,
		DirectX::XMMATRIX, ModelInfo*);

	//Utility Functions
	ID3D11Device* GetDevice();

private:
	//Main Functions
	bool XM_CALLCONV Render(float*,
		DirectX::XMMATRIX, ModelInfo*);
	void RenderModel(ModelInfo*);

	//Main Variables

	//Class Variables
	DirectX11* m_dX11;

	//Shader Variables
	ColorShader* m_colorShader;
};

#endif