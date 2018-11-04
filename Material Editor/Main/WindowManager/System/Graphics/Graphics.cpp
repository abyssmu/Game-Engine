#include "Graphics.h"

bool Graphics::Initialize(
	int screenHeight,
	int screenWidth,
	HWND hwnd)
{
	InitializeDirectX(screenHeight, screenWidth, hwnd);
	InitializeShaders(hwnd);

	return true;
}

bool Graphics::ResetDX(
	int& screenHeight,
	int& screenWidth,
	HWND hwnd)
{
	if (!m_dX11->Resize(screenHeight, screenWidth, hwnd,
						SCREEN_DEPTH, SCREEN_NEAR))
	{
		return false;
	}

	return true;
}

void Graphics::Shutdown()
{
	if (m_colorShader)
	{
		m_colorShader->Shutdown();
		delete m_colorShader;
		m_colorShader = 0;
	}

	if (m_dX11)
	{
		m_dX11->Shutdown();
		delete m_dX11;
		m_dX11 = 0;
	}
}

bool Graphics::Frame(
	Colors::Color bgcolor,
	DirectX::XMMATRIX viewMatrix,
	AllModelInfo* modelInfo)
{
	if (!Render(bgcolor, viewMatrix, modelInfo))
	{
		return false;
	}

	return true;
}

ID3D11Device* Graphics::GetDevice()
{
	return m_dX11->GetDevice();
}

DirectX::XMMATRIX Graphics::CalculateWorld(
	AllModelInfo* modelInfo)
{
	auto translation = DirectX::XMMatrixTranslation((float)modelInfo->position.x,
		(float)modelInfo->position.y,
		(float)modelInfo->position.z);

	auto rotation = DirectX::XMMatrixRotationRollPitchYaw((float)modelInfo->rotation.x,
		(float)modelInfo->rotation.y,
		(float)modelInfo->rotation.z);
	
	//auto scale;

	//return (scale * rotation * translation);
	return (rotation * translation);
}

bool Graphics::InitializeDirectX(
	int screenHeight,
	int screenWidth,
	HWND hwnd)
{
	m_dX11 = new DirectX11;
	if (!m_dX11)
	{
		return false;
	}

	if (!m_dX11->Initialize(screenHeight, screenWidth,
		VSYNC_ENABLED, hwnd, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, "Could not initialize DX11", "Error", MB_OK);
		return false;
	}

	return true;
}

bool Graphics::InitializeShaders(
	HWND hwnd)
{
	m_colorShader = new ColorShader;
	if (!m_colorShader)
	{
		return false;
	}

	if (!m_colorShader->Initialize(m_dX11->GetDevice(), hwnd))
	{
		MessageBox(hwnd, "Could not initialize color shader.", "Error",
			MB_OK);
		return false;
	}

	return true;
}

bool Graphics::Render(
	Colors::Color bgcolor,
	DirectX::XMMATRIX viewMatrix,
	AllModelInfo* modelInfo)
{
	m_dX11->BeginScene(bgcolor);

	RenderModel(modelInfo, viewMatrix);

	m_dX11->EndScene();

	return true;
}

bool Graphics::RenderModel(
	AllModelInfo* modelInfo,
	DirectX::XMMATRIX viewMatrix)
{
	auto world = CalculateWorld(modelInfo);

	if (!m_colorShader->Render(m_dX11->GetDeviceContext(),
		modelInfo->subModelInfo->indexCount, world,
		viewMatrix, m_dX11->GetProjectionMatrix()))
	{
		return false;
	}

	m_dX11->GetDeviceContext()->IASetVertexBuffers(0, 1,
		&modelInfo->subModelInfo->vertexBuffer, &modelInfo->subModelInfo->stride,
		&modelInfo->subModelInfo->offset);

	m_dX11->GetDeviceContext()->IASetIndexBuffer(modelInfo->subModelInfo->indexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	m_dX11->GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}