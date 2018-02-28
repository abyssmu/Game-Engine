#include "Input.h"

Input::Input()
{}

Input::Input(const Input& other)
{}

Input::~Input()
{}

void Input::Initialize()
{
	//Initialize key states to false
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}
}

bool Input::IsKeyDown(int key)
{
	//Return what state key is in
	return m_keys[key];
}

void Input::KeyDown(int input)
{
	//If a key is down, save state
	m_keys[input] = true;
}

void Input::KeyUp(int input)
{
	//If a key is released, save state
	m_keys[input] = false;
}

void Input::ProcessMouse(float* rot)
{
	//Check cursor position
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		float speed = 0.2f;

		//Rotate about y axis
		if (mouseP.x != prevMouseP.x)
		{
			rot[1] += (mouseP.x - prevMouseP.x) * speed;
		}
		//Rotate about x axis
		if (mouseP.y != prevMouseP.y)
		{
			rot[0] += (mouseP.y - prevMouseP.y) * speed;
		}
	}

	//Save previous mouse state and capture new
	prevMouseP = mouseP;
	GetCursorPos(&mouseP);
}

void Input::ProcessMovement(float& forw, float& lR, float& uD)
{
	float speed = 0.2f;

	//Unit X movement
	if (IsKeyDown(D))
	{
		lR += speed;
	}
	if (IsKeyDown(A))
	{
		lR -= speed;
	}

	//Unit Y movement
	if (IsKeyDown(R))
	{
		uD += speed;
	}
	if (IsKeyDown(F))
	{
		uD -= speed;
	}

	//Unit Z movement
	if (IsKeyDown(W))
	{
		forw += speed;
	}
	if (IsKeyDown(S))
	{
		forw -= speed;
	}
}

bool Input::ProcessQuit()
{
	if (IsKeyDown(ESC))
	{
		return false;
	}

	return true;
}