/*
Graphics class is a manager for the graphics core. It holds the DirectX class and the shader classes.
*/

#pragma once

//Includes
#include <Windows.h>

//Class Includes
#include "../Color/Color.h"
#include "ColorShader\ColorShader.h"
#include "DirectX\DirectX11.h"

//Globals
#include "..\Entity\Model\ModelInfo.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const double SCREEN_DEPTH = 1000.0;
const double SCREEN_NEAR = 0.1;

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

	//Reset DirectX if resolution changed
	bool ResetDX(int& screenWidth, int& screenHeight, HWND hwnd);

	//Shutdown components
	void Shutdown();

	//Graphical frame processing
	bool Frame(Colors::Color bgcolor, DirectX::XMMATRIX viewMatrix,
		AllModelInfo* modelInfo);

	////////Utility Functions
	//Get DirectX device
	ID3D11Device* GetDevice();

private:
	////////Main Functions
	//Calculate world matrix
	void CalculateWorld(DirectX::XMMATRIX& world, AllModelInfo* modelInfo);

	//Initialize DirectX
	bool InitializeDirectX(int screenWidth, int screenHeight, HWND hwnd);

	//Initialize shaders
	bool InitializeShaders(HWND hwnd);

	//Render model to scene and present scene
	bool Render(Colors::Color bgcolor, DirectX::XMMATRIX viewMatrix,
		AllModelInfo* modelInfo);
	
	//Put model information on pipeline
	bool RenderModel(AllModelInfo* modelInfo, DirectX::XMMATRIX viewMatrix);

	////////Class Variables
	DirectX11* m_dX11;

	////////Shader Variables
	ColorShader* m_colorShader;
};