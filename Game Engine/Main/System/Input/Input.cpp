#include "Input.h"

Input::Input()
{}

Input::Input(const Input& other)
{}

Input::~Input()
{}

void Input::Initialize()
{
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

bool Input::ProcessQuit()
{
	if (IsKeyDown(ESC))
	{
		return false;
	}

	return true;
}