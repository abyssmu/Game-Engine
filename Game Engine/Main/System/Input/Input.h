#pragma once

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

//Includes
#include <Windows.h>

//Class Includes
#include "../Math/MathLib.h"

class Input
{
public:
	//Default constructor
	Input();
	
	//Default copy constructor
	Input(const Input& other);

	//Default destructor
	~Input();

	////////Main Functions
	//Initialize all key states
	void Initialize();

	////////Utility Functions
	//Query current key state
	bool IsKeyDown(int key);

	//Capture down state of key
	void KeyDown(int key);
	
	//Capture up state of key
	void KeyUp(int key);

	//Capture mouse input
	void ProcessMouse(MathLib::Vectors::Vector3D& torque);

	//Capture movement keys
	void ProcessMovement(MathLib::Vectors::Vector3D& force);
	
	//Capture quit key
	bool ProcessQuit();

private:
	////////Main Functions

	////////Main Variables
	bool m_keys[256];
	POINT mouseP, prevMouseP;

	////////Keys
	enum
	{
		ESC = 0x1B,
		W = 0x57,
		A = 0x41,
		S = 0x53,
		D = 0x44,
		R = 0x52,
		F = 0x46
	};
};

#endif