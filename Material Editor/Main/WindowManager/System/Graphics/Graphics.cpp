#include "Graphics.h"

//Constructor
Graphics::Graphics()
{
	//Initialize pointers
	m_dX11 = 0;

	m_colorShader = 0;
}

//Default copy constructor
Graphics::Graphics(const Graphics& other)
{}

//Default destructor
Graphics::~Graphics()
{}

//Initialize components
bool Graphics::Initialize(int screenHeight, int screenWidth,
	HWND hwnd)
{
	//Initialize DirectX
	InitializeDirectX(screenHeight, screenWidth, hwnd);

	//Initialize shaders
	InitializeShaders(hwnd);

	return true;
}

//Reset DirectX if resolution changed
bool Graphics::ResetDX(int& screenHeight, int& screenWidth, HWND hwnd)
{
	if (!m_dX11->Resize(screenHeight, screenWidth, hwnd,
						SCREEN_DEPTH, SCREEN_NEAR))
	{
		return false;
	}

	return true;
}

//Shutdown components
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

//Graphical frame processing
bool Graphics::Frame(Colors::Color bgcolor, DirectX::XMMATRIX viewMatrix,
					AllModelInfo* modelInfo)
{
	//Render the scene
	if (!Render(bgcolor, viewMatrix, modelInfo))
	{
		return false;
	}

	return true;
}

//Get DirectX device
ID3D11Device* Graphics::GetDevice()
{
	return m_dX11->GetDevice();
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Calculate world matrix
void Graphics::CalculateWorld(DirectX::XMMATRIX& world, AllModelInfo* modelInfo)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation((float)modelInfo->position.x,
		(float)modelInfo->position.y,
		(float)modelInfo->position.z);

	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw((float)modelInfo->rotation.x,
		(float)modelInfo->rotation.y,
		(float)modelInfo->rotation.z);
	
	//DirectX::XMMATRIX scale;

	//world = scale * rotation * translation;
	world = rotation * translation;
}

//Initialize DirectX
bool Graphics::InitializeDirectX(int screenHeight, int screenWidth, HWND hwnd)
{
	//Create and initialize DirectX11 object
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

//Initialize shaders
bool Graphics::InitializeShaders(HWND hwnd)
{
	//Create and initialize color shader
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

//Render model to scene and present scene
bool Graphics::Render(Colors::Color bgcolor, DirectX::XMMATRIX viewMatrix,
					AllModelInfo* modelInfo)
{
	//Clear buffers to begin scene
	m_dX11->BeginScene(bgcolor);

	//Render model
	RenderModel(modelInfo, viewMatrix);

	//Present rendered scene
	m_dX11->EndScene();

	return true;
}

//Put model information on pipeline
bool Graphics::RenderModel(AllModelInfo* modelInfo, DirectX::XMMATRIX viewMatrix)
{
	DirectX::XMMATRIX world;
	CalculateWorld(world, modelInfo);

	//Render model with color shader
	if (!m_colorShader->Render(m_dX11->GetDeviceContext(),
		modelInfo->subModelInfo->indexCount, world,
		viewMatrix, m_dX11->GetProjectionMatrix()))
	{
		return false;
	}

	//Set vertex buffer to active
	m_dX11->GetDeviceContext()->IASetVertexBuffers(0, 1,
		&modelInfo->subModelInfo->vertexBuffer, &modelInfo->subModelInfo->stride,
		&modelInfo->subModelInfo->offset);

	//Set index buffer to active
	m_dX11->GetDeviceContext()->IASetIndexBuffer(modelInfo->subModelInfo->indexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	//Set type of primitive
	m_dX11->GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}