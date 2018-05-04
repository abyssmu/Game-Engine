/*
Color shader class is used to compiler HLSL code into a DirectX11 shader.
The class compiles both pixel and vertex shaders currently. Once compiled, it is used to
transfer information to the shader for rendering.
*/

#pragma once

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
	//Constructor
	ColorShader();

	//Default copy constructor
	ColorShader(const ColorShader& other);

	//Default destructor
	~ColorShader();

	////////Main Functions
	//Initialize shader filenames and create shaders
	bool Initialize(ID3D11Device* device, HWND hwnd);

	//Render model with color shader
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount,
				DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix,
				DirectX::XMMATRIX projectionMatrix);

	//Shutdown shaders
	void Shutdown();

private:
	////////Main Functions
	//Compile shaders from file
	bool CompilerShaders(ID3D11Device* device, HWND hwnd,
						LPCWSTR vsFilename, LPCWSTR psFilename);

	//Create polygon layout
	bool CreateLayout(ID3D11Device* device);

	//Create constant buffer matrix
	bool CreateMatrixCB(ID3D11Device* device);

	//Initialize shaders
	bool InitializeShader(ID3D11Device* device, HWND hwnd,
		LPCWSTR vsFilename, LPCWSTR psFilename);

	//Output error messages from shader compiler
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage,
		HWND hwnd, LPCWSTR shaderFile);

	//Render model with shader
	void RenderShader(ID3D11DeviceContext* device, int indexCount);

	//Set shader parameters
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, 
							DirectX::XMMATRIX worldMatrix,
							DirectX::XMMATRIX viewMatrix,
							DirectX::XMMATRIX projectionMatrix);
	
	//Shutdown shaders
	void ShutdownShader();

	////////Main Variables
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11PixelShader* m_pixelShader;
	ID3D11VertexShader* m_vertexShader;

	////////Utility Variables
	ID3D10Blob* vertexShaderBuffer, * pixelShaderBuffer;

	////////Buffers
	struct MatrixBufferType
	{
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX world;
	};
};