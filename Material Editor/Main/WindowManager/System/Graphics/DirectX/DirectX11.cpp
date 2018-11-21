#include "DirectX11.h"

bool DirectX11::Initialize(
	int& screenHeight,
	int& screenWidth,
	bool vsync,
	HWND& hwnd,
	double screenDepth,
	double screenNear)
{
	m_vSyncEnabled = vsync;

	if(!InitializeDirectX(screenHeight, screenWidth, hwnd))
	{
		return false;
	}

	if (!InitializeMatrices(screenHeight, screenWidth, screenDepth, screenNear))
	{
		return false;
	}

	return true;
}

bool DirectX11::Resize(
	int& screenHeight,
	int& screenWidth,
	HWND& hwnd,
	double screenDepth,
	double screenNear)
{
	ID3D11RenderTargetView* noViews[] = { 0 };

	m_deviceContext->OMSetRenderTargets(ARRAYSIZE(noViews), noViews, 0);
	m_renderTargetView->Release();
	m_depthStencilView->Release();
	m_deviceContext->Flush();

	auto result = m_swapChain->ResizeBuffers(1, screenWidth, screenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	if (!FAILED(result))
	{
		if (!RecreateRenderTarget())
		{
			return false;
		}

		if (!CreateDepthBuffer(screenHeight, screenWidth))
		{
			return false;
		}

		if (!CreateDepthStencilView())
		{
			return false;
		}

		auto fieldOfView = 1.0;
		auto screenAspect = 1.0;
		CreateViewport(screenHeight, screenWidth, fieldOfView, screenAspect);
		CreateMatrices(screenHeight, screenWidth, fieldOfView, screenAspect, screenDepth, screenNear);

		m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	}

	return true;
}

void DirectX11::Shutdown()
{
	if (m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, 0);
	}

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if (m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}
}

void DirectX11::BeginScene(
	Colors::Color& bgcolor)
{
	float bg[4] = {
		(float)bgcolor.color.r,
		(float)bgcolor.color.g,
		(float)bgcolor.color.b,
		(float)bgcolor.color.a
	};

	m_deviceContext->ClearRenderTargetView(m_renderTargetView, bg);

	m_deviceContext->ClearDepthStencilView(m_depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0F, 0);
}

void DirectX11::EndScene()
{
	if (m_vSyncEnabled)
	{
		m_swapChain->Present(1, 0);
	}
	else
	{
		m_swapChain->Present(0, 0);
	}
}

DirectX::XMMATRIX DirectX11::GetOrthoMatrix()
{
	return m_orthoMatrix;
}

DirectX::XMMATRIX DirectX11::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

void DirectX11::GetVideoCardInfo(
	char* cardName,
	int& memory)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;
}

DirectX::XMMATRIX DirectX11::GetWorldMatrix()
{
	return m_worldMatrix;
}

ID3D11Device* DirectX11::GetDevice()
{
	return m_device;
}

ID3D11DeviceContext* DirectX11::GetDeviceContext()
{
	return m_deviceContext;
}

