//System class
//Holds the cores of the game engine

//Includes
#include <vector>
#include <string>
#include <fstream>

//Class Includes
#include "System.h"

//Globals
bool MINIMIZED = false;

//Constructor
System::System()
{
	//Initialize pointers
	m_camera = 0;
	m_entities = 0;
	m_graphics = 0;
	m_input = 0;
}

//Default copy constructor
System::System(const System& other)
{}

//Default destructor
System::~System()
{}

//Initialize all cores and utilities
bool System::Initialize(int screenHeight, int screenWidth)
{
	bool result = false;

	//Initialize width and height of screen
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	//Initialize window api
	InitializeWindows();

	//Initialize graphics
	if (!InitializeGraphics())
	{
		return false;
	}

	//Initialize camera
	if (!InitializeCamera())
	{
		return false;
	}

	//Initialize entities
	if (!InitializeEntity())
	{
		return false;
	}

	//Initialize input
	if (!InitializeInput())
	{
		return false;
	}

	return true;
}

//Shutdown all cores and utilities
void System::Shutdown()
{
	//Shutdown graphics
	if (m_graphics)
	{
		m_graphics->Shutdown();
		delete m_graphics;
		m_graphics = 0;
	}

	//Shutdown entities
	if (m_entities)
	{
		m_entities->Shutdown();
		delete m_entities;
		m_entities = 0;
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

//Main program loop
void System::Run()
{
	MSG msg;
	bool done, result, firstPass;
	done = result = false;
	firstPass = true;

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

		//If message is quit
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		//Check if window size has changed then run frame
		else if (!MINIMIZED)
		{
			if (CheckResizeWindow())
			{
				result = Frame();
				if (!result)
				{
					done = true;
				}

				firstPass = false;
			}
			else if (!firstPass)
			{
				if (!m_graphics->ResetDX(m_screenWidth, m_screenHeight, m_hWnd))
				{
					done = true;
				}
			}
		}
	}
}

//Windows message handling
LRESULT CALLBACK System::MessageHandler(HWND hwnd, UINT umsg,
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

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Check for window resolution changes
bool System::CheckResizeWindow()
{
	RECT rect;

	GetWindowRect(m_hWnd, &rect);

	int dX, dY;

	dX = (rect.right - rect.left) - m_screenWidth;
	dY = (rect.bottom - rect.top) - m_screenHeight;
	
	if((dX != 0) || (dY != 0))
	{
		m_screenHeight = dY + m_screenHeight;
		m_screenWidth = dX + m_screenWidth;

		return false;
	}

	return true;
}

//Start of each frame processing
bool System::Frame()
{
	MathLib::Vectors::Vector3D force, forceC, torque;

	//Process input
	if (!ProcessInput(force, forceC, torque))
	{
		return false;
	}

	//Update camera
	UpdateCamera(force, torque);

	//Process and render scene
	ProcessGraphics();

	return true;
}

//Initialize camera
bool System::InitializeCamera()
{
	MathLib::Vectors::Vector3D position(0.0, 0.0, -10.0);
	MathLib::Vectors::Vector3D rotation(0.0, 0.0, 0.0);

	//Create and initialize camera
	m_camera = new Camera;
	if (!m_camera)
	{
		return false;
	}

	m_camera->Initialize(position, rotation);

	//Create initial view matrix
	m_camera->Render();

	return true;
}

//Initialize entities
bool System::InitializeEntity()
{
	//Create and initialize entities
	m_entities = new Entity;
	if (!m_entities)
	{
		return false;
	}

	MathLib::Vectors::Vector3D position(5.0, 0.0, 10.0);
	MathLib::Vectors::Vector3D rotation(0.0, 0.0, 0.0);
	
	if (!m_entities->Initialize(m_graphics->GetDevice(),
		position, rotation, (char*)"./Models/human.dae"))
	{
		return false;
	}

	return true;
}

//Initialize graphics
bool System::InitializeGraphics()
{
	//Create and initialize graphics
	m_graphics = new Graphics;
	if (!m_graphics)
	{
		return false;
	}

	m_graphics->Initialize(m_screenWidth, m_screenHeight,
		m_hWnd);

	return true;
}

//Initialize input
bool System::InitializeInput()
{
	//Create and initialize input
	m_input = new Input;
	if (!m_input)
	{
		return false;
	}

	m_input->Initialize();

	return true;
}

//Initialize windows handle to screen
void System::InitializeWindows()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY, resHeight, resWidth;
	posX = posY = 0;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get instance of application
	m_hInstance = GetModuleHandle(NULL);

	//Give application name
	m_applicationName = "Game Engine";

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
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register window class
	RegisterClassEx(&wc);

	//Determine resolution of clients desktop screen
	resHeight = GetSystemMetrics(SM_CYSCREEN);
	resWidth = GetSystemMetrics(SM_CXSCREEN);

	//Setup screen settings depending on full screen
	if (FULL_SCREEN)
	{
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
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, 
		(LPCSTR)m_applicationName, 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		posX, posY, m_screenWidth, m_screenHeight, NULL, NULL, m_hInstance, NULL);

	//Bring window up on screen and set it as main focus
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

//Process graphics
bool System::ProcessGraphics()
{
	double bgcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//Process and render scene
	for (int i = 0; i < m_entities->GetNumMeshes(); ++i)
	{
		if (!m_graphics->Frame(bgcolor, m_camera->GetViewMatrix(),
			m_entities->GetModelInfo(i)))
		{
			return false;
		}
	}

	return true;
}

//Process input
bool System::ProcessInput(MathLib::Vectors::Vector3D& force,
						MathLib::Vectors::Vector3D& forceC,
						MathLib::Vectors::Vector3D& torque)
{
	//Process if quit button pressed
	if (!m_input->ProcessQuit())
	{
		return false;
	}

	//Process character
	m_input->ProcessCharacter(forceC);
	m_entities->UpdatePosRot(forceC, MathLib::Vectors::Vector3D(0.0, 0.0, 0.0));

	//Process mouse
	m_input->ProcessMouse(torque);

	//Process keys
	m_input->ProcessMovement(force);

	return true;
}

//Shutdown windows
void System::ShutdownWindows()
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

//Update camera
void System::UpdateCamera(MathLib::Vectors::Vector3D force,
						MathLib::Vectors::Vector3D torque)
{
	//Set camera current view matrix
	m_camera->UpdatePosRot(force, torque);
	m_camera->Render();
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