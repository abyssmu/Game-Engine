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
	//Constructor
	Graphics();

	//Default copy constructor
	Graphics(const Graphics& other);

	//Default destructor
	~Graphics();

	////////Main Functions
	//Initialize components
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

	//Shutdown components
	void Shutdown();

	//Graphical frame processing
	bool Frame(float* bgcolor, DirectX::XMMATRIX viewMatrix,
		ModelInfo* modelInfo);

	////////Utility Functions
	//Get DirectX device
	ID3D11Device* GetDevice();

private:
	////////Main Functions
	//Render model to scene and present scene
	bool Render(float* bgcolor, DirectX::XMMATRIX viewMatrix,
		ModelInfo* modelInfo);
	
	//Put model information on pipeline
	void RenderModel(ModelInfo* modelInfo);

	////////Main Variables

	////////Class Variables
	DirectX11* m_dX11;

	////////Shader Variables
	ColorShader* m_colorShader;
};

#endif