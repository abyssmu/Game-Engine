#pragma once

#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

//Links
#pragma comment(lib, "d3dcompiler.lib")

//Includes
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <fstream>

class ColorShader
{
public:
	ColorShader();
	ColorShader(const ColorShader&);
	~ColorShader();

	//Main Functions
	bool Initialize(ID3D11Device*, HWND);
	bool XM_CALLCONV Render(ID3D11DeviceContext*, int,
		DirectX::XMMATRIX, DirectX::XMMATRIX,
		DirectX::XMMATRIX);
	void Shutdown();

private:
	//Main Functions
	bool CompilerShaders(ID3D11Device*, HWND, LPCWSTR,
		LPCWSTR);
	bool CreateLayout(ID3D11Device*);
	bool CreateMatrixCB(ID3D11Device*);
	bool InitializeShader(ID3D11Device*, HWND, LPCWSTR,
		LPCWSTR);
	void OutputShaderErrorMessage(ID3D10Blob*, HWND,
		LPCWSTR);
	void RenderShader(ID3D11DeviceContext*, int);
	bool XM_CALLCONV SetShaderParameters(ID3D11DeviceContext*,
		DirectX::XMMATRIX, DirectX::XMMATRIX,
		DirectX::XMMATRIX);
	void ShutdownShader();

	//Main Variables
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11PixelShader* m_pixelShader;
	ID3D11VertexShader* m_vertexShader;

	//Utility Variables
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	//Buffers
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
};

#endif