#include "Input.h"
#include "Keys.h"

void Input::Initialize()
{
	
	for (auto i = 0; i < 256; ++i)
	{
		if (m_keys.empty())
		{
			m_keys.insert({ i, false });
		}
		else
		{
			m_keys[i] = false;
		}
	}
}

bool Input::IsKeyDown(
	int& key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		return false;
	}

	return m_keys[key];
}

void Input::Keyboard(
	RAWKEYBOARD& kB)
{
	UINT flags = kB.Flags;
	UINT scanCode = kB.MakeCode;

	const bool up = (flags & RI_KEY_BREAK) != 0;

	if (!up)
	{
		m_keys[scanCode] = true;
	}
	else
	{
		m_keys[scanCode] = false;
	}
}

void Input::Mouse(
	RAWMOUSE& m)
{
	
}

void Input::ProcessCharacter(
	MathLib::Vectors::Vector3D& force)
{
	auto speed = 0.2;

	//Unit x movement
	if (IsKeyDown(Key::Left_Arrow))
	{
		force.y += speed;
	}
	if (IsKeyDown(Key::Right_Arrow))
	{
		force.y -= speed;
	}

	//Unit y movement

	//Unit z movement
	if (IsKeyDown(Key::Up_Arrow))
	{
		force.x -= speed;
	}
	if (IsKeyDown(Key::Down_Arrow))
	{
		force.x += speed;
	}
}

void Input::ProcessMovement(
	MathLib::Vectors::Vector3D& force)
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
	if (IsKeyDown(Key::Space))
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

void Input::ProcessMouse(
	MathLib::Vectors::Vector3D& torque)
{
	/*if (((GetKeyState(Key::Left_Mouse) & 0x100) != 0) && !go)
	{
		auto speed = 0.2;

		if (mouseP.x != prevMouseP.x)
		{
			torque.y += (double(mouseP.x) - double(prevMouseP.x)) * speed;
		}
		if (mouseP.y != prevMouseP.y)
		{
			torque.x += (double(mouseP.y) - double(prevMouseP.y)) * speed;
		}
	}*/

	/*if (go)
	{
		go = false;

		GetCursorPos(&mouseP);
		prevMouseP = mouseP;
	}
	else
	{
		prevMouseP = mouseP;
		GetCursorPos(&mouseP);
	}*/
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