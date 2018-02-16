#include "Graphics.h"

Graphics::Graphics()
{
	m_dX11 = 0;

	m_colorShader = 0;
}

Graphics::Graphics(const Graphics& other)
{}

Graphics::~Graphics()
{}

bool Graphics::Initialize(int screenWidth, int screenHeight,
	HWND hwnd)
{
	bool result = false;

	//Create and initialize DirectX11 object
	m_dX11 = new DirectX11;
	if (!m_dX11)
	{
		return false;
	}

	result = m_dX11->Initialize(screenWidth, screenHeight,
		VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH,
		SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize DX11", "Error", MB_OK);
		return false;
	}

	//Create and initialize color shader
	m_colorShader = new ColorShader;
	if (!m_colorShader)
	{
		return false;
	}

	result = m_colorShader->Initialize(m_dX11->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize color shader.", "Error",
			MB_OK);
		return false;
	}

	return true;
}

void Graphics::Shutdown()
{
	//Shutdown color shader
	if (m_colorShader)
	{
		m_colorShader->Shutdown();
		delete m_colorShader;
		m_colorShader = 0;
	}

	//Shutdown dx11
	if (m_dX11)
	{
		m_dX11->Shutdown();
		delete m_dX11;
		m_dX11 = 0;
	}
}

bool XM_CALLCONV Graphics::Frame(float* bgcolor,
	DirectX::XMMATRIX viewMatrix, ModelInfo* modelInfo)
{
	bool result = false;

	result = Render(bgcolor, viewMatrix, modelInfo);
	if (!result)
	{
		return false;
	}

	return true;
}

ID3D11Device* Graphics::GetDevice()
{
	return m_dX11->GetDevice();
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

bool XM_CALLCONV Graphics::Render(float* bgcolor,
	DirectX::XMMATRIX viewMatrix, ModelInfo* modelInfo)
{
	bool result = false;

	//Clear buffers to begin scene
	m_dX11->BeginScene(bgcolor);

	//Render model
	RenderModel(modelInfo);

	//Render model with color shader
	result = m_colorShader->Render(m_dX11->GetDeviceContext(),
		modelInfo->indexCount, m_dX11->GetWorldMatrix(),
		viewMatrix, m_dX11->GetProjectionMatrix());
	if (!result)
	{
		return false;
	}

	//Present rendered scene
	m_dX11->EndScene();

	return true;
}

void Graphics::RenderModel(ModelInfo* modelInfo)
{
	//Set vertex buffer to active
	m_dX11->GetDeviceContext()->IASetVertexBuffers(0, 1,
		&modelInfo->vertexBuffer, &modelInfo->stride,
		&modelInfo->offset);

	//Set index buffer to active
	m_dX11->GetDeviceContext()->IASetIndexBuffer(modelInfo->indexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	//Set type of primitive
	m_dX11->GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}