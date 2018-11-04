/*
Color shader class is used to compiler HLSL code into a DirectX11 shader.
The class compiles both pixel and vertex shaders currently. Once compiled, it is used to
transfer information to the shader for rendering.
*/

#pragma once
#pragma comment(lib, "d3dcompiler.lib")

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <fstream>

class ColorShader
{
public:
	bool Initialize(
		ID3D11Device* device,
		HWND hwnd);
	bool Render(
		ID3D11DeviceContext* deviceContext,
		int indexCount,
		DirectX::XMMATRIX worldMatrix,
		DirectX::XMMATRIX viewMatrix,
		DirectX::XMMATRIX projectionMatrix);
	void Shutdown();

private:
	bool CompilerShaders(
		ID3D11Device* device,
		HWND hwnd,
		LPCWSTR vsFilename,
		LPCWSTR psFilename);
	bool CreateLayout(
		ID3D11Device* device);
	bool CreateMatrixCB(
		ID3D11Device* device);
	bool InitializeShader(
		ID3D11Device* device,
		HWND hwnd,
		LPCWSTR vsFilename,
		LPCWSTR psFilename);
	void OutputShaderErrorMessage(
		ID3D10Blob* errorMessage,
		HWND hwnd,
		LPCWSTR shaderFile);
	void RenderShader(
		ID3D11DeviceContext* device,
		int indexCount);
	bool SetShaderParameters(
		ID3D11DeviceContext* deviceContext, 
		DirectX::XMMATRIX worldMatrix,
		DirectX::XMMATRIX viewMatrix,
		DirectX::XMMATRIX projectionMatrix);
	void ShutdownShader();

	ID3D11InputLayout* m_layout = 0;
	ID3D11Buffer* m_matrixBuffer = 0;
	ID3D11PixelShader* m_pixelShader = 0;
	ID3D11VertexShader* m_vertexShader = 0;
	ID3D10Blob* vertexShaderBuffer = 0, * pixelShaderBuffer = 0;

	struct MatrixBufferType
	{
		DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	};
};