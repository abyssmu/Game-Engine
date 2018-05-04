#include "WindowManager.h"

//Globals
bool MINIMIZED = false;

//Constructor
WindowManager::WindowManager()
{
	m_system = 0;
}

//Default copy constructor
WindowManager::WindowManager(const WindowManager& other)
{}

//Default destructor
WindowManager::~WindowManager()
{}

//Initialize window
bool WindowManager::Initialize(int screenHeight, int screenWidth)
{
	//Initialize window
	if (!InitializeWindow(screenHeight, screenWidth))
	{
		return false;
	}

	//Create and initialize system
	m_system = new System;
	if (!m_system)
	{
		return false;
	}

	if (!m_system->Initialize(screenHeight, screenWidth, m_hWnd))
	{
		return false;
	}

	return true;
}

//Shutdown window
void WindowManager::Shutdown()
{
	ShutdownWindow();
}

//Run program
void WindowManager::Run()
{
	m_system->Run(MINIMIZED);
}

//Windows message handling
LRESULT CALLBACK WindowManager::MessageHandler(HWND hwnd, UINT umsg,
	WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		//Check if a key is down
	case WM_KEYDOWN:
		m_system->KeyDown((unsigned int)wparam);
		return 0;
		//Check if a key is released
	case WM_KEYUP:
		m_system->KeyUp((unsigned int)wparam);
		//Any other messages send default
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Initialize window
bool WindowManager::InitializeWindow(int screenHeight, int screenWidth)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY, resHeight, resWidth;
	posX = posY = 0;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get instance of application
	m_hInstance = GetModuleHandle(0);

	//Give application name
	m_applicationName = "Game Engine";

	//Setup windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(0, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register window class
	RegisterClassEx(&wc);

	//Setup screen settings depending on full screen
	if (FULL_SCREEN)
	{	
		//Determine resolution of clients desktop screen
		resHeight = GetSystemMetrics(SM_CYSCREEN);
		resWidth = GetSystemMetrics(SM_CXSCREEN);

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)resWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)resHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Change display to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//Set position of window to top left corner
		posX = posY = 0;
	}
	else
	{
		//Place window in middle of screen
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//Create window with screen settings and get handle
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
		(LPCSTR)m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		posX, posY, screenWidth, screenHeight, 0, 0, m_hInstance, 0);

	//Bring window up on screen and set it as main focus
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	return true;
}

//Shutdown window
void WindowManager::ShutdownWindow()
{
	//Fix display settings if in full screen
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(0, 0);
	}

	//Remove window
	DestroyWindow(m_hWnd);
	m_hWnd = 0;

	//Remove application instance
	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = 0;

	//Release pointer to class
	ApplicationHandle = 0;
}

/////////////////////////////////////////////////////////
//Global
/////////////////////////////////////////////////////////

//Global windows message delivery
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage,
	WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		//Check if window is destroyed
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		//Check if window is closed
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		if (wparam = SIZE_MINIMIZED)
		{
			MINIMIZED = true;
		}

		if (wparam = SIZE_MAXIMIZED)
		{
			MINIMIZED = false;
		}
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage,
			wparam, lparam);
	}
}