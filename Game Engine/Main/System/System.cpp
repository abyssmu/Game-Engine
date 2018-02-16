//Includes
#include <vector>
#include <string>
#include <fstream>

//Class Includes
#include "System.h"

SystemClass::SystemClass()
{
	m_camera = 0;
	m_entities = 0;
	m_graphics = 0;
	m_input = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{}

SystemClass::~SystemClass()
{}

bool SystemClass::Initialize()
{
	bool result = false;

	//Initialize width and height of screen
	screenWidth = 0;
	screenHeight = 0;

	//Initialize windows API
	InitializeWindows(screenWidth, screenHeight);

	//Create and initialize graphics
	m_graphics = new Graphics;
	if (!m_graphics)
	{
		return false;
	}

	m_graphics->Initialize(screenWidth, screenHeight,
		m_hWnd);

	//Create and initialize camera
	m_camera = new Camera;
	if (!m_camera)
	{
		return false;
	}

	float pos[3] = { 0.0f, 0.0f, -10.0f };
	m_camera->SetPosition(pos);
	m_camera->Render();

	//Create and initialize entities
	m_entities = new Entity;
	if (!m_entities)
	{
		return false;
	}

	result = m_entities->Initialize(m_graphics->GetDevice());
	if (!result)
	{
		return false;
	}

	//Create and initialize input
	m_input = new Input;
	if (!m_input)
	{
		return false;
	}

	m_input->Initialize();

	return true;
}

void SystemClass::Shutdown()
{
	//Shutdown graphics
	if (m_graphics)
	{
		m_graphics->Shutdown();
		delete m_graphics;
		m_graphics = 0;
	}

	//Shutdown input
	if (m_input)
	{
		delete m_input;
		m_input = 0;
	}

	//Shutdown window
	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;
	done = result = false;

	//Initialize message structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until msg == quit
	while (!done)
	{
		//Handle windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

bool SystemClass::Frame()
{
	bool result = false;
	Entity* entities = 0;
	float bgcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	result = m_input->ProcessQuit();
	if (!result)
	{
		return false;
	}

	m_camera->Render();

	result = m_graphics->Frame(bgcolor, m_camera->GetViewMatrix(),
		m_entities->GetModelInfo());
	if (!result)
	{
		return false;
	}

	delete entities;

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg,
	WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	//Check if a key is down
	case WM_KEYDOWN:
		m_input->KeyDown((unsigned int)wparam);
		return 0;
	//Check if a key is released
	case WM_KEYUP:
		m_input->KeyUp((unsigned int)wparam);
	//Any other messages send default
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	posX = posY = 0;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get instance of application
	m_hInstance = GetModuleHandle(NULL);

	//Give application name
	m_applicationName = L"Game Engine";

	//Setup windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Regist window class
	RegisterClassEx(&wc);

	//Determine resolution of clients desktop screen
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Setup screen settings depending on full screen
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Change display to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//Set position of window to top left corner
		posX = posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		//Place window in middle of screen
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//Create window with screen settings and get handle
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_applicationName, 
		(LPCSTR)m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, 
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

	//Bring window up on screen and set it as main focus
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void SystemClass::ShutdownWindows()
{
	//Fix display settings if in full screen
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//Remove window
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	//Remove application instance
	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = NULL;

	//Release pointer to class
	ApplicationHandle = NULL;
}

/////////////////////////////////////////////////////////
//Global
/////////////////////////////////////////////////////////

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
	default:
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}