/*
DirectX11 class is an interface class that connects with the DirectX11 library.
It is used to initialize and maintain communications with DirectX
*/

#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

#include "..\..\Color\Color.h"

#include <DirectXMath.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgi.h>

class DirectX11
{
public:
	bool Initialize(int screenHeight, int screenWidth, bool vsync,
		HWND hwnd, double screenDepth, double screenNear);
	bool Resize(int& screenHeight, int& screenWidth, HWND hwnd, double screenDepth,
				double screenNear);
	void Shutdown();

	void BeginScene(Colors::Color bgcolor);
	void EndScene();
	DirectX::XMMATRIX GetOrthoMatrix();
	DirectX::XMMATRIX GetProjectionMatrix();
	void GetVideoCardInfo(char* cardName, int& memory);
	DirectX::XMMATRIX GetWorldMatrix();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	bool CreateAdapterDesc(int screenHeight, int screenWidth,
						unsigned int& numerator, unsigned int& denominator);
	bool CreateDepthBuffer(int screenHeight, int screenWidth);
	bool CreateDepthStencilState();
	bool CreateDepthStencilView();
	bool CreateMatrices(int screenHeight, int screenWidth, double fieldOfView,
						double screenAspect, double screenDepth, double screenNear);
	bool CreateRasterDesc();
	bool CreateSwapChain(int screenHeight, int screenWidth,	unsigned int numerator,
						unsigned int denominator, HWND hwnd);
	bool CreateViewport(int screenHeight, int screenWidth, double& fieldOfView,
						double& screenAspect);
	bool InitializeDirectX(int screenHeight, int screenWidth, HWND hwnd);
	bool InitializeMatrices(int screenHeight, int screenWidth, double screenDepth,
							double screenNear);
	bool RecreateRenderTarget();

	char m_videoCardDescription[128] = { 0 };
	int m_videoCardMemory = 0;
	bool m_vSyncEnabled = false;

	ID3D11Texture2D* m_depthStencilBuffer = 0;
	ID3D11DepthStencilState* m_depthStencilState = 0;
	ID3D11DepthStencilView* m_depthStencilView = 0;
	ID3D11Device* m_device = 0;
	ID3D11DeviceContext* m_deviceContext = 0;
	DirectX::XMMATRIX m_orthoMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX m_projectionMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX m_worldMatrix = DirectX::XMMatrixIdentity();
	ID3D11RasterizerState* m_rasterState = 0;
	ID3D11RenderTargetView* m_renderTargetView = 0;
	IDXGISwapChain* m_swapChain = 0;
};