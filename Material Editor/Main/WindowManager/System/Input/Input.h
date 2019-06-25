/*
Input class is captures peripheral input (currently mouse and keyboard).
It captures the state of a key/the mouse by receiving messages as to which keys are down from the message handler.
It then stores these states in a boolean array from which they can be queried.
An enumeration is used to store the keys as known alphabet characters.
*/

#pragma once

#include "../Math/MathLib.h"

#include <unordered_map>
#include <Windows.h>

class Input
{
public:
	void Initialize();
	bool IsKeyDown(
		int& key);
	void Keyboard(
		RAWKEYBOARD& kB);
	void Mouse(
		RAWMOUSE& m);
	void ProcessCharacter(
		MathLib::Vectors::Vector3D& force);
	void ProcessMovement(
		MathLib::Vectors::Vector3D& force);
	void ProcessMouse(
		MathLib::Vectors::Vector3D& torque);
	bool ProcessQuit();
	void ResetKeys();

private:
	POINT mouseP = { 0, 0 }, prevMouseP = { 0, 0 };

	std::unordered_map<int, bool> m_keys;
};