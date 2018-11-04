#include "Input.h"
#include "Keys.h"

void Input::Initialize()
{
	for (auto i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}
}

bool Input::IsKeyDown(int key)
{
	return m_keys[key];
}

void Input::KeyDown(int key)
{
	m_keys[key] = true;
}

void Input::KeyUp(int key)
{
	m_keys[key] = false;
}

void Input::ProcessCharacter(MathLib::Vectors::Vector3D& force)
{
	auto speed = 0.2;

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

void Input::ProcessMovement(MathLib::Vectors::Vector3D& force)
{
	auto speed = 0.2;

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

void Input::ProcessMouse(MathLib::Vectors::Vector3D& torque, bool& go)
{
	if (((GetKeyState(Key::Left_Mouse) & 0x100) != 0) && !go)
	{
		auto speed = 0.2;

		if (mouseP.x != prevMouseP.x)
		{
			torque.y += (mouseP.x - prevMouseP.x) * speed;
		}
		if (mouseP.y != prevMouseP.y)
		{
			torque.x += (mouseP.y - prevMouseP.y) * speed;
		}
	}

	if (go)
	{
		go = false;

		GetCursorPos(&mouseP);
		prevMouseP = mouseP;
	}
	else
	{
		prevMouseP = mouseP;
		GetCursorPos(&mouseP);
	}
}

bool Input::ProcessQuit()
{
	if (IsKeyDown(Key::Escape))
	{
		return false;
	}

	return true;
}

void Input::ResetKeys()
{
	Initialize();
}