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
	bool CheckSystem();
	HWND GetMain();
	bool GetMinimized();
	HWND GetWorld();
	void KeyDown(
		unsigned int key);
	void KeyUp(
		unsigned int key);
	void OpenFile();
	void SetMinimized(
		bool& min);
	void SetMouseState(
		bool state);
	void SizeControls();
	void SizeWorld();
	void UpdateModel(
		std::string model);

private:
	std::string ConvertFilename(
		std::wstring& path);
	std::string ExtractFilename(
		std::wstring& path);
	bool InitializeControlsContainer();
	bool InitializeInner();
	bool InitializeLightText();
	bool InitializeMain();
	bool InitializeTrackbar();
	bool InitializeWorld();
	void ShutdownWindow();

	LPCSTR m_applicationName = 0;
	HINSTANCE m_hInstance = 0;

	HWND m_mainWindow = 0, m_controlsContainer = 0, m_worldWindow = 0;
	HWND m_trackbar = 0, m_trackbarText = 0;
	HWND m_lightTextX = 0, m_lightTextY = 0, m_lightTextZ = 0;
	HWND m_lightInputX = 0, m_lightInputY = 0, m_lightInputZ = 0;

	System* m_system = 0;

	bool m_minimized = false, m_mouseState = true;
	int m_screenHeight = 0, m_screenWidth = 0;
	int m_worldHeight = 0, m_worldWidth = 0;
	double m_worldPerc = 0.8;
};

extern LRESULT CALLBACK ControlsMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam);
extern LRESULT CALLBACK MainMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam);
extern LRESULT CALLBACK WorldMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam);
extern WindowManager* ApplicationHandle;