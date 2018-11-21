#include "WindowManager.h"

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
	if (m_system)
	{
		return true;
	}

	return false;
}

HWND WindowManager::GetMain()
{
	return m_mainWindow;
}

HWND WindowManager::GetWorld()
{
	return m_worldWindow;
}

LRESULT CALLBACK WindowManager::MainMessageHandler(
	HWND& hwnd,
	UINT& umsg,
	WPARAM& wparam,
	LPARAM& lparam)
{
	if (m_system)
	{
		m_system->MouseActive(false);
		m_system->ResetKeys();
	}

	switch (umsg)
	{
	case WM_ACTIVATE:
		switch LOWORD(wparam)
		{
		case WA_ACTIVE:
			return 0;

		case WA_CLICKACTIVE:

			SendMessage(hwnd, WM_NCACTIVATE, TRUE, NULL);

			return 0;

		case WA_INACTIVE:
			if ((HWND)lparam != hwnd)
			{
				SendMessage(hwnd, WM_NCACTIVATE, TRUE, NULL);

				return 0;
			};
		}

	case WM_CLOSE:
		PostQuitMessage(0);

		return 0;

	case WM_COMMAND:
	{
		int iD = LOWORD(wparam);

		switch (iD)
		{
			//File menu actions
		case IDF_OPEN:
			OpenFile();

			return 0;

		case IDF_EXIT:
			PostQuitMessage(0);

			return 0;

			//Material menu actions

			//Model menu cations
		case IDMOD_CUBE:
			m_system->UpdateModel("Cube");

			return 0;

		case IDMOD_HUMANMALE:
			m_system->UpdateModel("HumanMale");

			return 0;

		case IDMOD_MONKEY:
			m_system->UpdateModel("Monkey");

			return 0;

		case IDMOD_SPHERE:
			m_system->UpdateModel("Sphere");

			return 0;

		default:
			break;
		}
	}

	case WM_SIZE:
		if ((wparam == SIZE_MINIMIZED) && m_system && !m_minimized)
		{
			m_minimized = true;
			m_system->SetMinimized(m_minimized);

			return 0;
		}
		else if ((wparam == 0) && m_system && m_minimized)
		{
			m_minimized = false;
			m_system->SetMinimized(m_minimized);

			return 0;
		}

		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

LRESULT CALLBACK WindowManager::WorldMessageHandler(
	HWND& hwnd,
	UINT& umsg,
	WPARAM& wparam,
	LPARAM& lparam)
{
	if (m_system)
	{
		m_system->MouseActive(true);
	}

	switch (umsg)
	{
	case WM_KEYDOWN:
		m_system->KeyDown((unsigned int)wparam);

		return 0;

	case WM_KEYUP:
		m_system->KeyUp((unsigned int)wparam);

		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void WindowManager::SizeWorld()
{
	auto rc = RECT();
	auto perc = 0.8;

	GetClientRect(m_mainWindow, &rc);

	m_worldHeight = (int)(rc.bottom);
	m_worldWidth = (int)(rc.right * perc);

	MoveWindow(m_worldWindow, rc.left, rc.top, m_worldWidth, m_worldHeight, false);
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

bool WindowManager::InitializeInner()
{
	if (!InitializeWorld())
	{
		return false;
	}

	return true;
}

bool WindowManager::InitializeMain()
{
	auto wc = WNDCLASSEX();

	ApplicationHandle = this;

	m_hInstance = GetModuleHandle(0);

	m_applicationName = "Material Editor";

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

	ShowWindow(m_mainWindow, SW_SHOW);
	SetFocus(m_mainWindow);

	return true;
}

bool WindowManager::InitializeWorld()
{
	auto wc = WNDCLASSEX();

	m_hInstance = GetModuleHandle(0);

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

	m_system->UpdateModel((char*)filename.c_str());
}

void WindowManager::ShutdownWindow()
{
	DestroyWindow(m_worldWindow);
	m_worldWindow = 0;

	DestroyWindow(m_mainWindow);
	m_mainWindow = 0;

	m_system->Shutdown();

	UnregisterClass((LPCSTR)m_applicationName, m_hInstance);
	m_hInstance = 0;

	ApplicationHandle = 0;
}

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT umessage,
	WPARAM wparam,
	LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;

	default:
		if (!ApplicationHandle->CheckResizeWindow())
		{
			ApplicationHandle->SizeWorld();
		}

		if (GetActiveWindow() == ApplicationHandle->GetWorld())
		{
			return ApplicationHandle->WorldMessageHandler(hwnd, umessage,
				wparam, lparam);
		}

		return ApplicationHandle->MainMessageHandler(hwnd, umessage,
			wparam, lparam);
	}
}