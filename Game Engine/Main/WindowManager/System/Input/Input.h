/*
Input class is captures peripheral input (currently mouse and keyboard).
It captures the state of a key/the mouse by receiving messages as to which keys are down from the message handler.
It then stores these states in a boolean array from which they can be queried.
An enumeration is used to store the keys as known alphabet characters.
*/

#pragma once

#include "../Math/MathLib.h"

#include <Windows.h>

class Input
{
public:
	void Initialize();
	bool IsKeyDown(int key);
	void KeyDown(int key);
	void KeyUp(int key);
	void ProcessCharacter(MathLib::Vectors::Vector3D& force);
	void ProcessMovement(MathLib::Vectors::Vector3D& force);
	void ProcessMouse(MathLib::Vectors::Vector3D& torque, bool& go);
	bool ProcessQuit();
	void ResetKeys();

private:
	bool m_keys[256] = { 0 };
	POINT mouseP = { 0, 0 }, prevMouseP = { 0, 0 };
};