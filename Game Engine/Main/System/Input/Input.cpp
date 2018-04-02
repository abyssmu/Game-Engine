//Input handler class
//Captures input process from windows messages

#include "Input.h"

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

//Capture mouse input
void Input::ProcessMouse(MathLib::Vectors::Vector3D& torque)
{
	//Check cursor position
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		float speed = 0.2f;

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

//Capture movement keys
void Input::ProcessMovement(MathLib::Vectors::Vector3D& force)
{
	float speed = 0.2f;

	//Unit X movement
	if (IsKeyDown(D))
	{
		force.x += speed;
	}
	if (IsKeyDown(A))
	{
		force.x -= speed;
	}

	//Unit Y movement
	if (IsKeyDown(R))
	{
		force.y += speed;
	}
	if (IsKeyDown(F))
	{
		force.y -= speed;
	}

	//Unit Z movement
	if (IsKeyDown(W))
	{
		force.z += speed;
	}
	if (IsKeyDown(S))
	{
		force.z -= speed;
	}
}

//Capture quit key
bool Input::ProcessQuit()
{
	if (IsKeyDown(ESC))
	{
		return false;
	}

	return true;
}