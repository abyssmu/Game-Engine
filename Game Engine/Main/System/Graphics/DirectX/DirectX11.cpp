//DirectX Class
//Creates DirectX utilities

#include "DirectX11.h"

//Constructor
DirectX11::DirectX11()
{
	//Initialize pointers
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_rasterState = 0;
	m_renderTargetView = 0;
	m_swapChain = 0;
}

//Default copy constructor
DirectX11::DirectX11(const DirectX11& other)
{}

//Default destructor
DirectX11::~DirectX11()
{}

//Initialize components
bool DirectX11::Initialize(int screenWidth, int screenHeight,
							bool vsync, HWND hwnd, bool fullscreen,
							double screenDepth, double screenNear)
{
	//Store vsync
	m_vSyncEnabled = vsync;

	//Initialize DirectX components
	if(!InitializeDirectX(screenWidth, screenHeight, hwnd, fullscreen))
	{
		return false;
	}

	//Initialize matrix components
	if (!InitializeMatrices(screenWidth, screenHeight, screenDepth, screenNear))
	{
		return false;
	}

	return true;
}

//Reset DirectX if resolution changed
bool DirectX11::Resize(int& screenWidth, int& screenHeight, HWND hwnd, double screenDepth, double screenNear)
{
	HRESULT result;

	ID3D11RenderTargetView* nullViews[] = { NULL };

	//Clear components
	m_deviceContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, NULL);
	m_renderTargetView->Release();
	m_depthStencilView->Release();
	m_deviceContext->Flush();

	//Resize buffers in swap chain
	result = m_swapChain->ResizeBuffers(1, screenWidth, screenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	if (!FAILED(result))
	{
		//Recreate render target view
		if (!RecreateRenderTarget())
		{
			return false;
		}

		//Recreate depth buffer
		if (!CreateDepthBuffer(screenWidth, screenHeight))
		{
			return false;
		}

		//Recreate depth stencil view
		if (!CreateDepthStencilView())
		{
			return false;
		}

		//Recreate rendering viewport
		double fieldOfView, screenAspect;
		CreateViewport(screenWidth, screenHeight, fieldOfView, screenAspect);

		//Recreate matrices
		CreateMatrices(screenWidth, screenHeight, fieldOfView, screenAspect, screenDepth, screenNear);

		//Reset render target view and depth
		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	}

	return true;
}

//Shutdown components
void DirectX11::Shutdown()
{
	//Check if fullscreen
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	//Shutdown raster state
	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	//Shutdown depth stencil view
	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	//Shutdown depth stencil state
	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	//Shutdown depth stencil buffer
	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	//Shutdown render target view
	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	//Shutdown device context
	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	//Shutdown device
	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	//Shutdown swapchain
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}
}

//Clear render target to begin scene
void DirectX11::BeginScene(double bgcolor[])
{
	float bg[4] = { 0 };

	for (int i = 0; i < 4; ++i)
	{
		bg[i] = bgcolor[i];
	}

	//Clear back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, bg);

	//Clear depth buffer
	m_deviceContext->ClearDepthStencilView(m_depthStencilView,
											D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
											1.0F, 0);
}

//Present scene to screen
void DirectX11::EndScene()
{
	//Present back buffer to screen
	if (m_vSyncEnabled)
	{
		//Lock screen refresh rate
		m_swapChain->Present(1, 0);
	}
	else
	{
		//Present as fast as possible
		m_swapChain->Present(0, 0);
	}
}

//Get orthogonal matrix
DirectX::XMMATRIX DirectX11::GetOrthoMatrix()
{
	return m_orthoMatrix;
}

//Get projection matrix
DirectX::XMMATRIX DirectX11::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

//Get video card information
void DirectX11::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
}

//Get world matrix
DirectX::XMMATRIX DirectX11::GetWorldMatrix()
{
	return m_worldMatrix;
}

//Get DirectX device
ID3D11Device* DirectX11::GetDevice()
{
	return m_device;
}

