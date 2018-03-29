#pragma once

#ifndef _DIRECTX11CLASS_H_
#define _DIRECTX11CLASS_H_

//Links
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

//Includes
#include <DirectXMath.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgi.h>

//Class Includes

class DirectX11
{
public:
	//Constructor
	DirectX11();

	//Default copy constructor
	DirectX11(const DirectX11&);

	//Default destructor
	~DirectX11();

	////////Main Functions
	//Initialize components
	bool Initialize(int screenWidth, int screenHeight, bool vsync,
		HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
	
	//Shutdown components
	void Shutdown();

	////////Utility Functions
	//Clear render target to begin scene
	void BeginScene(float bgcolor[]);

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
	bool CreateAdapterDesc(int screenWidth, int screenHeight, 
						unsigned int& numerator, unsigned int& denominator);

	//Create depth buffer
	bool CreateDepthBuffer(int screenWidth, int screenHeight);

	//Create depth stencil state
	bool CreateDepthStencilState();

	//Create depth stencil view
	bool CreateDepthStencilView();

	//Create all matrices
	bool CreateMatrices(int screenWidth, int screenHeight, float fieldOfView,
						float screenAspect, float screenDepth, float screenNear);

	//Create rasterizer description
	bool CreateRasterDesc();

	//Create swap chain
	bool CreateSwapChain(int screenWidth, int screenHeight,	unsigned int numerator,
						unsigned int denominator, HWND hwnd, bool fullscreen);
	
	//Create viewport
	bool CreateViewport(int screenWidth, int screenHeight, float& fieldOfView,
						float& screenAspect);

	////////Main Variables
	char m_videoCardDescription[128];
	int m_videoCardMemory;
	bool m_vSyncEnabled;

	////////Utility Variables

	////////Class Variables
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	DirectX::XMMATRIX m_orthoMatrix;
	DirectX::XMMATRIX m_projectionMatrix;
	ID3D11RasterizerState* m_rasterState;
	ID3D11RenderTargetView* m_renderTargetView;
	IDXGISwapChain* m_swapChain;
	DirectX::XMMATRIX m_worldMatrix;
};

#endif