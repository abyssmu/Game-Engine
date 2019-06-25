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
	HINSTANCE GetHInstance();
	HWND GetMain();
	bool GetMinimized();
	bool GetWorldActive();
	void Keyboard(
		RAWKEYBOARD& kB);
	void Mouse(
		RAWMOUSE& m);
	void OpenFile();
	void RegisterInput();
	void Resize();
	void ResetKeys();
	void SetLightAmbient(
		double r,
		double g,
		double b);
	void SetLightDiffuse(
		double r,
		double g,
		double b);
	void SetLightDirection(
		double x,
		double y,
		double z);
	void SetMinimized(
		bool& min);
	void SetSpecular(
		double r,
		double g,
		double b,
		double p);
	void SetWorldActive(
		int active);
	void UnregisterInput();
	void UpdateModel(
		std::string model);

private:
	std::string ConvertFilename(
		std::wstring& path);
	std::string ExtractFilename(
		std::wstring& path);
	bool InitializeInputDevice();
	bool InitializeMain();
	bool InitializeWorld();
	void ShutdownWindow();
	void SizeWorld();

	LPCSTR m_applicationName = 0;
	HINSTANCE m_hInstance = 0;

	HWND m_mainWindow = 0, m_worldWindow = 0;

	System* m_system = 0;

	bool m_minimized = false, m_worldActive = false;
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