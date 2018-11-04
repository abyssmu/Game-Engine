#include "System.h"

#include <vector>
#include <string>
#include <fstream>

bool System::Initialize(
	int screenHeight,
	int screenWidth,
	HWND hwnd)
{
	m_hWnd = hwnd;

	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	if (!InitializeGraphics())
	{
		return false;
	}

	if (!InitializeCamera())
	{
		return false;
	}

	if (!InitializeEntity())
	{
		return false;
	}

	if (!InitializeInput())
	{
		return false;
	}

	return true;
}

void System::Shutdown()
{
	if (m_graphics)
	{
		m_graphics->Shutdown();
		delete m_graphics;
		m_graphics = 0;
	}

	if (m_entities)
	{
		m_entities->Shutdown();
		delete m_entities;
		m_entities = 0;
	}

	if (m_input)
	{
		delete m_input;
		m_input = 0;
	}
}

void System::Run(
	bool& minimized)
{
	auto msg = MSG();

	ZeroMemory(&msg, sizeof(MSG));

	auto done = false;
	auto firstPass = true;
	
	while (!done)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else if (!minimized)
		{
			if (CheckResizeWindow())
			{
				if (!Frame())
				{
					done = true;
				}

				firstPass = false;
			}
			else if (!firstPass)
			{
				if (!m_graphics->ResetDX(m_screenHeight, m_screenWidth, m_hWnd))
				{
					done = true;
				}
			}
		}
	}
}

void System::KeyDown(
	unsigned int key)
{
	m_input->KeyDown(key);
}

void System::KeyUp(
	unsigned int key)
{
	m_input->KeyUp(key);
}

void System::MouseActive(
	bool active)
{
	if (!active)
	{
		m_mouseGo = true;
	}

	m_mouseActive = active;
}

void System::ResetKeys()
{
	m_input->ResetKeys();
}

void System::UpdateModel(
	std::string modelName)
{
	m_modelName = modelName;

	UpdateEntity();
}

void System::CreateFilenameString(
	std::string& filename)
{
	std::string post = ".dae";
	std::string pre = "./Models/";

	filename = pre + m_modelName + post;
}

void System::CheckPosition()
{
	switch (m_modelName[0])
	{
	case 'C':
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 2.0));
		return;

	case 'H':
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 5.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case 'M':
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 2.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(-MathLib::PI / 2, MathLib::PI, 0.0));
		return;
	}
}

bool System::CheckResizeWindow()
{
	auto rect = RECT();

	GetWindowRect(m_hWnd, &rect);

	auto dX = (rect.right - rect.left) - m_screenWidth;
	auto dY = (rect.bottom - rect.top) - m_screenHeight;
	
	if((dX != 0) || (dY != 0))
	{
		m_screenHeight = dY + m_screenHeight;
		m_screenWidth = dX + m_screenWidth;

		return false;
	}

	return true;
}

bool System::Frame()
{
	auto force = MathLib::Vectors::Zero_3D();
	auto forceC = MathLib::Vectors::Zero_3D();
	auto torque = MathLib::Vectors::Zero_3D();

	if (!ProcessInput(force, forceC, torque))
	{
		return false;
	}

	UpdateCamera(force, torque);
	ProcessGraphics();

	return true;
}

bool System::InitializeCamera()
{
	auto position = MathLib::Vectors::Vector3D(0.0, 0.0, -3.0);
	auto rotation = MathLib::Vectors::Vector3D(0.0, 0.0, 0.0);

	m_camera = new Camera;
	if (!m_camera)
	{
		return false;
	}

	m_camera->Initialize(position, rotation);
	m_camera->Render();

	return true;
}

bool System::InitializeEntity()
{
	auto filename = std::string("");

	CreateFilenameString(filename);

	m_entities = new Entity;
	if (!m_entities)
	{
		return false;
	}
	
	auto position = MathLib::Vectors::Vector3D(0.0, 0.0, 0.0);
	auto rotation = MathLib::Vectors::Vector3D(0.0, 0.0, 0.0);
	
	if (!m_entities->Initialize(m_graphics->GetDevice(),
		position, rotation, (char*)filename.c_str()))
	{
		return false;
	}

	return true;
}

bool System::InitializeGraphics()
{
	m_graphics = new Graphics;
	if (!m_graphics)
	{
		return false;
	}

	m_graphics->Initialize(m_screenHeight, m_screenWidth,
		m_hWnd);

	return true;
}

bool System::InitializeInput()
{
	m_input = new Input;
	if (!m_input)
	{
		return false;
	}

	m_input->Initialize();

	return true;
}

bool System::ProcessGraphics()
{
	auto bgcolor = Colors::Black();

	for (auto i = 0; i < m_entities->GetNumMeshes(); ++i)
	{
		if (!m_graphics->Frame(bgcolor, m_camera->GetViewMatrix(),
			m_entities->GetModelInfo(i)))
		{
			return false;
		}
	}

	return true;
}

bool System::ProcessInput(
	MathLib::Vectors::Vector3D& force,
	MathLib::Vectors::Vector3D& forceC,
	MathLib::Vectors::Vector3D& torque)
{
	if (!m_input->ProcessQuit())
	{
		return false;
	}

	m_input->ProcessCharacter(forceC);
	m_entities->UpdatePosRot(forceC, MathLib::Vectors::Vector3D(0.0, 0.0, 0.0));

	if (m_mouseActive)
	{
		m_input->ProcessMouse(torque, m_mouseGo);
	}

	m_input->ProcessMovement(force);

	return true;
}

void System::UpdateCamera(
	MathLib::Vectors::Vector3D force,
	MathLib::Vectors::Vector3D torque)
{
	m_camera->UpdatePosRot(force, torque);
	m_camera->Render();
}

void System::UpdateEntity()
{
	if (m_entities)
	{
		m_entities->Shutdown();
		delete m_entities;
		m_entities = 0;
	}

	InitializeEntity();
	CheckPosition();
}