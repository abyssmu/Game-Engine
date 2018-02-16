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
	DirectX11();
	DirectX11(const DirectX11&);
	~DirectX11();

	//Main Functions
	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	//Utility Functions
	void BeginScene(float[]);
	void EndScene();
	DirectX::XMMATRIX GetOrthoMatrix();
	DirectX::XMMATRIX GetProjectionMatrix();
	void GetVideoCardInfo(char*, int&);
	DirectX::XMMATRIX GetWorldMatrix();

	//Class Functions
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	//Main Functions
	bool CreateAdapterDesc(int, int, 
		unsigned int&, unsigned int&);
	bool CreateDepthBuffer(int, int);
	bool CreateDepthStencilState();
	bool CreateDepthStencilView();
	bool CreateMatrices(int, int, float,
		float, float, float);
	bool CreateRasterDesc();
	bool CreateSwapChain(int, int,
		unsigned int, unsigned int, HWND,
		bool);
	bool CreateViewport(int, int, float&,
		float&);

	//Main Variables
	char m_videoCardDescription[128];
	int m_videoCardMemory;
	bool m_vSyncEnabled;

	//Utility Variables

	//Class Variables
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