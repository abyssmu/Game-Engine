//Includes
#include <vector>
#include <string>
#include <fstream>

//Class Includes
#include "System.h"

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
bool System::Initialize(int screenHeight, int screenWidth, HWND hwnd)
{
	//Capture handle
	m_hWnd = hwnd;

	//Initialize width and height of screen
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

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
}

//Main program loop
void System::Run(bool& minimized)
{
	MSG msg;
	bool done, firstPass;
	done = false;
	firstPass = true;

	//Initialize message structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until msg == quit
	while (!done)
	{
		//Handle windows messages
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
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

//Set input key down
void System::KeyDown(unsigned int key)
{
	m_input->KeyDown(key);
}

//Set input key up
void System::KeyUp(unsigned int key)
{
	m_input->KeyUp(key);
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

	m_graphics->Initialize(m_screenHeight, m_screenWidth,
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

//Process graphics
bool System::ProcessGraphics()
{
	Colors::Color bgcolor = Colors::Black();

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

//Update camera
void System::UpdateCamera(MathLib::Vectors::Vector3D force,
						MathLib::Vectors::Vector3D torque)
{
	//Set camera current view matrix
	m_camera->UpdatePosRot(force, torque);
	m_camera->Render();
}