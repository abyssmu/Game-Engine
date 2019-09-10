/*
Texture shader class is used to compiler HLSL code into a DirectX11 shader.
The class compiles both pixel and vertex shaders currently. Once compiled, it is used to
transfer information to the shader for rendering.
*/

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <fstream>

class TextureShader
{
public:
	bool Initialize(
		ID3D11Device* device,
		HWND& hwnd);
	bool Render(
		ID3D11DeviceContext* deviceContext,
		int& indexCount,
		DirectX::XMMATRIX& worldMatrix,
		DirectX::XMMATRIX& viewMatrix,
		DirectX::XMMATRIX projectionMatrix,
		DirectX::XMFLOAT3 lightDirection,
		DirectX::XMFLOAT4 ambientColor,
		DirectX::XMFLOAT4 diffuseColor,
		DirectX::XMFLOAT3 cameraPosition,
		DirectX::XMFLOAT4 specularColor,
		double specularPower);
	void Shutdown();

private:
	bool CompilerShaders(
		ID3D11Device* device,
		HWND& hwnd,
		LPCWSTR& vsFilename,
		LPCWSTR& psFilename);
	bool CreateCameraCB(
		ID3D11Device* device);
	bool CreateCameraDP(
		ID3D11DeviceContext* deviceContext,
		DirectX::XMFLOAT3& cameraPosition);
	bool CreateLayout(
		ID3D11Device* device);
	bool CreateLightCB(
		ID3D11Device* device);
	bool CreateLightDP(
		ID3D11DeviceContext* deviceContext,
		DirectX::XMFLOAT4& ambientColor,
		DirectX::XMFLOAT4& diffuseColor,
		DirectX::XMFLOAT3& lightDirection,
		DirectX::XMFLOAT4& specularColor,
		double& specularPower);
	bool CreateMatrixCB(
		ID3D11Device* device);
	bool CreateMatrixDP(
		ID3D11DeviceContext* deviceContext,
		DirectX::XMMATRIX& worldMatrix,
		DirectX::XMMATRIX& viewMatrix,
		DirectX::XMMATRIX& projectionMatrix);
	bool InitializeShader(
		ID3D11Device* device,
		HWND& hwnd,
		LPCWSTR& vsFilename,
		LPCWSTR& psFilename);
	void OutputShaderErrorMessage(
		ID3D10Blob* errorMessage,
		HWND& hwnd,
		LPCWSTR& shaderFile);
	void RenderShader(
		ID3D11DeviceContext* device,
		int& indexCount);
	bool SetShaderParameters(
		ID3D11DeviceContext* deviceContext,
		DirectX::XMMATRIX& worldMatrix,
		DirectX::XMMATRIX& viewMatrix,
		DirectX::XMMATRIX& projectionMatrix,
		DirectX::XMFLOAT3& lightDirection,
		DirectX::XMFLOAT4& ambientColor,
		DirectX::XMFLOAT4& diffuseColor,
		DirectX::XMFLOAT3& cameraPosition,
		DirectX::XMFLOAT4& specularColor,
		double& specularPower);
	void ShutdownShader();

	ID3D11Buffer* m_cameraBuffer = 0;
	ID3D11InputLayout* m_layout = 0;
	ID3D11Buffer* m_lightBuffer = 0;
	ID3D11Buffer* m_matrixBuffer = 0;
	ID3D11PixelShader* m_pixelShader = 0;
	ID3D11VertexShader* m_vertexShader = 0;
	ID3D10Blob* vertexShaderBuffer = 0, *pixelShaderBuffer = 0;

	struct MatrixBufferType
	{
		DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	};

	struct CameraBufferType
	{
		DirectX::XMFLOAT3 cameraPosition = DirectX::XMFLOAT3(0.0, 0.0, 0.0);
		float pad = 0.0;
	};

	struct LightBufferType
	{
		DirectX::XMFLOAT4 ambientColor = DirectX::XMFLOAT4(0.0, 0.0, 0.0, 0.0);
		DirectX::XMFLOAT4 diffuseColor = DirectX::XMFLOAT4(0.0, 0.0, 0.0, 0.0);
		DirectX::XMFLOAT3 lightDirection = DirectX::XMFLOAT3(0.0, 0.0, 0.0);
		float specularPower = 0.0;
		DirectX::XMFLOAT4 specularColor = DirectX::XMFLOAT4(0.0, 0.0, 0.0, 0.0);
	};
};