//Get DirectX device context
ID3D11DeviceContext* DirectX11::GetDeviceContext()
{
	return m_deviceContext;
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Create adapter and factory to get video card information
//and display monitor information
bool DirectX11::CreateAdapterDesc(int screenWidth, int screenHeight, 
								unsigned int& numerator, unsigned int& denominator)
{
	HRESULT result;
	size_t stringLength;

	IDXGIAdapter* adapter;
	DXGI_ADAPTER_DESC adapterDesc;
	IDXGIOutput* adapterOutput;
	IDXGIFactory* factory;
	DXGI_MODE_DESC* displayModeList;

	int error;
	unsigned int numModes;

	//Create a DirectX graphics interface factory
	result = CreateDXGIFactory(__uuidof(IDXGIFactory),
								(void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	//Use factory to create an adapter to primary GPU
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	//Enumerate primary monitor
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	//Get number of modes that fit display format
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
												DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	//Create a list to hold all possible display modes
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	//Fill list
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
												DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	//Go through display modes to find matching screen width/height
	//When matched, store number for refresh rate
	for (int i = 0; i < (int)numModes; ++i)
	{
		if ((displayModeList[i].Width == (unsigned int)screenWidth) &&
			(displayModeList[i].Height == (unsigned int)screenHeight))
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	//Get GPU description
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	//Store dedicated GPU in MB
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	//Convert name of GPU to a char array
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128,
						adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	//Release display mode list;
	delete[] displayModeList;
	displayModeList = 0;

	//Release adapter output
	adapterOutput->Release();
	adapterOutput = 0;

	//Release adapter
	adapter->Release();
	adapter = 0;

	//Release factory
	factory->Release();
	factory = 0;

	return true;
}

//Create depth buffer
bool DirectX11::CreateDepthBuffer(int screenWidth, int screenHeight)
{
	HRESULT result;

	D3D11_TEXTURE2D_DESC depthBufferDesc;

	//Initialize depth buffer desc
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	//Setup depth buffer desc
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	//Create texture for depth buffer
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL,
										&m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//Create depth stencil state
bool DirectX11::CreateDepthStencilState()
{
	HRESULT result;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	//Initialize stencil state desc
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	//Setup stencil state description
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//Stencil operations if pixel faces front
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Stencil operations if pixel faces back
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Create depth stencil state
	result = m_device->CreateDepthStencilState(&depthStencilDesc,
												&m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	//Set depth stencil state
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	return true;
}

//Create depth stencil view
bool DirectX11::CreateDepthStencilView()
{
	HRESULT result;

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	//Initialize depth stencil view
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Setup depth stencil view description
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create depth stencil view
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer,
											&depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return 0;
	}

	return true;
}

//Create all matrices
bool DirectX11::CreateMatrices(int screenWidth, int screenHeight,
								double fieldOfView, double screenAspect,
								double screenDepth, double screenNear)
{
	//Create projection matrix for 3D rendering
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, screenAspect,
															screenNear, screenDepth);

	//Initialize world matrix to identity matrix
	m_worldMatrix = DirectX::XMMatrixIdentity();

	//Create an orthographic projection matrix for 2D rendering
	m_orthoMatrix = DirectX::XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight,
													screenNear, screenDepth);

	return true;
}

//Create rasterizer description
bool DirectX11::CreateRasterDesc()
{
	HRESULT result;

	D3D11_RASTERIZER_DESC rasterDesc;

	//Setup raster description which will determine polygons to be drawn
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0;

	//Create rasterizer state from description
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	//Set rasterizer state
	m_deviceContext->RSSetState(m_rasterState);

	return true;
}

//Create swap chain
bool DirectX11::CreateSwapChain(int screenWidth, int screenHeight,
								unsigned int numerator, unsigned int denominator,
								HWND hwnd, bool fullscreen)
{
	HRESULT result;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;

	//Initialize swap chain desc
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	//Set to a single back buffer
	swapChainDesc.BufferCount = 1;

	//Set width and height of back buffer
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	//Set regular 32 bit surface for back buffer
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//Set refresh rate of back buffer
	if (m_vSyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	//Set scan line ordering and scaling to unspecified
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Set usage of back buffer
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//Set handle for window
	swapChainDesc.OutputWindow = hwnd;

	//Turn multisampling off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//Set to fullscreen or windowed
	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	//Discard back buffer contents after presenting
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Don't set advanced flags
	swapChainDesc.Flags = 0;

	//Set feature level to DX11
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	//Create swap chain, Direct3D device, and device context
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
											NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION,
											&swapChainDesc, &m_swapChain, &m_device, NULL,
											&m_deviceContext);
	if (FAILED(result))
	{
		return false;
	}

	//Get pointer to back buffer
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
									(LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	//Create render target view with back buffer pointer
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL,
											&m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	//Release pointer to back buffer
	backBufferPtr->Release();
	backBufferPtr = 0;

	return true;
}

//Create viewport
bool DirectX11::CreateViewport(int screenWidth, int screenHeight,
	double& fieldOfView, double& screenAspect)
{
	D3D11_VIEWPORT viewport;

	//Set viewport for rendering
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0;
	viewport.MaxDepth = 1.0;
	viewport.TopLeftX = 0.0;
	viewport.TopLeftY = 0.0;

	//Create viewport
	m_deviceContext->RSSetViewports(1, &viewport);

	//Setup projection matrix values
	if (fieldOfView != 0)
	{
		fieldOfView = (float)DirectX::XM_PIDIV4;
	}

	if (screenAspect != 0)
	{
		screenAspect = (double)screenWidth / (double)screenHeight;
	}

	return true;
}

//Initialize DirectX components
bool DirectX11::InitializeDirectX(int screenWidth, int screenHeight, HWND hwnd,
								bool fullscreen)
{
	unsigned int denominator, numerator;

	//Setup adapter
	if (!CreateAdapterDesc(screenWidth, screenHeight,
		numerator, denominator))
	{
		return false;
	}

	//Setup swapchain
	if (!CreateSwapChain(screenWidth, screenHeight,
		numerator, denominator, hwnd, fullscreen))
	{
		return false;
	}

	//Setup depth buffer
	if (!CreateDepthBuffer(screenWidth, screenHeight))
	{
		return false;
	}

	//Setup depth stencil state
	if (!CreateDepthStencilState())
	{
		return false;
	}

	//Setup depth stencil view
	if (!CreateDepthStencilView())
	{
		return false;
	}

	//Bind render target view/depth stencil buffer to render pipeline
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView,
		m_depthStencilView);

	//Setup raster desc
	if (!CreateRasterDesc())
	{
		return false;
	}

	return true;
}

//Initialize matrix components
bool DirectX11::InitializeMatrices(int screenWidth, int screenHeight, double screenDepth,
									double screenNear)
{
	double fieldOfView, screenAspect;

	//Setup viewport
	if (!CreateViewport(screenWidth, screenHeight, fieldOfView,
		screenAspect))
	{
		return false;
	}

	//Setup matrices
	if (!CreateMatrices(screenWidth, screenHeight, fieldOfView,
		screenAspect, screenDepth, screenNear))
	{
		return false;
	}

	return true;
}

//Recreate render target
bool DirectX11::RecreateRenderTarget()
{
	HRESULT result;

	ID3D11Texture2D* backBufferPtr;

	//Get pointer to back buffer
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	//Create render target view with back buffer pointer
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL,
		&m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	//Release pointer to back buffer
	backBufferPtr->Release();
	backBufferPtr = 0;

	return true;
}