#include "WindowManager.h"

//Globals
bool MINIMIZED = false;

//Constructor
WindowManager::WindowManager()
{
	m_system = 0;

	go = true;
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
	//Capture main window height and width
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	//Initialize main window
	if (!InitializeMain())
	{
		return false;
	}

	//Initialize inner windows
	if (!InitializeInner())
	{
		return false;
	}

	//Set go to false to indicate first pass complete
	go = false;

	//Create and initialize system
	m_system = new System;
	if (!m_system)
	{
		return false;
	}

	if (!m_system->Initialize(m_screenHeight, m_screenWidth, m_worldWindow))
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

//Check window resolution changes
bool WindowManager::CheckResizeWindow()
{
	RECT rect;

	GetWindowRect(m_mainWindow, &rect);

	int dX, dY;

	dX = (rect.right - rect.left) - m_screenWidth;
	dY = (rect.bottom - rect.top) - m_screenHeight;

	if ((dX != 0) || (dY != 0))
	{
		m_screenHeight = dY + m_screenHeight;
		m_screenWidth = dX + m_screenWidth;

		return false;
	}

	return true;
}

//Return world window
HWND WindowManager::GetWorld()
{
	return m_worldWindow;
}

//Main windows message handling
LRESULT CALLBACK WindowManager::MainMessageHandler(HWND hwnd, UINT umsg,
													WPARAM wparam, LPARAM lparam)
{
	//Set mouse active in world
	if (m_system)
	{
		m_system->MouseActive(false);
		m_system->ResetKeys();
	}

	switch (umsg)
	{
		//Any other messages send default
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

//World windows message handling
LRESULT CALLBACK WindowManager::WorldMessageHandler(HWND hwnd, UINT umsg,
													WPARAM wparam, LPARAM lparam)
{
	//Set mouse active in world
	if (m_system)
	{
		m_system->MouseActive(true);
	}

	switch (umsg)
	{
		//Check if a key is down
	case WM_KEYDOWN:
		m_system->KeyDown((unsigned int)wparam);
		return 0;
		//Check if a key is released
	case WM_KEYUP:
		m_system->KeyUp((unsigned int)wparam);
		return 0;	
		//Any other messages send default
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

//Check if first pass
bool WindowManager::PassGo()
{
	return go;
}

//Size world window
void WindowManager::SizeWorld()
{
	RECT rc;
	double perc;
	int height, width;

	perc = 0.15;

	//Get world window size
	GetClientRect(m_mainWindow, &rc);

	//Calculate world window height and width
	height = (int)(rc.bottom - (double)m_screenHeight * perc);
	width = (int)(rc.right - (double)m_screenWidth * perc);

	//Move world window inside main window
	MoveWindow(m_worldWindow, rc.left, rc.top, width, height, false);
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Initialize button windows
bool WindowManager::InitializeButtons()
{
	m_buttons = new HWND;

	//Create track buttons
	if (!CreateTracks(0, 1))
	{
		return false;
	}

	return true;
}

//Initialize inner windows
bool WindowManager::InitializeInner()
{
	//Initialize world window
	if (!InitializeWorld())
	{
		return false;
	}

	//Initialize button windows
	if (!InitializeButtons())
	{
		return false;
	}

	return true;
}

//Initialize main window
bool WindowManager::InitializeMain()
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
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenHeight) / 2;
	}

	//Create window with screen settings and get handle
	m_mainWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
		(LPCSTR)m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		posX, posY, m_screenWidth, m_screenHeight, 0, 0, m_hInstance, 0);

	//Bring window up on screen and set it as main focus
	ShowWindow(m_mainWindow, SW_SHOW);
	SetFocus(m_mainWindow);

	return true;
}

//Initialize world window
bool WindowManager::InitializeWorld()
{
	WNDCLASSEX wc;

	//Get instance of application
	m_hInstance = GetModuleHandle(0);

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

	//Create window with screen settings and get handle
	m_worldWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName,
		(LPCSTR)m_applicationName, WS_POPUP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, m_hInstance, 0);

	//Set main window as world window parent
	SetParent(m_worldWindow, m_mainWindow);

	//Size world window
	SizeWorld();

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
	DestroyWindow(m_mainWindow);
	m_mainWindow = 0;

	DestroyWindow(m_worldWindow);
	m_worldWindow = 0;

	//Remove application instance
	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = 0;

	//Release pointer to class
	ApplicationHandle = 0;
}

//Create track buttons
bool WindowManager::CreateTracks(int x, int y)
{
	return true;
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
		//Check for resize window
		if ((!ApplicationHandle->CheckResizeWindow()) && (!ApplicationHandle->PassGo()))
		{
			//Size world window
			ApplicationHandle->SizeWorld();
		}

		//Send message to world window
		if (GetActiveWindow() == ApplicationHandle->GetWorld())
		{
			return ApplicationHandle->WorldMessageHandler(hwnd, umessage,
				wparam, lparam);
		}

		//Send message to main window
		return ApplicationHandle->MainMessageHandler(hwnd, umessage,
			wparam, lparam);
	}
}