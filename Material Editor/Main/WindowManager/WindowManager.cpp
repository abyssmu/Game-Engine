#include "WindowManager.h"

WindowManager* ApplicationHandle = 0;

bool WindowManager::Initialize(
	int screenHeight,
	int screenWidth)
{
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	if (!InitializeMain())
	{
		return false;
	}

	if (!InitializeInner())
	{
		return false;
	}

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

void WindowManager::Shutdown()
{
	ShutdownWindow();
}

void WindowManager::Run()
{
	m_system->Run();
}

bool WindowManager::CheckResizeWindow()
{
	auto rect = RECT();

	GetWindowRect(m_mainWindow, &rect);

	auto dX = (rect.right - rect.left) - m_screenWidth;
	auto dY = (rect.bottom - rect.top) - m_screenHeight;

	if ((dX != 0) || (dY != 0))
	{
		m_screenHeight = dY + m_screenHeight;
		m_screenWidth = dX + m_screenWidth;

		return false;
	}

	return true;
}

bool WindowManager::CheckSystem()
{
	return bool(m_system);
}

HWND WindowManager::GetMain()
{
	return m_mainWindow;
}

bool WindowManager::GetMinimized()
{
	return m_minimized;
}

HWND WindowManager::GetWorld()
{
	return m_worldWindow;
}

void WindowManager::KeyDown(
	unsigned int key)
{
	m_system->KeyDown(key);
}

void WindowManager::KeyUp(
	unsigned int key)
{
	m_system->KeyUp(key);
}

void WindowManager::OpenFile()
{
	auto filename = std::string("");
	auto hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileDialog* fo = 0;

		hr = CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&fo));

		if (SUCCEEDED(hr))
		{
			hr = fo->Show(0);

			if (SUCCEEDED(hr))
			{
				IShellItem* item;

				hr = fo->GetResult(&item);

				if (SUCCEEDED(hr))
				{
					auto path = LPWSTR();

					hr = item->GetDisplayName(SIGDN_FILESYSPATH, &path);

					if (SUCCEEDED(hr))
					{
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

	auto model = std::string(filename.c_str());

	m_system->UpdateModel(model);
}

void WindowManager::SetMinimized(
	bool& min)
{
	m_minimized = min;
}

void WindowManager::SetMouseState(
	bool state)
{
	if (m_system)
	{
		m_system->MouseActive(state);

		if (m_mouseState)
		{
			m_system->ResetKeys();
		}
	}
}

void WindowManager::SizeControls()
{
	auto rc = RECT();
	GetClientRect(m_controlsContainer, &rc);

	auto posY = int(20);
	auto w = int(rc.right);

	MoveWindow(m_trackbarText, 0, 0, w, 20, false);
	MoveWindow(m_trackbar, 0, posY, w, 30, false);
}

void WindowManager::SizeWorld()
{
	auto rc = RECT();
	GetClientRect(m_mainWindow, &rc);

	m_worldHeight = int(rc.bottom);
	m_worldWidth = int(rc.right * m_worldPerc);

	MoveWindow(m_worldWindow, rc.left, rc.top, m_worldWidth, m_worldHeight, false);
}

void WindowManager::UpdateModel(
	std::string model)
{
	m_system->UpdateModel(model);
}

std::string WindowManager::ConvertFilename(
	std::wstring& path)
{
	auto pathLength = (int)path.length() + 1;
	auto size = WideCharToMultiByte(CP_ACP, 0, path.c_str(), pathLength, 0, 0, 0, 0);

	auto result = std::string(size, '\0');

	WideCharToMultiByte(CP_ACP, 0, path.c_str(), pathLength, &result[0], size, 0, 0);

	return result;
}

std::string WindowManager::ExtractFilename(
	std::wstring& path)
{
	auto p = ConvertFilename(path);

	auto i = 0;
	auto h = ' ';

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
	auto result = std::string("");

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

bool WindowManager::InitializeControlsContainer()
{
	auto wc = WNDCLASSEX();

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WNDPROC(ControlsMessageHandler);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = 0;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	m_controlsContainer = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_POPUP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, m_hInstance, 0);

	if (!m_controlsContainer)
	{
		return false;
	}

	return true;
}

bool WindowManager::InitializeInner()
{
	if (!InitializeWorld())
	{
		return false;
	}

	if (!InitializeTrackbar())
	{
		return false;
	}

	if (!InitializeLightText())
	{
		return false;
	}

	SizeControls();

	return true;
}

bool WindowManager::InitializeLightText()
{
	m_lightInputX = CreateWindow("EDIT", 0, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, m_mainWindow, 0, m_hInstance, 0);
	m_lightInputY = CreateWindow("EDIT", 0, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, m_mainWindow, 0, m_hInstance, 0);
	m_lightInputZ = CreateWindow("EDIT", 0, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, m_mainWindow, 0, m_hInstance, 0);

	return true;
}

bool WindowManager::InitializeMain()
{
	auto wc = WNDCLASSEX();

	ApplicationHandle = this;

	m_hInstance = GetModuleHandle(0);

	m_applicationName = "Material Editor";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WNDPROC(MainMessageHandler);
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

	RegisterClassEx(&wc);

	auto posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenWidth) / 2;
	auto posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenHeight) / 2;

	m_mainWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		posX, posY, m_screenWidth, m_screenHeight, 0, 0, m_hInstance, 0);

	if (!m_mainWindow)
	{
		return false;
	}

	return true;
}

bool WindowManager::InitializeTrackbar()
{
	m_trackbar = CreateWindowEx(0, TRACKBAR_CLASS, "",
		WS_CHILD | WS_VISIBLE | TBS_NOTICKS,
		0, 0, 0, 0, m_controlsContainer, 0, m_hInstance, 0);

	SendMessage(m_trackbar, TBM_SETRANGE, WPARAM(TRUE), LPARAM(MAKELONG(0, 100)));
	SendMessage(m_trackbar, TBM_SETPAGESIZE, 0, LPARAM(4));
	SendMessage(m_trackbar, TBM_SETSEL, WPARAM(FALSE), LPARAM(MAKELONG(0, 1)));
	SendMessage(m_trackbar, TBM_SETPOS, WPARAM(TRUE), LPARAM(0));

	return true;
}

bool WindowManager::InitializeWorld()
{
	auto wc = WNDCLASSEX();

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WNDPROC(WorldMessageHandler);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = 0;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	m_worldWindow = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_POPUP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, m_hInstance, 0);

	if (!m_worldWindow)
	{
		return false;
	}

	SetParent(m_worldWindow, m_mainWindow);
	SizeWorld();
	SetMenu(m_worldWindow, 0);

	return true;
}

void WindowManager::ShutdownWindow()
{
	m_system->Shutdown();

	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = 0;

	ApplicationHandle = 0;
}