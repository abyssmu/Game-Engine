/*
DirectX11 class is an interface class that connects with the DirectX11 library.
It is used to initialize and maintain communications with DirectX
*/

#pragma once

//Links
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

//Includes
#include <DirectXMath.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgi.h>

//Class Includes
#include "../../Color/Color.h"

class DirectX11
{
public:
	//Constructor
	DirectX11();

	//Default copy constructor
	DirectX11(const DirectX11& other);

	//Default destructor
	~DirectX11();

	////////Main Functions
	//Initialize components
	bool Initialize(int screenHeight, int screenWidth, bool vsync,
		HWND hwnd, bool fullscreen, double screenDepth, double screenNear);

	//Reset DirectX if resolution changed
	bool Resize(int& screenHeight, int& screenWidth, HWND hwnd, double screenDepth,
				double screenNear);

	//Shutdown components
	void Shutdown();

	////////Utility Functions
	//Clear render target to begin scene
	void BeginScene(Colors::Color bgcolor);

	//Present screen to scene
	void EndScene();

	//Get orthogonal matrix
	DirectX::XMMATRIX GetOrthoMatrix();

	//Get projection matrix
	DirectX::XMMATRIX GetProjectionMatrix();

	//Get video card information
	void GetVideoCardInfo(char* cardName, int& memory);

	//Get world matrix
	DirectX::XMMATRIX GetWorldMatrix();

	////////Class Functions
	//Get DirectX device
	ID3D11Device* GetDevice();

	//Get DirectX device context
	ID3D11DeviceContext* GetDeviceContext();

private:
	////////Main Functions
	//Create adapter and factory to get video card and
	//display monitor information
	bool CreateAdapterDesc(int screenHeight, int screenWidth,
						unsigned int& numerator, unsigned int& denominator);

	//Create depth buffer
	bool CreateDepthBuffer(int screenHeight, int screenWidth);

	//Create depth stencil state
	bool CreateDepthStencilState();

	//Create depth stencil view
	bool CreateDepthStencilView();

	//Create all matrices
	bool CreateMatrices(int screenHeight, int screenWidth, double fieldOfView,
						double screenAspect, double screenDepth, double screenNear);

	//Create rasterizer description
	bool CreateRasterDesc();

	//Create swap chain
	bool CreateSwapChain(int screenHeight, int screenWidth,	unsigned int numerator,
						unsigned int denominator, HWND hwnd, bool fullscreen);
	
	//Create viewport
	bool CreateViewport(int screenHeight, int screenWidth, double& fieldOfView,
						double& screenAspect);

	//Initialize DirectX components
	bool InitializeDirectX(int screenHeight, int screenWidth, HWND hwnd,
							bool fullscreen);

	//Initialize matrix components
	bool InitializeMatrices(int screenHeight, int screenWidth, double screenDepth,
							double screenNear);

	//Recreate render target view
	bool RecreateRenderTarget();

	////////Main Variables
	char m_videoCardDescription[128];
	int m_videoCardMemory;
	bool m_vSyncEnabled;

	////////Class Variables
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	DirectX::XMMATRIX m_orthoMatrix, m_projectionMatrix, m_worldMatrix;
	ID3D11RasterizerState* m_rasterState;
	ID3D11RenderTargetView* m_renderTargetView;
	IDXGISwapChain* m_swapChain;
};