/*
WindowManager class is used as a manager for the window display.
It holds the program manager and transfers information from there to the display.
*/

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "MenuResource.h"
#include "System\System.h"

#include <ShObjIdl.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

class WindowManager
{
public:
	bool Initialize(
		int screenHeight,
		int screenWidth);
	void Shutdown();
	void Run();

	bool CheckResizeWindow();
	HWND GetWorld();
	LRESULT CALLBACK MainMessageHandler(
		HWND hwnd,
		UINT umsg,
		WPARAM wparam,
		LPARAM lparam);
	LRESULT CALLBACK WorldMessageHandler(
		HWND hwnd,
		UINT umsg,
		WPARAM wparam,
		LPARAM lparam);
	bool PassGo();
	void SizeWorld();
	void UpdateModel(
		std::string modelName);

private:
	bool InitializeInner();
	bool InitializeMain();
	bool InitializeWorld();
	void ShutdownWindow();

	LPCSTR m_applicationName = 0;
	HINSTANCE m_hInstance = 0;
	HWND m_mainWindow = HWND(0), m_worldWindow = HWND(0);

	System* m_system = 0;

	bool go = false;
	int m_screenHeight = 0, m_screenWidth = 0;
	int m_worldHeight = 0, m_worldWidth = 0;
};

static LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam);
static WindowManager* ApplicationHandle = 0;