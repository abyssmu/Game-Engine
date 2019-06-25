#include "System.h"

#include <vector>
#include <string>
#include <fstream>

bool System::Initialize(
	int& screenHeight,
	int& screenWidth,
	HWND& hwnd)
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

	if (!InitializeLight())
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

void System::Run()
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
		else if (!m_minimized)
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

void System::Keyboard(
	RAWKEYBOARD& kB)
{
	m_input->Keyboard(kB);
}

void System::Mouse(
	RAWMOUSE& m)
{
	m_input->Mouse(m);
}

void System::ResetKeys()
{
	m_input->ResetKeys();
}

void System::SetLightAmbient(
	double r,
	double g,
	double b)
{
	m_directionalLight->SetAmbientColor(Colors::Color(r, g, b, 1.0));
}

void System::SetLightDiffuse(
	double r,
	double g,
	double b)
{
	m_directionalLight->SetDiffuseColor(Colors::Color(r, g, b, 1.0));
}

void System::SetLightDirection(
	double x,
	double y,
	double z)
{
	m_directionalLight->SetDirection(MathLib::Vectors::Vector3D(x, y, z));
}

void System::SetMinimized(
	bool& min)
{
	m_minimized = min;
}

void System::SetSpecular(
	double r,
	double g,
	double b,
	double p)
{
	m_directionalLight->SetSpecularColor(Colors::Color(r, g, b, 1.0));
	
	m_directionalLight->SetSpecularPower(p);
}

void System::UpdateModel(
	std::string& modelName)
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
	enum
	{
		Bedroom,
		Bird,
		Cube,
		Dragon,
		HumanMale,
		Monkey,
		Skull,
		Sofa,
		Sphere,
		Tree
	};

	int name = -1;

	if (m_modelName == "Bedroom")
	{
		name = Bedroom;
	}
	else if (m_modelName == "Bird")
	{
		name = Bird;
	}
	else if (m_modelName == "Cube")
	{
		name = Cube;
	}
	else if (m_modelName == "Dragon")
	{
		name = Dragon;
	}
	else if (m_modelName == "HumanMale")
	{
		name = HumanMale;
	}
	else if (m_modelName == "Monkey")
	{
		name = Monkey;
	}
	else if (m_modelName == "Skull")
	{
		name = Skull;
	}
	else if (m_modelName == "Sofa")
	{
		name = Sofa;
	}
	else if (m_modelName == "Sphere")
	{
		name = Sphere;
	}
	else if (m_modelName == "Tree")
	{
		name = Tree;
	}

	switch (name)
	{
	case Bird:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 4.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case Bedroom:
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, 2 * MathLib::PI / 3, 0.0));
		return;

	case Cube:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 2.0));
		return;

	case Dragon:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 15.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case HumanMale:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 5.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case Monkey:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 2.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(-MathLib::PI / 2, MathLib::PI, 0.0));
		return;
		
	case Skull:
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case Sofa:
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, MathLib::PI, 0.0));
		return;

	case Sphere:
		m_entities->SetRotation(MathLib::Vectors::Vector3D(MathLib::PI / 2, 0.0, 0.0));
		return;

	case Tree:
		m_entities->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 20.0));
		m_entities->SetRotation(MathLib::Vectors::Vector3D(0.0, 0.0, 0.0));
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
	auto zero = MathLib::Vectors::Zero_3D();

	if (!ProcessInput(force, forceC, torque))
	{
		return false;
	}

	m_entities->UpdatePosRot(forceC, torque);
	UpdateCamera(force, zero);

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
	auto rotation = MathLib::Vectors::Vector3D(MathLib::PI / 2, 0.0, 0.0);
	
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

bool System::InitializeLight()
{
	m_directionalLight = new Directional;
	if (!m_directionalLight)
	{
		return false;
	}

	m_directionalLight->SetAmbientColor(Colors::Grey());
	m_directionalLight->SetDiffuseColor(Colors::White());
	m_directionalLight->SetDirection(MathLib::Vectors::Vector3D(0.0, 0.0, 1.0));
	m_directionalLight->SetPosition(MathLib::Vectors::Vector3D(0.0, 0.0, 0.0));
	m_directionalLight->SetSpecularColor(Colors::White());
	m_directionalLight->SetSpecularPower(32.0);

	return true;
}

bool System::ProcessGraphics()
{
	auto bgcolor = Colors::Black();

	for (auto i = 0; i < m_entities->GetNumMeshes(); ++i)
	{
		if (!m_graphics->Frame(bgcolor, m_camera->GetViewMatrix(),
			m_camera->GetPosition(), m_directionalLight, m_entities->GetModelInfo(i)))
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

	m_input->ProcessCharacter(torque);

	/*if (m_mouseActive)
	{
		m_input->ProcessMouse(torque, m_mouseGo);
	}*/

	m_input->ProcessMovement(force);

	return true;
}

void System::UpdateCamera(
	MathLib::Vectors::Vector3D& force,
	MathLib::Vectors::Vector3D& torque)
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