bool DirectX11::CreateAdapterDesc(
	int& screenHeight,
	int& screenWidth,
	unsigned int& numerator,
	unsigned int& denominator)
{
	IDXGIFactory* factory = 0;
	auto result = CreateDXGIFactory(__uuidof(IDXGIFactory),
								(void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	IDXGIAdapter* adapter = 0;
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	IDXGIOutput* adapterOutput = 0;
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	auto numModes = 0u;
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
												DXGI_ENUM_MODES_INTERLACED, &numModes, 0);
	if (FAILED(result))
	{
		return false;
	}

	DXGI_MODE_DESC* displayModeList = 0;
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
												DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	for (auto i = 0; i < (int)numModes; ++i)
	{
		if ((displayModeList[i].Width == (unsigned int)screenWidth) &&
			(displayModeList[i].Height == (unsigned int)screenHeight))
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	auto adapterDesc = DXGI_ADAPTER_DESC();
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	auto stringLength = size_t();
	auto error = wcstombs_s(&stringLength, m_videoCardDescription, 128,
						adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

	return true;
}

bool DirectX11::CreateDepthBuffer(
	int& screenHeight,
	int& screenWidth)
{
	auto depthBufferDesc = D3D11_TEXTURE2D_DESC();

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

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

	auto result = m_device->CreateTexture2D(&depthBufferDesc, 0,
										&m_depthStencilBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool DirectX11::CreateDepthStencilState()
{
	auto depthStencilDesc = D3D11_DEPTH_STENCIL_DESC();

	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	auto result = m_device->CreateDepthStencilState(&depthStencilDesc,
												&m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	return true;
}

bool DirectX11::CreateDepthStencilView()
{
	auto depthStencilViewDesc = D3D11_DEPTH_STENCIL_VIEW_DESC();

	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	auto result = m_device->CreateDepthStencilView(m_depthStencilBuffer,
											&depthStencilViewDesc, &m_depthStencilView);
	if (FAILED(result))
	{
		return 0;
	}

	return true;
}

bool DirectX11::CreateMatrices(
	int& screenHeight,
	int& screenWidth,
	double& fieldOfView,
	double& screenAspect,
	double& screenDepth,
	double& screenNear)
{
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH((float)fieldOfView, (float)screenAspect,
		(float)screenNear, (float)screenDepth);

	m_worldMatrix = DirectX::XMMatrixIdentity();

	m_orthoMatrix = DirectX::XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight,
		(float)screenNear, (float)screenDepth);

	return true;
}

bool DirectX11::CreateRasterDesc()
{
	auto rasterDesc = D3D11_RASTERIZER_DESC();

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

	auto result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	m_deviceContext->RSSetState(m_rasterState);

	return true;
}

bool DirectX11::CreateSwapChain(
	int& screenHeight,
	int& screenWidth,
	unsigned int& numerator,
	unsigned int& denominator,
	HWND& hwnd)
{
	auto swapChainDesc = DXGI_SWAP_CHAIN_DESC();

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

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

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	swapChainDesc.OutputWindow = hwnd;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	auto featureLevel = D3D_FEATURE_LEVEL();
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	auto result = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE,
		0, 0, &featureLevel, 1, D3D11_SDK_VERSION,
		&swapChainDesc, &m_swapChain, &m_device, 0,
		&m_deviceContext);
	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* backBufferPtr = 0;
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
									(LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	result = m_device->CreateRenderTargetView(backBufferPtr, 0,
											&m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	backBufferPtr->Release();
	backBufferPtr = 0;

	return true;
}

bool DirectX11::CreateViewport(
	int& screenHeight,
	int& screenWidth,
	double& fieldOfView,
	double& screenAspect)
{
	auto viewport = D3D11_VIEWPORT();

	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0;
	viewport.MaxDepth = 1.0;
	viewport.TopLeftX = 0.0;
	viewport.TopLeftY = 0.0;

	m_deviceContext->RSSetViewports(1, &viewport);

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

bool DirectX11::InitializeDirectX(
	int& screenHeight,
	int& screenWidth,
	HWND& hwnd)
{
	auto denominator = 0u, numerator = 0u;

	if (!CreateAdapterDesc(screenHeight, screenWidth,
		numerator, denominator))
	{
		return false;
	}

	if (!CreateSwapChain(screenHeight, screenWidth,
		numerator, denominator, hwnd))
	{
		return false;
	}

	if (!CreateDepthBuffer(screenHeight, screenWidth))
	{
		return false;
	}

	if (!CreateDepthStencilState())
	{
		return false;
	}

	if (!CreateDepthStencilView())
	{
		return false;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView,
		m_depthStencilView);

	if (!CreateRasterDesc())
	{
		return false;
	}

	return true;
}

bool DirectX11::InitializeMatrices(
	int& screenHeight,
	int& screenWidth,
	double& screenDepth,
	double& screenNear)
{
	auto fieldOfView = 1.0, screenAspect = 1.0;

	if (!CreateViewport(screenHeight, screenWidth, fieldOfView,
		screenAspect))
	{
		return false;
	}

	if (!CreateMatrices(screenHeight, screenWidth, fieldOfView,
		screenAspect, screenDepth, screenNear))
	{
		return false;
	}

	return true;
}

bool DirectX11::RecreateRenderTarget()
{
	ID3D11Texture2D* backBufferPtr = 0;

	auto result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&backBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	result = m_device->CreateRenderTargetView(backBufferPtr, 0,
		&m_renderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	backBufferPtr->Release();
	backBufferPtr = 0;

	return true;
}