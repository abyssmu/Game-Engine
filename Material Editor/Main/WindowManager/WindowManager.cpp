//Includes
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

	if (!m_system->Initialize(m_worldHeight, m_worldWidth, m_worldWindow))
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
	int dX, dY;

	GetWindowRect(m_mainWindow, &rect);

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

//Main window message handling
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
		//Just to get a warning to go away
	case 0:
		return DefWindowProc(hwnd, umsg, wparam, lparam);

		//Any other messages send default
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

//World window message handling
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

	//% of the main window
	perc = 0.8;

	//Get world window size
	GetClientRect(m_mainWindow, &rc);

	//Calculate world window height and width
	m_worldHeight = (int)(rc.bottom);
	m_worldWidth = (int)(rc.right * perc);

	//Move world window inside main window
	MoveWindow(m_worldWindow, rc.left, rc.top, m_worldWidth, m_worldHeight, false);
}

//Update model
void WindowManager::UpdateModel(std::string modelName)
{
	m_system->UpdateModel(modelName);
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

//Initialize inner windows
bool WindowManager::InitializeInner()
{
	//Initialize world window
	if (!InitializeWorld())
	{
		return false;
	}

	return true;
}

//Initialize main window
bool WindowManager::InitializeMain()
{
	WNDCLASSEX wc;
	int posX, posY;
	posX = posY = 0;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get instance of application
	m_hInstance = GetModuleHandle(0);

	//Give application name
	m_applicationName = "Material Editor";

	//Setup windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_PSI));
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_PSI));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register window class
	RegisterClassEx(&wc);

	//Setup screen settings
	//Place window in middle of screen
	posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenWidth) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenHeight) / 2;

	//Create window with screen settings and get handle
	m_mainWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		posX, posY, m_screenWidth, m_screenHeight, 0, 0, m_hInstance, 0);

	if (!m_mainWindow)
	{
		return false;
	}

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
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = 0;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register window class
	RegisterClassEx(&wc);

	//Create window with screen settings and get handle
	m_worldWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_POPUP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, m_hInstance, 0);

	if (!m_worldWindow)
	{
		return false;
	}

	//Set main window as world window parent
	SetParent(m_worldWindow, m_mainWindow);

	//Size world window
	SizeWorld();

	SetMenu(m_worldWindow, 0);

	return true;
}

//Shutdown window
void WindowManager::ShutdownWindow()
{
	//Remove child window
	DestroyWindow(m_worldWindow);
	m_worldWindow = 0;

	//Remove window
	DestroyWindow(m_mainWindow);
	m_mainWindow = 0;

	//Shutdown system
	m_system->Shutdown();

	//Remove application instance
	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = 0;

	//Release pointer to class
	ApplicationHandle = 0;
}

/////////////////////////////////////////////////////////
//Local
/////////////////////////////////////////////////////////

//Convert filename
std::string ConvertFilename(std::wstring path)
{
	int size;
	int pathLength = (int)path.length() + 1;

	//Get size of path
	size = WideCharToMultiByte(CP_ACP, 0, path.c_str(), pathLength, 0, 0, 0, 0);

	//Create string to size of path
	std::string result(size, '\0');

	//Convert path to result
	WideCharToMultiByte(CP_ACP, 0, path.c_str(), pathLength, &result[0], size, 0, 0);

	return result;
}

//Extract filename
std::string ExtractFilename(std::wstring path)
{
	std::string p = ConvertFilename(path);
	std::string result;

	int i = 0;
	char h = ' ';

	while (h != '.')
	{
		h = p[i];

		++i;
	}

	while (h != '\\')
	{
		h = p[i];

		--i;
	}

	++i;

	while (h != '.')
	{
		h = p[i];

		if ((h != '.') && (h != '\\'))
		{
			result.push_back(h);
		}

		++i;
	}

	return result;
}

//Open file dialog
void OpenFile(HWND hwnd)
{
	std::string filename;

	//Initialize common item
	HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED |
									COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileDialog* fo = 0;

		//Create the file open dialog object
		hr = CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&fo));

		if (SUCCEEDED(hr))
		{
			//Show the open dialog box
			hr = fo->Show(0);

			//Get the file name from the dialog box
			if (SUCCEEDED(hr))
			{
				IShellItem* item;

				hr = fo->GetResult(&item);

				if (SUCCEEDED(hr))
				{
					LPWSTR path;

					hr = item->GetDisplayName(SIGDN_FILESYSPATH, &path);

					//Display the file name
					if (SUCCEEDED(hr))
					{
						//Convert to wstring and extract filename
						std::wstring t = path;
						filename = ExtractFilename(t);

						CoTaskMemFree(path);
					}

					item->Release();
				}
			}

			fo->Release();
		}

		CoUninitialize();
	}

	ApplicationHandle->UpdateModel((char*)filename.c_str());
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
		//Check for activation messages
	case WM_ACTIVATE:
		switch LOWORD(wparam)
		{
			//If window is active
		case WA_ACTIVE:
			return 0;

			//If window was activated by click
		case WA_CLICKACTIVE:

			SendMessage(hwnd, WM_NCACTIVATE, TRUE, NULL);

			return 0;

			//If window was deactivated
		case WA_INACTIVE:
			if ((HWND)lparam != hwnd)
			{
				SendMessage(hwnd, WM_NCACTIVATE, TRUE, NULL);
				return 0;
			};
		}

		//Check if window is closed
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

		//Check if window is destroyed
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		//Check for minimize
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

		//Menu bar options
	case WM_COMMAND:
	{	
		int iD = LOWORD(wparam);

		switch (iD)
		{
			//File menu actions
			//Open file
		case IDF_OPEN:
			OpenFile(hwnd);
			return 0;

			//Shutdown and exit program
		case IDF_EXIT:
			PostQuitMessage(0);
			return 0;

			//Material menu actions
			
			//Model menu cations
			//Load cube model
		case IDMOD_CUBE:
			ApplicationHandle->UpdateModel("Cube");
			return 0;

			//Load human male model
		case IDMOD_HUMANMALE:
			ApplicationHandle->UpdateModel("HumanMale");
			return 0;

			//Load monkey model
		case IDMOD_MONKEY:
			ApplicationHandle->UpdateModel("Monkey");
			return 0;

			//Load sphere model
		case IDMOD_SPHERE:
			ApplicationHandle->UpdateModel("Sphere");
			return 0;

		default:
			break;
		}
	}

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