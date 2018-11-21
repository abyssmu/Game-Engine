/*
Graphics class is a manager for the graphics core. It holds the DirectX class and the shader classes.
*/

#pragma once

#include "../Color/Color.h"
#include "../Objects/Light/Directional/Directional.h"
#include "DirectX\DirectX11.h"
#include "MaterialShader\MaterialShader.h"

#include "../Objects/Entity/Model/ModelInfo.h"

#include <Windows.h>

const bool VSYNC_ENABLED = true;
const double SCREEN_DEPTH = 1000.0;
const double SCREEN_NEAR = 0.1;

class Graphics
{
public:
	bool Initialize(
		int& screenHeight,
		int& screenWidth,
		HWND& hwnd);
	bool ResetDX(
		int& screenHeight,
		int& screenWidth,
		HWND& hwnd);
	void Shutdown();
	bool Frame(
		Colors::Color& bgcolor,
		DirectX::XMMATRIX viewMatrix,
		MathLib::Vectors::Vector3D cameraPosition,
		Directional* directionalLight,
		AllModelInfo* modelInfo);

	ID3D11Device* GetDevice();

private:
	DirectX::XMMATRIX CalculateWorld(
		AllModelInfo* modelInfo);
	bool InitializeDirectX(
		int& screenHeight,
		int& screenWidth,
		HWND& hwnd);
	bool InitializeShaders(
		HWND& hwnd);
	bool Render(
		Colors::Color& bgcolor,
		DirectX::XMMATRIX& viewMatrix,
		MathLib::Vectors::Vector3D& cameraPosition,
		Directional* directionalLight,
		AllModelInfo* modelInfo);
	bool RenderModel(
		AllModelInfo* modelInfo,
		MathLib::Vectors::Vector3D& cameraPosition,
		Directional* directionalLight,
		DirectX::XMMATRIX& viewMatrix);

	DirectX11* m_dX11 = 0;
	MaterialShader* m_materialShader = 0;
};