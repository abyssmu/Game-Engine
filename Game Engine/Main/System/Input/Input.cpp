#include "Input.h"
#include "Keys.h"

//Default constructor
Input::Input()
{}

//Default copy constructor
Input::Input(const Input& other)
{}

//Default destructor
Input::~Input()
{}

//Initialize all key states
void Input::Initialize()
{
	//Initialize key states to false
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}
}

//Query current key state
bool Input::IsKeyDown(int key)
{
	//Return what state key is in
	return m_keys[key];
}

//Capture down state of key
void Input::KeyDown(int key)
{
	//If a key is down, save state
	m_keys[key] = true;
}

//Capture up state of key
void Input::KeyUp(int key)
{
	//If a key is released, save state
	m_keys[key] = false;
}

//Process character movement
void Input::ProcessCharacter(MathLib::Vectors::Vector3D& force)
{
	double speed = 0.2;

	//Unit x movement
	if (IsKeyDown(Key::Right_Arrow))
	{
		force.x += speed;
	}
	if (IsKeyDown(Key::Left_Arrow))
	{
		force.x -= speed;
	}

	//Unit y movement

	//Unit z movement
	if (IsKeyDown(Key::Up_Arrow))
	{
		force.z += speed;
	}
	if (IsKeyDown(Key::Down_Arrow))
	{
		force.z -= speed;
	}
}

//Capture movement keys
void Input::ProcessMovement(MathLib::Vectors::Vector3D& force)
{
	double speed = 0.2;

	//Unit x movement
	if (IsKeyDown(Key::D))
	{
		force.x += speed;
	}
	if (IsKeyDown(Key::A))
	{
		force.x -= speed;
	}

	//Unit y movement
	if (IsKeyDown(Key::R))
	{
		force.y += speed;
	}
	if (IsKeyDown(Key::F))
	{
		force.y -= speed;
	}

	//Unit z movement
	if (IsKeyDown(Key::W))
	{
		force.z += speed;
	}
	if (IsKeyDown(Key::S))
	{
		force.z -= speed;
	}
}

//Capture mouse input
void Input::ProcessMouse(MathLib::Vectors::Vector3D& torque)
{
	//Check cursor position
	if ((GetKeyState(Key::Left_Mouse) & 0x100) != 0)
	{
		double speed = 0.2;

		//Rotate about y axis
		if (mouseP.x != prevMouseP.x)
		{
			torque.y += (mouseP.x - prevMouseP.x) * speed;
		}
		//Rotate about x axis
		if (mouseP.y != prevMouseP.y)
		{
			torque.x += (mouseP.y - prevMouseP.y) * speed;
		}
	}

	//Save previous mouse state and capture new
	prevMouseP = mouseP;
	GetCursorPos(&mouseP);
}

//Capture quit key
bool Input::ProcessQuit()
{
	if (IsKeyDown(Key::Escape))
	{
		return false;
	}

	return true;
}